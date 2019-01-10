import torch, torchvision
import torch.nn as nn
from global_set import v_num



class appearance(nn.Module):
    def __init__(self):
        super(appearance, self).__init__()
        features = list(torchvision.models.resnet34(pretrained=True).children())[:-1]
        # print features
        self.features = nn.Sequential(*features)

    def forward(self, x):
        return self.features(x)


class car(nn.Module):
    def __init__(self):
        super(car, self).__init__()
        # self.features = nn.Sequential(
        #     nn.Conv2d(1, 32, 3, 2, 1),
        #     nn.BatchNorm2d(32),
        #     nn.Conv2d(32, 64, 3, 2, 1),
        #     nn.BatchNorm2d(64),
        #     nn.Conv2d(64, 128, 3, 2, 1),
        #     nn.BatchNorm2d(128),
        #     nn.Conv2d(128, v_num, 3, 2, 1),
        #     nn.BatchNorm2d(v_num),
        #     nn.AdaptiveAvgPool2d(1),
        # )

        self.features = nn.Sequential(
            nn.Conv2d(1, 32, 3, 2, 1),
            nn.BatchNorm2d(32),
            nn.ReLU(inplace=True),
            nn.Conv2d(32, 64, 3, 2, 1),
            nn.BatchNorm2d(64),
            nn.ReLU(inplace=True),
            nn.Conv2d(64, 128, 3, 2, 1),
            nn.BatchNorm2d(128),
            nn.ReLU(inplace=True),
            nn.Conv2d(128, v_num, 3, 2, 1),
            nn.BatchNorm2d(v_num),
            nn.AdaptiveAvgPool2d(1),
        )

        # self.features = nn.Sequential(
        #     nn.Conv2d(1, 32, 3, 2, 1),
        #     nn.BatchNorm2d(32),
        #     nn.ReLU(inplace=True),
        #     nn.Conv2d(32, v_num, 3, 2, 1),
        #     nn.BatchNorm2d(v_num),
        #     nn.AdaptiveAvgPool2d(1),
        # )

        self.cls = nn.Sequential(
            nn.Linear(v_num, 256),
            nn.LeakyReLU(inplace=True),
            nn.Linear(256, 2),
        )

    def forward(self, x):
        # print x.size()
        if x.size()[0] == 1:
            x = x.view(1, x.size()[0], x.size()[1], x.size()[2])
        x_1 = self.features(x)
        x_2 = x_1.view(x.size()[0], -1)
        return self.cls(x_2)


# features = list(torchvision.models.resnet34(pretrained=True).children())
# print features