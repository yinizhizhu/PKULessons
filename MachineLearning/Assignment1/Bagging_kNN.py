import random
from math import *
from time import clock
from sklearn import neighbors

start = clock()

class Bagging():
    def __init__(self, n):
        '''
        The source data set
            Number of Attributes:
                There are six attribute variables and one class variable.

            Class Distribution:
               draw       2796
               zero         27
               one          78
               two         246
               three        81
               four        198
               five        471
               six         592
               seven       683
               eight      1433
               nine       1712
               ten        1985
               eleven     2854
               twelve     3597
               thirteen   4194
               fourteen   4553
               fifteen    2166
               sixteen     390
            
               Total     28056
        '''
        
        self.input_file = 'data\krkopt.data'
        self.output_file = 'result\Bagging.txt'
        self.out = open(self.output_file, 'w')
        
        self.attr_len = 6
        
        self.getMap()
        
        self.loadData()
        
        self.clf_n = n
        self.clf = [neighbors.KNeighborsClassifier(n_neighbors = 6)
                                                   for i in xrange(self.clf_n)]

        self.BootstrapSample()

    def getMap(self):
        self.map = dict()
        self.verse_map = dict()
        read = open('map.txt', 'r')
        i = 0
        for line in read.readlines():
            one = line.strip('\n')
            if len(one) > 1:
                self.map[one] = i
                self.verse_map[i] = one
                i = i+1
        read.close()

    def insertData(self, words):
        kind = words[self.attr_len]
        tmp = [ord(words[i])/256.0 for i in xrange(self.attr_len)]
        self.data[self.map[kind]].append(tmp)

    def showKind(self, kind):
        if type(kind) == str:
            kind = self.map[kind]
        n = len(self.data[kind])
        print 'The number of {0} is {1}: '.format(kind, n)
        for i in xrange(len(self.data[kind])):
            print self.data[kind][i]
        
    def BootstrapSample(self):
        self.x = [[] for i in xrange(self.clf_n)]
        self.y = [[] for i in xrange(self.clf_n)]
        self.train_n = [0 for i in xrange(self.clf_n)]

        self.x_test = [[] for i in xrange(self.clf_n)]
        self.y_test = [[] for i in xrange(self.clf_n)]
        self.test_n = [0 for i in xrange(self.clf_n)]

        for k in xrange(self.clf_n):
            for i in xrange(len(self.map)):
                n = len(self.data[i])
                index = [0 for j in xrange(n)]
                while sum(index) < n*0.64:
                    index[random.randint(0,n-1)] = 1
                
                for j in xrange(n):
                    if index[j]:
                        self.x[k].append(self.data[i][j])
                        self.y[k].append(i)
                    else:
                        self.x_test[k].append(self.data[i][j])
                        self.y_test[k].append(i)
                n_train = sum(index)
                self.train_n[k] += n_train
                self.test_n[k] += n - n_train

    def loadData(self):
        data = open(self.input_file, 'r')
        self.data = [[] for i in xrange(len(self.map))]
        for line in data.readlines():
            words = line.strip('\n').split(',')
            self.insertData(words)
        data.close()

    def main(self):
        for m in xrange(self.clf_n):
            s = clock()
            self.clf[m].fit(self.x[m], self.y[m])
            self.trainingLoss(m)
            e = clock()
            print "The step time consuming: ", e-s
            print >> self.out, "The step time consuming: ", e-s

    def finalG(self, i, tag):
        ans = [0 for j in xrange(len(self.map))]
        for j in xrange(self.clf_n):
            if tag:
                ans[self.clf[j].predict(self.x_test[0][i])[0]] += 1
            else:
                ans[self.clf[j].predict(self.x[0][i])[0]] += 1
        maxT = 0
        maxN = ans[0]
        for j in xrange(1, len(ans)):
            if ans[j] > maxN:
                maxN = ans[j]
                maxT = j
        return  maxT

    def finalLoss(self):
        ans = 0
        for i in xrange(self.test_n[0]):
            tmp = self.finalG(i, 1)
            if tmp == self.y_test[0][i]:
                ans = ans+1
        print 'The total accuracy for test sets is: ', ans*1.0/self.test_n[0]
        print >> self.out, 'The total accuracy for test sets is: ', ans*1.0/self.test_n[0]
        
        ans = 0
        for i in xrange(self.train_n[0]):
            tmp = self.finalG(i, 0)
            if tmp == self.y[0][i]:
                ans = ans+1
        print 'The total accuracy for train sets is: ', ans*1.0/self.train_n[0]
        print >> self.out, 'The total accuracy for train sets is: ', ans*1.0/self.train_n[0]
    
    def trainingLoss(self, m):
        ans = 0
        for i in xrange(self.train_n[m]):
            if self.clf[m].predict(self.x[m][i]) == self.y[m][i]:
                ans += 1
        print 'Trainig accuracy is:', ans*1.0/self.train_n[m]
        print >> self.out, 'Trainig accuracy is:', ans*1.0/self.train_n[m]

    def partLoss(self):
        testL = 0
        trainL= 0
        for j in xrange(self.clf_n):
            ans = 0
            for i in xrange(self.test_n[j]):
                if self.y_test[j][i] == self.clf[j].predict(self.x_test[j][i]):
                    ans += 1
            print 'The {0}th'.format(j+1), 'clf accuracy is: ', ans*1.0/self.test_n[j],
            print >> self.out, 'The {0}th'.format(j+1), 'clf accuracy is: ', ans*1.0/self.test_n[j],
            
            testL += ans*1.0/self.test_n[j]
            
            ans = 0
            for i in xrange(self.train_n[j]):
                if self.y[j][i] == self.clf[j].predict(self.x[j][i]):
                    ans += 1
            print ans*1.0/self.train_n[j]
            print >> self.out, ans*1.0/self.train_n[j]
            
            trainL += ans*1.0/self.train_n[j]
            
        print "Average accuracy is: ", testL/self.clf_n, trainL/self.clf_n

a = Bagging(6)
#a.showKind('zero')
#a.showKind('one')
#a.showKind('two')

a.main()

a.partLoss()

a.finalLoss()

print >> a.out, "The total time consuming: ", clock()-start
a.out.close()

end = clock()
print "The total time consuming: ", end-start

#
#tmp = neighbors.KNeighborsClassifier(algorithm='auto')
#print tmp.__doc__