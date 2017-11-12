from math import *
from time import clock
from sklearn import neighbors

start = clock()

class AdaBoost():
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
        self.attr_len = 6
        
        self.getMap()
        
        self.loadData()
        
        self.clf_n = n
        self.clf = [neighbors.KNeighborsClassifier(n_neighbors = 6)
                                                   for i in xrange(self.clf_n)]

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
        self.x = []
        self.y = []
        self.train_n = 0

        self.x_test = []
        self.y_test = []
        self.test_n = 0

        for i in xrange(len(self.map)):
            n = len(self.data[i])
            index = [0 for j in xrange(n)]
            while sum(index) < n*0.8:
                index[random.randint(0,n-1)] = 1
            
            for j in xrange(n):
                if index[j]:
                    self.x.append(self.data[i][j])
                    self.y.append(i)
                else:
                    self.x_test.append(self.data[i][j])
                    self.y_test.append(i)
            n_train = sum(index)
            self.train_n += n_train
            self.test_n += n - n_train

    def loadData(self):
        data = open(self.input_file, 'r')
        self.data = [[] for i in xrange(len(self.map))]
        for line in data.readlines():
            words = line.strip('\n').split(',')
            self.insertData(words)
        data.close()

    def I(self, value):
        if value != 0:
            return 1
        return 0

    def judge(self, value):
        return self.verse_map[value]

    def G(self, m, i):
        ans =  self.clf[m].predict(self.x_test[i])
        if ans[0] > 17:
            print ans[0] - self.y_test[i]
        return ans[0]
    def Em(self, m):
        em = 0.0
        G_m = []
        for i in xrange(self.test_n):
            tmp = self.G(m, i)
            G_m.append(tmp)
            if tmp != self.y_test[i]:
                em = em + self.weight[i]
        return [em, G_m]

    def main(self):
        self.a_m = []
        for m in xrange(self.clf_n):
            s = clock()
            
            self.BootstrapSample()
            self.weight = [1.0/self.test_n for i in xrange(self.test_n)]
            self.clf[m].fit(self.x, self.y)
            [em, G_m] = self.Em(m)
            while em > 0.5:
                self.BootstrapSample()
                self.weight = [1.0/self.test_n for i in xrange(self.test_n)]
                self.clf[m].fit(self.x, self.y)
                [em, G_m] = self.Em(m)
            
            aerfa = 0.5*log((1-em)/em)
            z = 0
            for i in xrange(self.test_n):
                if self.y_test[i] == G_m[i]:
                    tmp = self.weight[i]*exp(-aerfa)
                else:
                    tmp = self.weight[i]*exp(aerfa)
                self.weight[i] = tmp
                z = z+tmp
            for i in xrange(self.test_n):
                self.weight[i] /= z
    #        print aerfa
            self.a_m.append(aerfa)
            e = clock()
#            print self.a_m
            print "The step {0}, time consuming: {1}".format(m+1, e-s)

    def finalG(self, i):
        ans = [0 for j in xrange(len(self.map))]
        for j in xrange(self.clf_n):
            k = self.G(j, i)
            ans[k] += self.a_m[j]
        maxT = 0
        maxN = ans[0]
        for j in xrange(1, len(ans)):
            if ans[j] > maxN:
                maxN = ans[j]
                maxT = j
        return  maxT

    def finalLoss(self):
        ans = 0
        for i in xrange(self.test_n):
            if self.finalG(i) == self.y_test[i]:
                ans = ans+1
        print 'Toatal accuracy is: ', ans*1.0/self.test_n
    
    def partLoss(self):
        for j in xrange(self.clf_n):
            ans = 0
            for i in xrange(self.test_n):
                if self.y_test[i] == self.G(j, i):
                    ans += 1
            print '{0}th'.format(j+1), 'clf accuracy is:', ans*1.0/self.test_n

a = AdaBoost(24)
#a.showKind('zero')
#a.showKind('one')
#a.showKind('two')

a.main()

print a.a_m

a.partLoss()

a.finalLoss()

end = clock()
print "The total time consuming: ", end-start

#
#tmp = neighbors.KNeighborsClassifier(algorithm='auto')
#print tmp.__doc__