import torch.utils.data as data
import torch
from PIL import Image


def load_img(filepath):
    img = Image.open(filepath)
    return img


class DatasetFromFolder(data.Dataset):
    def __init__(self, scale):
        super(DatasetFromFolder, self).__init__()
        if scale:
            self.img_dir = '../CarData/TestImages_Scale/'
            self.num = 108
        else:
            self.img_dir = '../CarData/TestImages/'
            self.num = 170
        self.feature()

    def feature(self):
        self.candidates = []
        for i in xrange(self.num):
            img = load_img(self.img_dir+'test-%d.pgm'%i)
            self.candidates.append(img)

    def __getitem__(self, index):
        return self.candidates[index]

    def __len__(self):
        return len(self.candidates)