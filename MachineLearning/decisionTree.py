from sklearn import tree
from sklearn.datasets import load_iris

X = [[0, 0], [1, 1]]
Y = [0, 1]

clf = tree.DecisionTreeClassifier()
clf = clf.fit(X, Y)

print clf.predict([[2., 2.]])

print clf.predict_proba([[2., 2.]])

iris = load_iris()
clf = tree.DecisionTreeClassifier()
clf = clf.fit(iris.data, iris.target)