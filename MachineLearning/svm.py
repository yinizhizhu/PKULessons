from sklearn import svm
import numpy as np
import random
from time import clock
import matplotlib.pyplot as plt

start = clock()

class perceptron():
    def __init__(self, w1, w2, bias, yet):
        '''
        w1, w2 - the weights
        bias - the bias
        yet - the ratio of learning
        '''
        print w1, w2, bias
        self.clf = svm.LinearSVC()
        
        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class
        
        self.generateData()
        self.readData()
        
        self.doIt()
        
    def generateData(self):
        '''
        generate the source data:(convinient to get access to the data)
            the separating hyperplane is 'y=x'
            output the data into text file
        '''
        out = open('data.txt', 'w')
        for i in xrange(100):
            print >> out, '{0} {1} {2}'.format(i+random.random(), 
                        i+random.uniform(1, 9)+1, 1)
        
        for i in xrange(100):
            print >> out, '{0} {1} {2}'.format(i+random.random(), 
                        i-random.uniform(1, 9)-1, -1)
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
        h = -self.clf.tol/self.clf.coef_[0][1]
        t = -self.clf.coef_[0][0]/self.clf.coef_[0][1]*101+h
        self.drawLine(h, t, 'b')
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.show()
        
    def doIt(self):
        self.clf.fit(self.x, self.y)
        print self.clf.predict([[-0.8, -1]])
        print self.clf.class_weight
        print self.clf.decision_function
        print self.clf.loss
        print self.clf.C
        print self.clf.coef_
        print self.clf.penalty
        print self.clf.tol

tmp = perceptron(random.random(), random.random(), random.random(), 0.01)
tmp.drawData()

end = clock()
print "The total time is: ", end-start