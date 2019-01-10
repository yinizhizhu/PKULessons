# from __future__ import print_function
import torch.optim as optim
import torch.nn.functional as F
import numpy as np
from torch.utils.data import DataLoader
from dataset import DatasetFromFolder
import shutil, os, random, time
from mot_model import *

from tensorboardX import SummaryWriter

torch.manual_seed(123)
np.random.seed(123)


def deleteDir(del_dir):
    shutil.rmtree(del_dir)


class GN():
    def __init__(self, lr=1e-5, batchs=8, cuda=True):
        '''
        :param tt: train_test
        :param tag: 1 - evaluation on testing data, 0 - without evaluation on testing data
        :param lr:
        :param batchs:
        :param cuda:
        '''
        self.device = torch.device("cuda" if cuda else "cpu")
        self.nEpochs = 99
        self.lr = lr
        self.batchsize = batchs
        self.numWorker = 4
        self.writer = SummaryWriter()

        self.show_process = 0   # interaction
        self.step_input = 1

        self.criterion = nn.CrossEntropyLoss()
        self.criterion = self.criterion.to(self.device)

        self.bestAcc = 0.0

    def updateNetwork(self):
        print '     Preparing the model...'
        self.Car = car().to(self.device)
        self.train_set = DatasetFromFolder()
        data_loader = DataLoader(dataset=self.train_set, num_workers=self.numWorker, batch_size=self.batchsize, shuffle=True)

        self.Car.train()
        self.optimizer1 = optim.Adam([
            {'params': self.Car.parameters()}],
            lr=self.lr)

        step = 0
        for epoch_i in xrange(1, self.nEpochs):
            t_loss = 0.0
            num = 0
            for iteration in enumerate(data_loader, 1):
                index, (e, gt) = iteration
                e = e.to(self.device)
                gt = gt.to(self.device)

                self.optimizer1.zero_grad()
                p = self.Car(e)
                # update the Ephi1
                loss = self.criterion(p, gt.squeeze(1))
                tmp = loss.item()
                t_loss += tmp
                loss.backward()
                self.optimizer1.step()

                step += 1
                num += e.size()[0]

                self.writer.add_scalar('Step_loss', tmp, step)
            self.writer.add_scalar('Total_loss', t_loss/num, epoch_i)
            print ' Evaluating %d...' % epoch_i
            self.evaluation(epoch_i)

    def saveModel(self):
        print 'Saving the Car model...'
        torch.save(self.Car, 'car_side_view_ReLU.pth')
        print 'Done!'

    def evaluation(self, epoch_i):
        with torch.no_grad():
            self.Car.eval()
            acc = 0
            n = len(self.train_set.validates)
            for iter in self.train_set.validates:
                e, gt = iter
                e = e.to(self.device)
                e1 = self.Car(e)
                tmp = F.softmax(e1)[0]
                # print tmp
                if tmp[1] > 0.5 and gt.item():
                    acc += 1
                elif tmp[1] < 0.5 and gt.item() == 0:
                    acc += 1
            acc = acc*1.0/n
            print '     Acc:', acc
            self.writer.add_scalar('Acc', acc, epoch_i)
            if acc > self.bestAcc:
                self.bestAcc = acc
                self.saveModel()

a = GN()
a.updateNetwork()
print a.bestAcc