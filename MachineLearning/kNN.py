import numpy as np
import random, math
from time import clock
import matplotlib.pyplot as plt

start = clock()

class employee:
    pass

class knn():
    def __init__(self, k):
        '''
        w1, w2 - the weights
        bias - the bias
        yet - the ratio of learning
        '''
        
        self.k = k
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
        for i in xrange(30):
            print >> out, '{0} {1} {2}'.format(random.uniform(1, 9), 
                        random.uniform(1, 9), 1)
        
        for i in xrange(30):
            print >> out, '{0} {1} {2}'.format(99+random.uniform(1, 9), 
                        random.uniform(1, 9), 2)
                        
        for i in xrange(30):
            print >> out, '{0} {1} {2}'.format(99+random.uniform(1, 9), 
                        99+random.uniform(1, 9), 3)
                        
        for i in xrange(30):
            print >> out, '{0} {1} {2}'.format(random.uniform(1, 9), 
                        99+random.uniform(1, 9), 4)
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
    
    def drawLine(self, y1, y2, mode):
        gap = (y2-y1)/100.0
        t = []
        for i in xrange(101):
            t.append(y1)
            y1 += gap
        plt.plot(t, mode)
    
    def drawData(self):
        for i in xrange(120):
            if self.y[i] == 1:
                plt.plot(self.x[i][0], self.x[i][1], 'ro')
            elif self.y[i] == 2:
                plt.plot(self.x[i][0], self.x[i][1], 'g^')
            elif self.y[i] == 3:
                plt.plot(self.x[i][0], self.x[i][1], 'b*')
            else:
                plt.plot(self.x[i][0], self.x[i][1], 'k+')
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.show()
    
    def dis(self, node, i):
        ans = 0
        for j in xrange(len(node)):
            delta = self.x[i][j]-node[j]
            ans = ans + delta*delta
        return math.sqrt(ans)
    
    def getMost(self, ans):
        res = [0, 0, 0, 0, 0]
        for i in xrange(len(ans)):
            res[ans[i]] = res[ans[i]] + 1;
        maxT = 1
        maxN = res[1]
        for i in xrange(2, len(res)):
            if res[i] > maxN:
                maxT = i
                maxN = res[i]
        return maxT
    
    def doIt(self, node):
        distance = []
        for i in xrange(len(self.y)):
            tmp = employee()
            tmp.type = self.y[i]
            tmp.dis = self.dis(node, i)
            distance.append(tmp)
        
        distance.sort(key = lambda d:d.dis)
        ans = []
        for i in xrange(self.k):
            ans.append(distance[i].type)
            
        tag = self.getMost(ans)
        if tag == 1:
            kind = 'ro'
        elif tag == 2:
            kind = 'g^'
        elif tag == 3:
            kind = 'b*'
        else:
            kind = 'k+'
        print ans, tag, kind
        plt.plot(node[0], node[1], kind)
        plt.show()
        
    def doItIncrease(self, node):
        distance = []
        for i in xrange(len(self.y)):
            tmp = employee()
            tmp.type = self.y[i]
            tmp.dis = self.dis(node, i)
            distance.append(tmp)
        
        distance.sort(key = lambda d:d.dis)
        ans = []
        for i in xrange(self.k):
            ans.append(distance[i].type)
            
        tag = self.getMost(ans)
        if tag == 1:
            kind = 'ro'
        elif tag == 2:
            kind = 'g^'
        elif tag == 3:
            kind = 'b*'
        else:
            kind = 'k+'
        print ans, tag, kind
        plt.plot(node[0], node[1], kind)
        plt.show()
        #add the new one into the basic classes
        self.x.append(node)
        self.y.append(tag)

tmp = knn(4)
tmp.drawData()

for i in xrange(30):
    tmp.doIt([random.uniform(30, 81), random.uniform(30, 81)])

end = clock()
print "The total time is: ", end-start