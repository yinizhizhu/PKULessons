import nltk

from nltk.corpus import names

import random

#############################
def gender_features(word):

   return {'last_letter':word[-1]}


namesljl=[(name,'male') for name in names.words('male.txt')]

namesljl=namesljl+[[name,'female'] for name in names.words('female.txt')]

random.shuffle(namesljl)


features=[(gender_features(n),g) for(n,g)in namesljl]


train_set,test_set=features[500:],features[:500]

# classifier=nltk.NaiveBayesClassifier.train(train_set)

classifier=nltk.MaxentClassifier.train(train_set)

testone=classifier.classify(gender_features("Neo"))

print(testone)

testone=classifier.classify(gender_features("Trinity"))

print(testone)

print(nltk.classify.accuracy(classifier,test_set))