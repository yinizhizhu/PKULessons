from sklearn import linear_model, tree, neighbors, svm
from sklearn.neighbors.nearest_centroid import NearestCentroid
from sklearn.ensemble import BaggingClassifier, AdaBoostClassifier, RandomForestClassifier
from sklearn.naive_bayes import GaussianNB
import numpy as np
import random
from math import *
import sys
from time import clock
from sklearn.externals import joblib

start = clock()

N = [12, 12]

File = ['trainBinary.txt', 'trainMulti.txt']


classifierName = ["SGD", "decisionTree", "knn", "gaussianNB", "svm_",
	"bagging_", "randomforest", "svc", "adaboost_", 'centroid', 'maxEntropy' ]

classifierName2 = ["decisionTree", "knn", "svm_", "randomforest", "adaboost_", 'svc']

class SGD():
    def __init__(self, bm):
        self.input = File[bm]
        self.clf = linear_model.SGDClassifier(max_iter = 390)

        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class

        self.readData(bm)

        print 'SGD Fitting...'
        self.clf.fit(self.x, self.y)
        print 'Done!'

    def readData(self, bm):
        '''
        readData:
            get the data in the source data
        '''
        read = open(self.input, 'r')
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[bm]):
                tmp.append(float(one[i]))
            self.x.append(tmp)
            self.y.append(int(one[N[bm]]))
        read.close()
        self.x = np.array(self.x)
        self.y= np.array(self.y)

    def doIt(self):
        accuracy = 0
        for i in xrange(len(self.y)):
            if self.y[i] == self.clf.predict(self.x[i]):
                accuracy += 1
        print accuracy*1.0/len(self.y)
        return accuracy*1.0/len(self.y)

    def predict(self, x):
        return self.clf.predict(x)

class decisionTree():
    def __init__(self, bm):
        self.input = File[bm]
        self.clf = tree.DecisionTreeClassifier()
        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class

        self.readData(bm)

        print 'decisionTree Fitting...'
        self.clf.fit(self.x, self.y)
        print 'Done!'

    def readData(self, bm):
        '''
        readData:
            get the data in the source data
        '''
        read = open(self.input, 'r')
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[bm]):
                tmp.append(float(one[i]))
            self.x.append(tmp)
            self.y.append(int(one[N[bm]]))
        read.close()
        self.x = np.array(self.x)
        self.y= np.array(self.y)

    def doIt(self):
        accuracy = 0
        for i in xrange(len(self.y)):
            if self.y[i] == self.clf.predict(self.x[i]):
                accuracy += 1
        print accuracy*1.0/len(self.y)
        return accuracy*1.0/len(self.y)

    def predict(self, x):
        return self.clf.predict(x)

class knn():
    def __init__(self, bm):
        self.input = File[bm]
        self.clf = neighbors.KNeighborsClassifier(n_neighbors=1)
#        self.clf = neighbors.KNeighborsClassifier(n_neighbors=9)
        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class

        self.readData(bm)

        print 'knn Fitting...'
        self.clf.fit(self.x, self.y)
        print 'Done!'

    def readData(self, bm):
        '''
        readData:
            get the data in the source data
        '''
        read = open(self.input, 'r')
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[bm]):
                tmp.append(float(one[i]))
            self.x.append(tmp)
            self.y.append(int(one[N[bm]]))
        read.close()
        self.x = np.array(self.x)
        self.y= np.array(self.y)

    def doIt(self):
        accuracy = 0
        for i in xrange(len(self.y)):
            if self.y[i] == self.clf.predict(self.x[i]):
                accuracy += 1
        print accuracy*1.0/len(self.y)
        return accuracy*1.0/len(self.y)

    def predict(self, x):
        return self.clf.predict(x)

class gaussianNB():
    def __init__(self, bm):
        self.input = File[bm]
        self.clf = GaussianNB()
#        self.clf = neighbors.KNeighborsClassifier(n_neighbors=9)
        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class

        self.readData(bm)

        print 'gaussianNB Fitting...'
        self.clf.fit(self.x, self.y)
        print 'Done!'

    def readData(self, bm):
        '''
        readData:
            get the data in the source data
        '''
        read = open(self.input, 'r')
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[bm]):
                tmp.append(float(one[i]))
            self.x.append(tmp)
            self.y.append(int(one[N[bm]]))
        read.close()
        self.x = np.array(self.x)
        self.y= np.array(self.y)

    def doIt(self):
        accuracy = 0
        for i in xrange(len(self.y)):
            if self.y[i] == self.clf.predict(self.x[i]):
                accuracy += 1
        print accuracy*1.0/len(self.y)
        return accuracy*1.0/len(self.y)

    def predict(self, x):
        return self.clf.predict(x)

class svm_():
    def __init__(self, bm):
        self.input = File[bm]
        self.clf = svm.LinearSVC()
        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class

        self.readData(bm)

        print 'svm_ Fitting...'
        self.clf.fit(self.x, self.y)
        print 'Done!'

    def readData(self, bm):
        '''
        readData:
            get the data in the source data
        '''
        read = open(self.input, 'r')
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[bm]):
                tmp.append(float(one[i]))
            self.x.append(tmp)
            self.y.append(int(one[N[bm]]))
        read.close()
        self.x = np.array(self.x)
        self.y= np.array(self.y)

    def doIt(self):
        accuracy = 0
        for i in xrange(len(self.y)):
            if self.y[i] == self.clf.predict(self.x[i]):
                accuracy += 1
        print accuracy*1.0/len(self.y)
        return accuracy*1.0/len(self.y)

    def predict(self, x):
        return self.clf.predict(x)

class bagging_():
    def __init__(self, bm):
        self.input = File[bm]
        self.clf = BaggingClassifier(neighbors.KNeighborsClassifier(), max_samples=0.5, max_features=0.5)
        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class

        self.readData(bm)

        print 'bagging_ Fitting...'
        self.clf.fit(self.x, self.y)
        print 'Done!'

    def readData(self, bm):
        '''
        readData:
            get the data in the source data
        '''
        read = open(self.input, 'r')
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[bm]):
                tmp.append(float(one[i]))
            self.x.append(tmp)
            self.y.append(int(one[N[bm]]))
        read.close()
        self.x = np.array(self.x)
        self.y= np.array(self.y)

    def doIt(self):
        accuracy = 0
        for i in xrange(len(self.y)):
            if self.y[i] == self.clf.predict(self.x[i]):
                accuracy += 1
        print accuracy*1.0/len(self.y)
        return accuracy*1.0/len(self.y)

    def predict(self, x):
        return self.clf.predict(x)

class randomforest():
    def __init__(self, bm):
        self.input = File[bm]
        self.clf = RandomForestClassifier(n_estimators=10)
        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class

        self.readData(bm)

        print 'randomforest Fitting...'
        self.clf.fit(self.x, self.y)
        print 'Done!'

    def readData(self, bm):
        '''
        readData:
            get the data in the source data
        '''
        read = open(self.input, 'r')
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[bm]):
                tmp.append(float(one[i]))
            self.x.append(tmp)
            self.y.append(int(one[N[bm]]))
        read.close()
        self.x = np.array(self.x)
        self.y= np.array(self.y)

    def doIt(self):
        accuracy = 0
        for i in xrange(len(self.y)):
            if self.y[i] == self.clf.predict(self.x[i]):
                accuracy += 1
        print accuracy*1.0/len(self.y)
        return accuracy*1.0/len(self.y)

    def predict(self, x):
        return self.clf.predict(x)

class adaboost_():
    def __init__(self, bm):
        self.input = File[bm]
        self.clf = AdaBoostClassifier(n_estimators=100)
        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class

        self.readData(bm)

        print 'adaboost_ Fitting...'
        self.clf.fit(self.x, self.y)
        print 'Done!'

    def readData(self, bm):
        '''
        readData:
            get the data in the source data
        '''
        read = open(self.input, 'r')
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[bm]):
                tmp.append(float(one[i]))
            self.x.append(tmp)
            self.y.append(int(one[N[bm]]))
        read.close()
        self.x = np.array(self.x)
        self.y= np.array(self.y)

    def doIt(self):
        accuracy = 0
        for i in xrange(len(self.y)):
            if self.y[i] == self.clf.predict(self.x[i]):
                accuracy += 1
        print accuracy*1.0/len(self.y)
        return accuracy*1.0/len(self.y)

    def predict(self, x):
        return self.clf.predict(x)

class centroid():
    def __init__(self, bm):
        self.input = File[bm]
        self.clf = NearestCentroid()
        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class

        self.readData(bm)

        print 'centroid Fitting...'
        self.clf.fit(self.x, self.y)
        print 'Done!'

    def readData(self, bm):
        '''
        readData:
            get the data in the source data
        '''
        read = open(self.input, 'r')
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[bm]):
                tmp.append(float(one[i]))
            self.x.append(tmp)
            self.y.append(int(one[N[bm]]))
        read.close()
        self.x = np.array(self.x)
        self.y= np.array(self.y)

    def doIt(self):
        accuracy = 0
        for i in xrange(len(self.y)):
            if self.y[i] == self.clf.predict(self.x[i]):
                accuracy += 1
        print accuracy*1.0/len(self.y)
        return accuracy*1.0/len(self.y)

    def predict(self, x):
        return self.clf.predict(x)

class maxEntropy():
    def __init__(self, bm):
        self.input = File[bm]
        self.clf = linear_model.LogisticRegression()
        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class

        self.readData(bm)

        print 'maxEntropy Fitting...'
        self.clf.fit(self.x, self.y)
        print 'Done!'

    def readData(self, bm):
        '''
        readData:
            get the data in the source data
        '''
        read = open(self.input, 'r')
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[bm]):
                tmp.append(float(one[i]))
            self.x.append(tmp)
            self.y.append(int(one[N[bm]]))
        read.close()
        self.x = np.array(self.x)
        self.y= np.array(self.y)

    def doIt(self):
        accuracy = 0
        for i in xrange(len(self.y)):
            if self.y[i] == self.clf.predict(self.x[i]):
                accuracy += 1
        print accuracy*1.0/len(self.y)
        return accuracy*1.0/len(self.y)

    def predict(self, x):
        return self.clf.predict(x)

class svc():
    def __init__(self, bm):
        self.input = File[bm]
        self.clf = svm.SVC()
        self.x = [] #store the properties of the object
        self.y = [] #store the kind of class

        self.readData(bm)

        print 'svc Fitting...'
        self.clf.fit(self.x, self.y)
        print 'Done!'

    def readData(self, bm):
        '''
        readData:
            get the data in the source data
        '''
        read = open(self.input, 'r')
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[bm]):
                tmp.append(float(one[i]))
            self.x.append(tmp)
            self.y.append(int(one[N[bm]]))
        read.close()
        self.x = np.array(self.x)
        self.y= np.array(self.y)

    def doIt(self):
        accuracy = 0
        for i in xrange(len(self.y)):
            if self.y[i] == self.clf.predict(self.x[i]):
                accuracy += 1
        print accuracy*1.0/len(self.y)
        return accuracy*1.0/len(self.y)

    def predict(self, x):
        return self.clf.predict(x)

class classifier():
    def __init__(self, b, m):
        self.binary =  b
        self.multi = m

        self.xb = [] #store the properties of the object
        self.xm = []

    def readData(self, light):
        '''
        readData:
            get the data in the source data
        '''
        targetFM = 'devFeatureM.txt'
        targetFB = 'devFeatureB.txt'
        if light == 0:
            targetFM = 'testFeatureM.txt'
            targetFB = 'testFeatureB.txt'
        readb = open(targetFB, 'r')
        for line in readb.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[0]):
                tmp.append(float(one[i]))
            self.xb.append(tmp)
        readb.close()
        readm = open(targetFM, 'r')
        for line in readm.readlines():
            one = line.strip('\n').split(' ')
            tmp = list()
            for i in xrange(N[1]):
                tmp.append(float(one[i]))
            self.xm.append(tmp)
        readm.close()

        #change the type of self.x into np.array which is better for operation
        #it's same with self.y
        self.xb = np.array(self.xb)
        self.xm = np.array(self.xm)

    def doIt(self, x, y, savetime, light):
        self.readData(light)
        fileOut ='devLabel/demoFeatureDevLabel_'
        if light == 0:
            fileOut = 'final/testLabel_'
        out = open(fileOut+str(x)+'_'+str(y)+'.txt', 'w')
        counter = 0
        for i in xrange(len(self.xb)):
            if self.binary.predict([self.xb[i]])[0]:
                print >> out, self.multi.predict([self.xm[i]])[0]
                counter += 1
            else:
                print >> out, 0
        out.close()
        if savetime == '1':
            print classifierName2[x]+'*'+classifierName2[y]+':',
        else:
            print classifierName[x]+'*'+classifierName[y]+':',
        print " "+str(counter)+"    is the total number of the arguments labeled."
        return counter

if (__name__ == '__main__'):
#    out = open('argLabelCounter.txt', 'w')
#    start = clock()
#    svcB = svc(0)
#    joblib.dump(svcB.clf, "binary.m")
#    print >> out, 'Time consuming for binary classification: ', clock()-start

#    start = clock()
#    svcM = svc(1)
#    joblib.dump(svcM.clf, "multi.m")
#    print >> out, 'Time consuming for multi-classification: ', clock()-start

#    print >> out, classifierName2[5]

#    tmpC = classifier(svcB, svcM).doIt(5, 5, '1')

#    print >> out, '    ', tmpC, classifierName2[5]
#    out.close()
#else:
    light = 1
    if sys.argv[2] == '0':
        out1 = open('final/result.txt', 'w')
        out1.close()
        light = 0
    else:
        out1 = open('devLabel/result.txt', 'w')
        out1.close()
    savetime = sys.argv[1]
    if savetime == '0':
        M = 11
        classifiers = []
        for i in xrange(M):
            classifiers.append([])

        SGDB = SGD(0)
        SGDM = SGD(1)
        classifiers[0].append(SGDB)
        classifiers[0].append(SGDM)

        decisionTreeB = decisionTree(0)
        decisionTreeM = decisionTree(1)
        classifiers[1].append(decisionTreeB)
        classifiers[1].append(decisionTreeM)

        knnB = knn(0)
        knnM = knn(1)
        classifiers[2].append(knnB)
        classifiers[2].append(knnM)

        gaussianNBB = gaussianNB(0)
        gaussianNBM = gaussianNB(1)
        classifiers[3].append(gaussianNBB)
        classifiers[3].append(gaussianNBM)

        svm_B = svm_(0)
        svm_M = svm_(1)
        classifiers[4].append(svm_B)
        classifiers[4].append(svm_M)

        bagging_B = bagging_(0)
        bagging_M = bagging_(1)
        classifiers[5].append(bagging_B)
        classifiers[5].append(bagging_M)

        randomforestB = randomforest(0)
        randomforestM = randomforest(1)
        classifiers[6].append(randomforestB)
        classifiers[6].append(randomforestM)

        #svcB = joblib.load("binary.m")
        #svcM = joblib.load("multi.m")
        #classifiers[7].append(svcB)
        #classifiers[7].append(svcM)

        adaboost_B = adaboost_(0)
        adaboost_M = adaboost_(1)
        classifiers[8].append(adaboost_B)
        classifiers[8].append(adaboost_M)

        centroidB = centroid(0)
        centroidM = centroid(1)
        classifiers[9].append(centroidB)
        classifiers[9].append(centroidM)

        maxEntropyB = maxEntropy(0)
        maxEntropyM = maxEntropy(1)
        classifiers[10].append(maxEntropyB)
        classifiers[10].append(maxEntropyM)

        #       0           1           2       3       4   5           6           7       8           9
        #       SGD decisionTree knn gaussianNB svm_ bagging_ randomforest adaboost adaboost_ centroid

        out = open('argLabelCounter.txt', 'w')
        for i in xrange(M):
            if i != 7:
                print >> out, classifierName[i]
                for j in xrange(M):
                    if j != 7:
                        tmpC = classifier(classifiers[i][0], classifiers[j][1]).doIt(i, j, savetime, light)
                        print >> out, '    ', tmpC, classifierName[j]
                print >> out, ''
        out.close()
    else:
        M = 5
        classifiers = []
        for i in xrange(M):
            classifiers.append([])

        decisionTreeB = decisionTree(0)
        decisionTreeM = decisionTree(1)
        classifiers[0].append(decisionTreeB)
        classifiers[0].append(decisionTreeM)

        knnB = knn(0)
        knnM = knn(1)
        classifiers[1].append(knnB)
        classifiers[1].append(knnM)

        svm_B = svm_(0)
        svm_M = svm_(1)
        classifiers[2].append(svm_B)
        classifiers[2].append(svm_M)

        randomforestB = randomforest(0)
        randomforestM = randomforest(1)
        classifiers[3].append(randomforestB)
        classifiers[3].append(randomforestM)

        adaboost_B = adaboost_(0)
        adaboost_M = adaboost_(1)
        classifiers[4].append(adaboost_B)
        classifiers[4].append(adaboost_M)

        #svcB = joblib.load("binary.m")
        #svcM = joblib.load("multi.m")
        #classifiers[5].append(svcB)
        #classifiers[5].append(svcM)
        #       0           1           2       3       4   5           6           7       8           9
        #       SGD decisionTree knn gaussianNB svm_ bagging_ randomforest adaboost adaboost_ centroid

        out = open('argLabelCounter.txt', 'w')
        for i in xrange(M):
            print >> out, classifierName[i]
            for j in xrange(M):
                tmpC = classifier(classifiers[i][0], classifiers[j][1]).doIt(i, j, savetime, light)
                print >> out, '    ', tmpC, classifierName2[j]
            print >> out, ''
        out.close()

