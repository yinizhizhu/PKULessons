import torch.utils.data as data
import torch, cv2
from PIL import Image
from torchvision.transforms import ToTensor
from global_set import w, h


def load_img(filepath):
    img = Image.open(filepath)
    return img


class DatasetFromFolder(data.Dataset):
    def __init__(self):
        super(DatasetFromFolder, self).__init__()
        self.feature()

    def feature(self):
        self.candidates = []
        self.validates = []

        self.img_dir = '../CarData/TrainImages/'
        for i in xrange(500):
            img = load_img(self.img_dir+'neg-%d.pgm'%i)
            container = []
            img1 = ToTensor()(img)
            img2 = ToTensor()(img.transpose(Image.FLIP_LEFT_RIGHT))
            img3 = ToTensor()(img.transpose(Image.FLIP_TOP_BOTTOM))
            img4 = ToTensor()(img.transpose(Image.ROTATE_180))
            container.append(img1)
            container.append(img2)
            container.append(img3)
            container.append(img4)

            if i < 401:
                for tmpI in container:
                    self.candidates.append([tmpI, torch.LongTensor([0])])
            else:
                self.validates.append([container[0], torch.LongTensor([0])])
                # for tmpI in container:
                #     self.validates.append([tmpI, torch.LongTensor([0])])

        for i in xrange(550):
            img = load_img(self.img_dir+'pos-%d.pgm'%i)
            container = []

            img1 = ToTensor()(img)
            img2 = ToTensor()(img.transpose(Image.FLIP_LEFT_RIGHT))
            img3 = ToTensor()(img.transpose(Image.FLIP_TOP_BOTTOM))
            img4 = ToTensor()(img.transpose(Image.ROTATE_180))
            container.append(img1)
            container.append(img2)
            container.append(img3)
            container.append(img4)

            if i < 441:
                for tmpI in container:
                    self.candidates.append([tmpI, torch.LongTensor([1])])
            else:
                self.validates.append([container[0], torch.LongTensor([1])])
                # for tmpI in container:
                #     self.validates.append([tmpI, torch.LongTensor([1])])

        self.img_dir = '../CarData/cars_side_view/'
        for i in xrange(947):
            img = cv2.imread(self.img_dir+'pos-%d.pgm'%i)
            container = []

            img1 = ToTensor()(img)
            img2 = ToTensor()(cv2.flip(img, 1))
            img3 = ToTensor()(cv2.flip(img, 0))
            img4 = ToTensor()(cv2.flip(img, -1))
            container.append(img1[0].view(-1, 40, 100))
            container.append(img2[0].view(-1, 40, 100))
            container.append(img3[0].view(-1, 40, 100))
            container.append(img4[0].view(-1, 40, 100))

            if i < 758:
                for tmpI in container:
                    self.candidates.append([tmpI, torch.LongTensor([0])])
            else:
                self.validates.append([container[0], torch.LongTensor([0])])
                # for tmpI in container:
                #     self.validates.append([tmpI, torch.LongTensor([0])])

        for i in xrange(3120):
            img = cv2.imread(self.img_dir+'neg-%d.pgm'%i)
            container = []

            img1 = ToTensor()(img)
            img2 = ToTensor()(cv2.flip(img, 1))
            img3 = ToTensor()(cv2.flip(img, 0))
            img4 = ToTensor()(cv2.flip(img, -1))
            container.append(img1[0].view(-1, 40, 100))
            container.append(img2[0].view(-1, 40, 100))
            container.append(img3[0].view(-1, 40, 100))
            container.append(img4[0].view(-1, 40, 100))

            if i < 2496:
                for tmpI in container:
                    self.candidates.append([tmpI, torch.LongTensor([1])])
            else:
                self.validates.append([container[0], torch.LongTensor([1])])
                # for tmpI in container:
                #     self.validates.append([tmpI, torch.LongTensor([1])])

    def __getitem__(self, index):
        return self.candidates[index]

    def __len__(self):
        return len(self.candidates)


# img = load_img('../CarData/TrainImages/pos-0.pgm')
# img.show()
# img2 = img.crop([0, 10, 100, 40])
# img2.show()
# bbx = img2.resize((w, h), Image.ANTIALIAS)
# bbx.show()

# img = load_img('../CarData/TestImages/test-0.pgm')
# img.show()
# img1 = img.crop([0, 0, w, h])
# img1.show()

# import cv2
# import matplotlib.pyplot as plt
# import selectivesearch.selectivesearch as ss
# import matplotlib.patches as mpatches
#
# img = cv2.imread('../CarData/TestImages/test-0.pgm')
# print img.shape
# plt.imshow(img)
# img_lbl, regions = ss.selective_search(img, scale=500, sigma=0.8, min_size=40)
# print regions[:10]
# print len(regions)
#
# fig, ax = plt.subplots(ncols=1, nrows=1, figsize=(6, 6))
# ax.imshow(img)
# for reg in regions:
#     x, y, w, h = reg['rect']
#     rect = mpatches.Rectangle(
#     (x, y), w, h, fill=False, edgecolor='red', linewidth=1)
#     ax.add_patch(rect)
# plt.show()


# import numpy as np
# img = load_img('../CarData/TestImages/test-0.pgm')
# tmp = np.asarray(img)
# print type(tmp)
#
# tmp = tmp.tolist()
# print type(tmp)
#
# tmp = np.array(tmp)
# print type(tmp)

#
# import random
#
# a = [[random.random() for j in xrange(2)] for i in xrange(10)]
#
# b = sorted(a, key=lambda t: t[0])
# print a
# print b
# c = sorted(a, key=lambda t: t[1])
# print c



# img = load_img('../CarData/TrainImages/neg-0.pgm')
# print type(img)
# print img.size
# img1 = ToTensor()(img)
# print img1.size()
# print img1[0]
#
# import cv2
# import numpy as np
#
# img = cv2.imread('../CarData/cars_side_view/neg-0.pgm')
# print type(img)
# print img.shape
#
# img = ToTensor()(img)
# print img.size()
# print img[0]
# print img[1]
# print img[2]
#
# img = img[0].view(1, 40, 100)
# print img.size()
#
# ans = img[0]-img1[0]
#
# print sum(sum(abs(ans)))