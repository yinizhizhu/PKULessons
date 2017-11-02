from sklearn import datasets, svm, linear_model, cluster
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
#KNeighborsClassifier(algorithm='auto', leaf_size=30, metric='minkowski',
#metric_params=None, n_neighbors=5, p=2, weights='uniform')
print ans
print iris_y_test


# Linear regression
diabetes = datasets.load_diabetes()
#print len(diabetes.data[0])
#print diabetes.data, len(diabetes.data)
#print diabetes.target, len(diabetes.target)

diabetes_X_train = diabetes.data[:-20]
diabetes_X_test = diabetes.data[-20:]
diabetes_y_train = diabetes.target[:-20]
diabetes_y_test = diabetes.target[-20:]

regr = linear_model.LinearRegression()
regr.fit(diabetes_X_train, diabetes_y_train)
print regr.coef_
print regr.intercept_
# The mean square error
print np.mean((regr.predict(diabetes_X_test)-diabetes_y_test)**2)
# Explained variance score: 1 is perfect prediction
# and 0 means that there is no linear relationship
# between X and Y.
print regr.score(diabetes_X_test, diabetes_y_test)


# shrinkage
X = np.c_[ .5, 1].T
y = [.5, 1]
test = np.c_[ 0, 2].T
regr = linear_model.LinearRegression()
pl.figure()
np.random.seed(0)
for _ in range(6):
    this_X = .1*np.random.normal(size=(2, 1)) + X
    regr.fit(this_X, y)
    pl.plot(test, regr.predict(test))
    pl.scatter(this_X, y, s=3)


# ridge
regr = linear_model.Ridge(alpha=.1)
pl.figure()
np.random.seed(0)
for _ in range(6):
    this_X = .1*np.random.normal(size=(2, 1)) + X
    regr.fit(this_X, y)
    pl.plot(test, regr.predict(test))
    pl.scatter(this_X, y, s=3)


alphas = np.logspace(-4, -1, 6)
# sparse model
regr = linear_model.Lasso()
scores = [regr.set_params(alpha=alpha).fit(diabetes_X_train, diabetes_y_train,).score(diabetes_X_test, diabetes_y_test) for alpha in alphas]
best_alpha = alphas[scores.index(max(scores))]
regr.alpha = best_alpha
regr.fit(diabetes_X_train, diabetes_y_train)
#Lasso(alpha=0.025118864315095794, copy_X=True, fit_intercept=True,
#max_iter=1000, normalize=False, positive=False, precompute=False,
#random_state=None, selection='cyclic', tol=0.0001, warm_start=False)
print regr.coef_
print regr.intercept_


# LogisticRegression
logistic = linear_model.LogisticRegression(C=1e5)
logistic.fit(iris_X_train, iris_y_train)
#LogisticRegression(C=100000.0, class_weight=None, dual=False,
#fit_intercept=True, intercept_scaling=1, max_iter=100,
#multi_class='ovr', penalty='l2', random_state=None,
#solver='liblinear', tol=0.0001, verbose=0)
print logistic.coef_
print logistic.intercept_



# # Support vector machines (SVMs)
# Linear SVMs
svc = svm.SVC(kernel='linear')
# Polynomial kernel
#svc = svm.SVC(kernel='poly', degree=3) # degree: polynomial degree
# RBF kernel (Radial Basis Function)
#svc = svm.SVC(kernel='rbf') # gamma: inverse of size of radial kernel
svc.fit(iris_X_train, iris_y_train)
# SVC(C=1.0, cache_size=200, class_weight=None, coef0=0.0, degree=3, gamma=0.0,
#kernel='linear', max_iter=-1, probability=False, random_state=None,
#shrinking=True, tol=0.001, verbose=False)




# Application example: vector quantization
import scipy as sp
try:
    lena = sp.lena()
except AttributeError:
    from scipy import misc
    lena = misc.lena()
X = lena.reshape((-1, 1)) # We need an (n_sample, n_feature) array
k_means = cluster.KMeans(n_clusters=5, n_init=1)
k_means.fit(X)
#KMeans(copy_x=True, init='k-means++', ...
values = k_means.cluster_centers_.squeeze()
labels = k_means.labels_
lena_compressed = np.choose(labels, values)
lena_compressed.shape = lena.shape