from PIL import Image
from torch.utils.data import Dataset
from torchvision.transforms import ToTensor


class DepthDataset(Dataset):
    def __init__(self, img_dir, is_train):
        print('Loading')
        self.is_train = is_train
        self.basic_dir = '/home/lee/Downloads/3D/Project/'
        self.load_train(img_dir) if is_train else self.load_test(img_dir)

    def load_train(self, img_dir):
        self.imgs_dir = []
        self.deps_dir = []
        input = open(img_dir, 'r')
        for line in input.readlines():
            line = line.strip().split(',')

            self.imgs_dir.append(self.basic_dir + line[0])

            self.deps_dir.append(self.basic_dir + line[1])

    def load_test(self, img_dir):
        self.imgs_dir = []
        input = open(img_dir, 'r')
        for line in input.readlines():
            line = line.strip().split(',')

            self.imgs_dir.append(self.basic_dir + line[0])

    def __len__(self):
        return len(self.imgs_dir)

    def __getitem__(self, idx):
        img_dir = self.imgs_dir[idx]
        img = Image.open(img_dir)
        img = ToTensor()(img)

        if self.is_train:
            dep_dir = self.deps_dir[idx]
            dep = Image.open(dep_dir)
            dep = ToTensor()(dep)
            return img, dep
        return img