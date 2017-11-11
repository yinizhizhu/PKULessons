from sklearn.cluster import KMeans
from time import clock

start = clock()

class knn():
    def __init__(self):
        self.n_clusters = [[] for i in xrange(3)]
        
        self.hsv = [[] for i in xrange(3)] #store the properties of the object
        self.hsv_features = [360, 256, 256]
        self.hsv_imgs = [[] for i in xrange(3)]
        self.hsv_files = ['data\\h.txt', 'data\\s.txt', 'data\\v.txt']
        self.hsv_out_files = ['cluster\\h.txt', 'cluster\\s.txt', 'cluster\\v.txt']
        self.hsv_plot = ['cluster\\h_.txt', 'cluster\\s_.txt', 'cluster\\v_.txt']
        
        for i in xrange(3):
            self.readHSV(i)
        
    def readHSV(self, index):
        '''
        readData: 
            get the data in the source data
        '''
        read = open(self.hsv_files[index], 'r')
        n_features = self.hsv_features[index]
        for line in read.readlines():
            one = line.strip('\n').split(' ')
            self.hsv_imgs[index].append(one[0])
            self.hsv[index].append([float(one[j]) for j in xrange(1, n_features)])
        read.close()
        
    def clusterHSV(self, index):
        best = 9999999
        n = 1
        basic = 3 #146
        for n_cluster in xrange(2, basic):
            n_cluster = 20
            print 'Clustering the data with n_cluster({0}) in file {1}...'.format(n_cluster, self.hsv_files[index])
            clf = KMeans(n_clusters=n_cluster)
            clf.max_iter = 1200
            s = clf.fit(self.hsv[index])
            if clf.inertia_ < best:
                print '****{0}->{1}****'.format(best, clf.inertia_)
                best = clf.inertia_
                n = n_cluster
                print 'Done!!!'
                print s
                
#                print len(clf.labels_)
        
                store = [[] for i in xrange(n_cluster)]
                for i in xrange(len(clf.labels_)):
                    store[clf.labels_[i]].append(i)
                        
                out = open(self.hsv_out_files[index], 'w')
                out_plot = open(self.hsv_plot[index], 'w')
                for i in xrange(n_cluster):
                    print >> out, '{0}:\n'.format(i),
                    print >> out_plot, '*'
                    print >> out_plot, len(store[i])
                    for j in xrange(len(store[i])):
                        print >> out, '    {0} , {1}'.format(self.hsv_imgs[index][store[i][j]], store[i][j]+1)
                        print >> out_plot, store[i][j]+1
                    print >> out
                out.close()
                out_plot.close()
                print 'Output the labels into text file {0}!!!\n'.format(self.hsv_out_files[index])
            self.n_clusters[index].append(n)
        
tmp = knn()
for i in xrange(3):
    tmp.clusterHSV(i)
for i in xrange(3):
    print tmp.n_clusters[i]
    for j in xrange(1, len(tmp.n_clusters[i])):
        if tmp.n_clusters[i][j] <= tmp.n_clusters[i][j-1]:
            print j-1, j, ': ', tmp.n_clusters[i][j]

end = clock()
print "The total time is: ", end-start