from sklearn import datasets, svm
from sklearn.externals import joblib
import matplotlib.pyplot as plt
import numpy as np
import pickle

iris = datasets.load_iris()

X, y = iris.data, iris.target

def showImage(f):
    print f
    plt.figure()
    plt.imshow(f, cmap='gray')
    plt.show()

print iris
out = open('iris.txt', 'w')
print >> out, 'target_names', iris.target_names
print >> out, 'data', iris.data, len(iris.data)
print >> out, 'target', iris.target, len(iris.target)
print >> out, 'descr', iris.DESCR
print >> out, 'feature_names', iris.feature_names
out.close()

clf = svm.SVC()
clf.fit(X, y)

s = pickle.dumps(clf)
clf2 = pickle.loads(s)

ans = clf2.predict(X[0])
print 'predict', ans, ', target', y[0]

joblib.dump(clf, 'filename.pkl')
clf = joblib.load('filename.pkl')

ans = clf.predict(X[0])
print 'predict', ans, ', target', y[0]


digits = datasets.load_digits()

print digits
out = open('digits.txt', 'w')
print >> out, 'images', digits.images
print >> out, 'data', digits.data
print >> out, 'target_names', digits.target_names
print >> out, 'descr', digits.DESCR
print >> out, 'target', digits.target
out.close()

print digits.images[0]
showImage(digits.images[0])


clf = svm.SVC(gamma=0.001, C=100.)

clf.fit(digits.data[:-1], digits.target[:-1])


f = digits.data[-1]
print len(f)
showImage(np.array(f).reshape(8, 8))

ans = clf.predict(f)
print ans