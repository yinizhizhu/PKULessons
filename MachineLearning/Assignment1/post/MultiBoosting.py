from math import *
from time import clock
from sklearn import neighbors

start = clock()

class AdaBoost:
    def __init__(self, n = 9):
        self.n_features = 18
        self.clf_n = n
        self.clf = [neighbors.KNeighborsClassifier(n_neighbors = 6)
                                                   for i in xrange(self.clf_n)]

    def BootstrapSample(self):
        self.x = []
        self.y = []

        self.x_test = []
        self.y_test = []

        n = len(self.data_x)
        index = [0 for j in xrange(n)]
        
        n_train = 0
        while n_train < n*0.8:
            tmp = random.randint(0,n-1)
            if index[tmp] == 0:
                n_train += 1
                index[tmp] = 1
        
        for j in xrange(n):
            if index[j]:
                self.x.append(self.data_x[j])
                self.y.append(self.data_y[j])
            else:
                self.x_test.append(self.data_x[j])
                self.y_test.append(self.data_y[j])

        self.train_n = n_train
        self.test_n = n - n_train

    def judge(self, value):
        return self.verse_map[value]
        
    def Em(self, m):
        em = 0.0
        G_m = []
        for i in xrange(self.train_n):
            tmp = self.clf[m].predict(self.x[i])[0]
            G_m.append(tmp)
            if tmp != self.y[i]:
                em = em + self.weight[i]
        return [em, G_m]

    def main(self):
        self.a_m = []
        for m in xrange(self.clf_n):
            self.BootstrapSample()
            self.weight = [1.0/self.train_n for i in xrange(self.train_n)]
            self.clf[m].fit(self.x, self.y)
            [em, G_m] = self.Em(m)
            while em > 0.5:
                self.BootstrapSample()
                self.weight = [1.0/self.train_n for i in xrange(self.train_n)]
                self.clf[m].fit(self.x, self.y)
                [em, G_m] = self.Em(m)
            
            aerfa = 0.5*log((1-em)/em)
#            print aerfa
            self.a_m.append(aerfa)
#            print self.a_m
    
    def fit(self, x, y):
        self.data_x = x;
        self.data_y = y;
        print 'Fitting...'
        self.main()
        print 'Fitting finished!'
        
    def predict(self, x):
        ans = [0 for j in xrange(self.n_features)]
        for j in xrange(self.clf_n):
            k = self.clf[j].predict(x)[0]
            ans[k] += self.a_m[j]
        maxT = 0
        maxN = ans[0]
        for j in xrange(1, len(ans)):
            if ans[j] > maxN:
                maxN = ans[j]
                maxT = j
        return  maxT

class MultiBoosting():
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
        self.output_file = 'result\MultiBoosting.txt'
        self.out = open(self.output_file, 'w')
        
        self.attr_len = 6
        
        self.getMap()
        
        self.loadData()
        
        self.clf_n = n
        self.clf = [AdaBoost() for i in xrange(self.clf_n)]
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
        self.train_test = [0 for j in xrange(len(self.map))]

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
                while sum(index) < n*0.8:
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

    def trainingLoss(self, m):
        ans = 0
        for i in xrange(self.train_n[m]):
            if self.clf[m].predict(self.x[m][i]) == self.y[m][i]:
                ans += 1
        print 'Trainig accuracy is:', ans*1.0/self.train_n[m]
        print >> self.out, 'Trainig accuracy is:', ans*1.0/self.train_n[m]
        
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
                ans[self.clf[j].predict(self.x_test[0][i])] += 1
            else:
                ans[self.clf[j].predict(self.x[0][i])] += 1
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
    
    def partLoss(self):
        for j in xrange(self.clf_n):
            ans = 0
            for i in xrange(self.test_n[j]):
                if self.y_test[j][i] == self.clf[j].predict(self.x_test[j][i]):
                    ans += 1
            print 'The {0}th'.format(j+1), 'clf accuracy is: ', ans*1.0/self.test_n[j]
            print >> self.out, 'The {0}th'.format(j+1), 'clf accuracy is: ', ans*1.0/self.test_n[j]

a = MultiBoosting(6)
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