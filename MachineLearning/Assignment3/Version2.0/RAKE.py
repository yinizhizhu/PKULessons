# coding=UTF-8

from rake_nltk import Rake

if (__name__ == '__main__'):
    print 'Start extracting the keywords...'
    r = Rake()
    read = open('FilteredDBLP.txt', 'r')
    out = open('FilteredDBLP_noun.txt', 'w')
#    read = open('a.txt', 'r')
#    out = open('a_out.txt', 'w')
    for line in read.readlines():
        line = line.strip('\n')
        one = line.split(chr(9))
#        print one
        if one[0] == 'title':
            r.extract_keywords_from_text(one[1])
            result = r.get_ranked_phrases()
            ans = ", ".join(result)
            print >> out, one[0]+chr(9)+ans
        else:
            print >> out, line
    out.close()
    read.close()
    print "Done! The result is stored in the 'FilteredDBLP_noun.txt'"