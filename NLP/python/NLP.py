from time import clock

start = clock()

class divider():
    def __init__(self):
        self.words = dict()
        self.symbol = dict()
        self.result = open("mine/res.txt", "w")
        
        self.arg = dict()
        self.argType = open('mine/argType.txt', 'w')
#        self.result.close()

    def showWord(self, word):
        print word[0].decode("utf8").encode("gbk"), word[1], word[2]

    def outputWords(self):
        out = open('mine/words.txt', 'w')
        for word in self.words:
            print >> out, "{0}  {1}".format(word, self.words[word])
        out.close()

    def outputSymbol(self):
        out = open('mine/symbol.txt', 'w')
        for s in self.symbol:
            print >> out, "{0}  {1}".format(s, self.symbol[s])
        out.close()

    def readData(self):
        data = open('data/cpbtrain.txt', 'r')
        for line in data.readlines():
            words = line.strip('\n').split(' ')
            for word in words:
                if len(word) > 2:
                    word = word.split('/')
                    if word[1] == 'PU':
                        if word[0] in self.symbol:
                            self.symbol[word[0]] += 1
                        else:
                            self.symbol[word[0]] = 1
                    else:
                        if word[0] in self.words:
                            self.words[word[0]] += 1
                        else:
                            self.words[word[0]] = 1
    #                    self.showWord(word)
                    if 'ARG' in word[2]:
                        if word[2][2:] in self.arg:
                            self.arg[word[2][2:]] += 1
                        else:
                            self.arg[word[2][2:]] = 0
                            print >> self.argType, word[2][2:]
                            print word[2][2:]
        data.close()
        self.outputWords()
        self.outputSymbol()
        self.result.close()
        self.argType.close()
    

test = divider()

test.readData()

end = clock()
print "The total time is: ", end-start