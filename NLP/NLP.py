from time import clock

start = clock()

class divider():
    def __init__(self):
        self.words = dict()
        self.store = dict()
        self.symbol = dict()
        self.result = open("res.txt", "w")
#        self.result.close()
        
    def showWord(self, word):
        print word[0].decode("utf8").encode("gbk"), word[1], word[2]
    
    def outputWords(self):
        out = open('words.txt', 'w')
        for word in self.words:
            print >> out, "{0}  {1}".format(word, self.words[word])
        out.close()
        
    def outputStore(self):
        out = open('store.txt', 'w')
        for word in self.store:
            print >> out, word, self.store[word]
        out.close()
        
    def outputSymbol(self):
        out = open('symbol.txt', 'w')
        for s in self.symbol:
            print >> out, "{0}  {1}".format(s, self.symbol[s])
        out.close()
    
    def insertWord(self, word):
        word = word.decode("utf8").encode("gbk")
        n = len(word)/2
        for i in xrange(n):
            tmp = str(word[i*2])+str(word[2*i+1])
            if tmp in self.store:
                self.store[tmp] += 1
            else:
                self.store[tmp] = 1
    
    def readData(self):
        data = open('cpbtrain.txt', 'r')
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
                            self.insertWord(word[0])
                            self.words[word[0]] = 1
    #                    self.showWord(word)
        data.close()
        self.outputWords()
        self.outputSymbol()
        self.outputStore()
        self.result.close()
    

test = divider()

test.readData()

end = clock()
print "The total time is: ", end-start