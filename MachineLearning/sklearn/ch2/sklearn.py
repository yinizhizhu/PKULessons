from sklearn import datasets, svm
from sklearn.externals import joblib
from sklearn.neighbors import KNeighborsClassifier
import matplotlib.pyplot as plt
import numpy as np
import pylab as pl
import pickle

def showImage(f):
    print f
    plt.figure()
    plt.imshow(f, cmap='gray')
    plt.show()

iris = datasets.load_iris()

iris_X, iris_y = iris.data, iris.target

print iris_y
# get the unique term in the list iris_y
print np.unique(iris_y)

print iris_X.shape

digits = datasets.load_digits()

print digits.images.shape

pl.imshow(digits.images[-1], cmap=pl.cm.gray_r)

# transform each 8x8 image into a feature vector of length 64
print digits.images.shape[0]
data = digits.images.reshape(digits.images.shape[0], -1)
print data



# KNN (k nearest neighbors) classification example:
np.random.seed(0)
indices = np.random.permutation(len(iris_X))

iris_X_train = iris_X[indices[:-10]]
iris_y_train = iris_y[indices[:-10]]

iris_X_test = iris_X[indices[-10:]]
iris_y_test = iris_y[indices[-10:]]

# Create and fit a nearest-neighbor classifier
knn = KNeighborsClassifier()
knn.fit(iris_X_train, iris_y_train)
ans = knn.predict(iris_X_test)

print ans
print iris_y_test


