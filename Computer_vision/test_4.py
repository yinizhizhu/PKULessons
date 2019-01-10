# from __future__ import print_function
import torch.nn.functional as F
import numpy as np
from test_dataset import DatasetFromFolder
import time, random, os, shutil
from mot_model import *
from torchvision.transforms import ToTensor
from global_set import w, h
from PIL import Image, ImageDraw
import matplotlib.pyplot as plt

torch.manual_seed(123)
np.random.seed(123)

t_dir = ''  # the dir of the final level


def deleteDir(del_dir):
    shutil.rmtree(del_dir)


tau_conf_score = 0.96

scale = 0  # 0 - single, 1 - multi-scale
if scale:
    scale_m = '_m'
else:
    scale_m = ''


if os.path.exists('Cars%s/'%scale_m):
    deleteDir('Cars%s/'%scale_m)
os.mkdir('Cars%s/'%scale_m)

if os.path.exists('Results%s/'%scale_m):
    deleteDir('Results%s/'%scale_m)
os.mkdir('Results%s/'%scale_m)

if os.path.exists('Resultso%s/'%scale_m):
    deleteDir('Resultso%s/'%scale_m)
os.mkdir('Resultso%s/'%scale_m)


class GN():
    def __init__(self, cuda=True):
        self.device = torch.device("cuda" if cuda else "cpu")

        print '     Preparing the model...'
        self.Car = torch.load('car_side_view.pth').to(self.device)
        self.test_set = DatasetFromFolder(scale)

    def evaluation(self):
        with torch.no_grad():
            out = open('../CarData/Evaluation/out%s.txt'%scale_m, 'w')
            gt = open('../CarData/Evaluation/trueLocations.txt', 'r')
            out1 = open('Results/results%s.txt'%scale_m, 'w')
            step = 0
            self.Car.eval()
            checker = []
            for img in self.test_set.candidates:
                bestScore = 0.0
                xs = []
                ys = []
                cs = []
                # bestPos = [0, 0]
                car = None
                width, height = img.size
                imn = np.asarray(img).tolist()
                for x in xrange(width):
                    for y in xrange(height):
                        imn[y][x] = 100
                # print imn.size

                container = []
                for x in xrange(0, width-w, 1):
                    for y in xrange(0, height-h, 1):
                        crop = img.crop([x, y, x + w, y + h])
                        e = ToTensor()(crop)
                        e = e.to(self.device)
                        e1 = self.Car(e)
                        tmp = F.softmax(e1)[0]
                        container.append(tmp[1].item())
                        if tmp[1] > bestScore:
                            bestScore = tmp[1].item()
                            bestPos = [x, y]
                            car = crop
                        if tmp[1] > tau_conf_score:
                            xs.append(x)
                            ys.append(y)
                            cs.append(tmp[1].item()-tau_conf_score)

                        if tmp[1] > tau_conf_score:
                            imn[y][x] = 255
                # plt.figure()
                # plt.hist(container, bins=1000, rwidth=0.9)
                # plt.xlabel('conf_score')
                # plt.ylabel('HZ')
                # plt.title(step)
                # plt.savefig(out_dir+'%d.png'%step)
                # plt.close()

                car.save('Cars%s/car%d_%.6f.png'%(scale_m, step, bestScore))
                imn = np.array(imn)
                imn = Image.fromarray(np.uint8(imn))
                line = gt.readline().strip().replace('(', '').replace(')', '').split(' ')
                draw = ImageDraw.Draw(imn)
                for pair in xrange(1, len(line)):
                    y, x = line[pair].split(',')
                    x, y = int(x), int(y)
                    draw.line((x, y, x+w, y), fill=180)
                    draw.line((x, y, x, y+h), fill=180)
                    draw.line((x+w, y, x+w, y+h), fill=180)
                    draw.line((x, y+h, x+w, y+h), fill=180)
                x = bestPos[0]
                y = bestPos[1]
                x, y = int(x), int(y)

                draw.line((x, y, x + w, y), fill=255)
                draw.line((x, y, x, y + h), fill=255)
                draw.line((x + w, y, x + w, y + h), fill=255)
                draw.line((x, y + h, x + w, y + h), fill=255)
                imn.save('Results%s/car%d.png'%(scale_m, step))

                drawo = ImageDraw.Draw(img)
                drawo.line((x, y, x + w, y), fill=255)
                drawo.line((x, y, x, y + h), fill=255)
                drawo.line((x + w, y, x + w, y + h), fill=255)
                drawo.line((x, y + h, x + w, y + h), fill=255)
                img.save('Resultso%s/car%d.png'%(scale_m, step))

                # x = 0.0
                # y = 0.0
                # conf_score = sum(cs)
                # for i in xrange(len(xs)):
                #     x += xs[i]*cs[i]
                #     y += ys[i]*cs[i]
                # bestPos = [x/conf_score, y/conf_score]

                print '%d: (%d,%d) %.6f' % (step, bestPos[1], bestPos[0], bestScore)
                print >> out1, '%d: (%d,%d) %.6f' % (step, bestPos[1], bestPos[0], bestScore)
                print >> out, '%d: (%d,%d)'%(step, bestPos[1], bestPos[0])
                checker.append([step, bestScore])
                step += 1
            gt.close()
            out.close()
            out1.close()

            ans = sorted(checker, key=lambda t: t[1])
            for tmp in ans:
                print tmp


a = GN()
a.evaluation()