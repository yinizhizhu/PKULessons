from math import *

class employee:
    pass

class knn():
    def __init__(self, k):
        self.k = k
        

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
        
        self.train_test = [0 for i in xrange(len(self.map))]
        self.AdaSample()
        
        self.weight = [1.0/self.train_n for i in xrange(self.train_n)]
        
        
        self.clf_n = n
        self.clf = [i+1 for i in xrange(self.clf_n)]
        
    
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
        tmp = [ord(words[i])/256.0 for i in xrange(self.attr_len-1)]
        self.data[self.map[kind]].append(tmp)
    
    def showKind(self, kind):
        if type(kind) == str:
            kind = self.map[kind]
        n = len(self.data[kind])
        print 'The number of {0} is {1}: '.format(kind, n)
        for i in xrange(len(self.data[kind])):
            print self.data[kind][i]
    
    def AdaSample(self):
        self.x = []
        self.y = []
        self.train_n = 0
        
        self.x_test = []
        self.y_test = []
        self.test_n = 0

        for i in xrange(len(self.map)):
            n = len(self.data[i])
            n_train = int(n*0.5)
            self.train_test[i] = n_train
            
            for j in xrange(n_train):
                self.x.append(self.data[i][j])
            for j in xrange(n_train):
                self.y.append(i)
            self.train_n += n_train
            
            for j in xrange(n_train, n):
                self.x_test.append(self.data[i][j])
            for j in xrange(n_train, n):
                self.y_test.append(i)
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
        return self.fit(self.x_test[i], self.clf[m])
    
    def Em(self, m):
        em = 0.0
        for i in xrange(self.test_n):
            if self.G(m, i) != self.y_test[i]:
                em = em + self.weight[i]
        return em
        
    def Aerfa(self, m):
#        print m, 
        em = self.Em(m)
#        print em
        return 0.5*log((1-em)/em)
        
    def step(self, m):
        aerfa = self.Aerfa(m)
        z = 0
        for i in xrange(self.sample_n):
            tmp = self.weight[i]*math.exp(-aerfa*self.y_test[i]*self.G(m, i))
            self.weight[i] = tmp
            z = z+tmp
        for i in xrange(self.sample_n):
            self.weight[i] /= z
#        print aerfa
        self.a_m.append(aerfa)

    def main(self):
        for i in xrange(self.clf_n):
            self.step(i)
    
#    def partG(self, m, i):
#        return self.judge(self.G(m, i))
#            
#    def partLoss(self, m):
#        ans = 0
#        for i in xrange(self.test_n):
#            if self.partG(m, i) != self.y[i]:
#                ans = ans+1
#        return ans
    
    def finalG(self, i):
        ans = [0 for j in xrange(len(self.map))]
        for j in xrange(self.clf_n):
            ans[self.G(j, i)] += self.a_m[j]
        maxT = 0
        maxN = ans[0]
        for j in xrange(1, len(self.ans)):
            if ans[j] > maxN:
                maxN = ans[j]
                maxT = j
        return maxT
    
    def finalLoss(self):
        ans = 0
        for i in xrange(self.test_n):
            tmp = self.finalG(i)
            if tmp != self.y_test[i]:
                print self.x_test[i], tmp, self.y_test[i]
                ans = ans+1
        return ans
    
    '''
        For the kNN
    '''
    def dis(self, node, i):
        ans = 0
        for j in xrange(len(node)):
            delta = self.x[i][j]-node[j]
            ans = ans + delta*delta
        return sqrt(ans)
    
    def getMost(self, ans):
        res = [0 for i in xrange(len(self.map))]
        for i in xrange(len(ans)):
            res[ans[i]] = res[ans[i]] + 1
        maxT = 0
        maxN = res[0]
        for i in xrange(1, len(res)):
            if res[i] > maxN:
                maxT = i
                maxN = res[i]
        return maxT
    
    def fit(self, node, k):
        distance = []
#        print node
        for i in xrange(len(self.y)):
            tmp = employee()
            tmp.type = self.y[i]
            tmp.dis = self.dis(node, i)
            distance.append(tmp)
        
        distance.sort(key = lambda d:d.dis)
        ans = []
        for i in xrange(k):
            ans.append(distance[i].type)
            
        return self.getMost(ans)

a = AdaBoost(3)
a.showKind('zero')
a.showKind('one')
a.showKind('two')
a.main()
print a.finalLoss()