import numpy as np
import random
from time import clock
import math
import matplotlib.pyplot as plt

start = clock()

class perceptron():
    def __init__(self):
        '''
            Just do this
        '''
        self.max_iter = 900
        
    def function(self, i):
        '''
        calculate the 'w*x + b'
            return the value calculated
        '''
        ans = self.x[i].dot(self.coef_.transpose())+self.intercept_
        return ans[0]
        
    def loss(self):
        for i in xrange(len(self.x)):
            if self.function(i)*self.y[i] < 0:
                return 1
        return 0

    def fit(self, x, y, weight, yet = 0.1):
        self.x = x #store the properties of the object
        self.y = y #store the kind of class
        
        self.weight = weight
        self.yeta = yet  #the ratio of learning
        
        self.coef_ = np.array([[random.random() for i in xrange(len(self.x[0]))]]) #the weight of each properties
        self.intercept_ = np.array([random.random()])    #the bias
        
        pre_loss = 0
        
        self.max_iter = 300
        iter_i = self.max_iter
        while iter_i:
            number = 0
            deltaw = np.array([0 for i in xrange(len(self.x[0]))])
            deltab = np.array([0])
            cur_loss = 0
            for i in xrange(len(self.x)):
                if self.function(i)*self.y[i] <= 0:
                    cur_loss += self.weight[i]
                    deltaw += self.y[i]*self.x[i]*self.weight[i]
                    deltab += self.y[i]*self.weight[i]
                    number += 1
            self.coef_[0] += self.yeta*deltaw/number
            self.intercept_ += self.yeta*deltab/number
            
            if pre_loss == cur_loss:
                iter_i = iter_i - 1
            else:
                pre_loss = cur_loss
                iter_i = self.max_iter

    def fitRandom(self, x, y, weight, yet = 0.1):
        self.x = x #store the properties of the object
        self.y = y #store the kind of class
        
        self.weight = weight
        self.yeta = yet  #the ratio of learning
        
        
        self.coef_ = np.array([[random.random() for i in xrange(len(self.x[0]))]]) #the weight of each properties
        self.intercept_ = np.array([random.random()])    #the bias
        
        iter_i = self.max_iter
        while iter_i:
            index = []
            for i in xrange(len(self.x)):
                if self.function(i)*self.y[i] <= 0:
                    index.append(i)
                    
            if len(index):
                i = index[random.randint(0, len(index)-1)]
                self.coef_[0] += self.yeta*self.y[i]*self.x[i]*self.weight[i]
                self.intercept_ += self.yeta*self.y[i]*self.weight[i]
            
            iter_i = iter_i - 1

class AdaBoost():
    def __init__(self, n):
        self.sample_n = 200
        self.weight = [1.0/self.sample_n for i in xrange(self.sample_n)]
        
        self.a_m = []
        self.clf_n = n
        self.clf = [perceptron() for i in xrange(self.clf_n)]
        
        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class
        
        self.generateData()
        self.readData()
        
    def generateData(self):
        '''
            generate the source data:(convinient to get access to the data)
                the separating hyperplane is 'y=x'
                output the data into text file
        '''
        out = open('data.txt', 'w')
        for i in xrange(90):
            print >> out, '{0} {1} {2}'.format(i+random.random(), 
                        i+random.uniform(1, 9)+1, 1)
        
        for i in xrange(10):
            a = random.uniform(1, 100)
            print >> out, '{0} {1} {2}'.format(a+random.random(), 
                        a+random.uniform(1, 9)+1, -1)
        
        for i in xrange(90):
            print >> out, '{0} {1} {2}'.format(i+random.random(), 
                        i-random.uniform(1, 9)-1, -1)
                        
        for i in xrange(10):
            a = random.uniform(1, 100)
            print >> out, '{0} {1} {2}'.format(a+random.random(), 
                        a-random.uniform(1, 9)-1, 1)
        
        out.close()
        
    def readData(self):
        '''
            readData: 
                get the data in the source data
        '''
        read = open('data.txt', 'r')
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            self.x.append([float(one[0]), float(one[1])])
            self.y.append(int(one[2]))
        read.close()
        
        #change the type of self.x into np.array which is better for operation
        #it's same with self.y
        self.x = np.array(self.x)
        self.y= np.array(self.y)
    
    def sign(self, value):
        if value > 0:
            return 1
        return -1
    
    def G(self, m, i):
        ans = self.sign(self.x[i].dot(self.clf[m].coef_.transpose())
                +self.clf[m].intercept_)
        if ans > 0:
            return 1
        return -1
    
    def Em(self, m):
        em = 0.0
        for i in xrange(self.sample_n):
            if self.G(m, i) != self.y[i]:
                em = em + self.weight[i]
        return em
    
    def Aerfa(self, m):
#        print m, 
        em = self.Em(m)
#        print em
        return 0.5*math.log((1-em)/em)
    
    def step(self, m):
        self.basicLearn(m)
        aerfa = self.Aerfa(m)
        z = 0
        for i in xrange(self.sample_n):
            tmp = self.weight[i]*math.exp(-aerfa*self.y[i]*self.G(m, i))
            self.weight[i] = tmp
            z = z+tmp
        for i in xrange(self.sample_n):
            self.weight[i] /= z
#        print aerfa
        self.a_m.append(aerfa)

    def basicLearn(self, m):
        self.clf[m].max_iter = 1000+m*1000
#        self.clf[m].fit(self.x, self.y, self.weight)
        self.clf[m].fitRandom(self.x, self.y, self.weight)
        
    
    def main(self):
        for i in xrange(self.clf_n):
            self.step(i)
    
    def partG(self, m, i):
        return self.sign(self.G(m, i))
            
    def partLoss(self, m):
        ans = 0
        for i in xrange(self.sample_n):
            if self.partG(m, i) != self.y[i]:
                ans = ans+1
        return ans
    
    def finalG(self, i):
        ans = 0
        for j in xrange(self.clf_n):
            ans = ans + self.a_m[j]*self.G(j, i)
        return self.sign(ans)
    
    def finalLoss(self):
        ans = 0
        for i in xrange(self.sample_n):
            if self.finalG(i) != self.y[i]:
                ans = ans+1
        return ans

    def drawLine(self, y1, y2, mode):
        gap = (y2-y1)/100.0
        t = []
        for i in xrange(101):
            t.append(y1)
            y1 += gap
        plt.plot(t, mode)
    
    def drawData(self):
#        self.drawLine(0, 101, 'r') #draw the x1+x2=0
        for i in xrange(200):
            if self.y[i] == 1:
                plt.plot(self.x[i][0], self.x[i][1], 'ro')
            else:
                plt.plot(self.x[i][0], self.x[i][1], 'g^')

#        t = []
        for j in xrange(self.sample_n):
            tmp = 0
            for i in xrange(self.clf_n):
                tmp += self.G(i, j)*self.weight[j]
                h = -self.clf[i].intercept_[0]/self.clf[i].coef_[0][1]
                t = -self.clf[i].coef_[0][0]/self.clf[i].coef_[0][1]*101+h
                self.drawLine(h, t, 'b')
#            t.append(tmp)
        plt.plot(t, 'b')
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.show()

#out = open('result.txt', 'w')

min_loss = 200
max_loss = 0

#n = random.randint(1, 9)
man = AdaBoost(6)
man.main()
ans = man.finalLoss()
if ans > max_loss:
    max_loss = ans
if ans < min_loss:
    min_loss = ans
print ans

#print >> out, n, ans
man.drawData()

#print >> out, min_loss, max_loss
#out.close()

end = clock()
print "The total time is: ", end-start