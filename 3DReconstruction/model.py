import torch
import torch.nn as nn
import torch.nn.functional as F
import torchvision.models as models
import pdb

class DepthNet(nn.Module):
    def __init__(self):
        super(DepthNet, self).__init__()

        self.base = nn.Sequential(
                nn.Conv2d(3, 4, kernel_size=5, padding=2),
                nn.ReLU(),
                nn.Conv2d(4, 8, kernel_size=5, padding=2),
                nn.ReLU(),
                nn.MaxPool2d(kernel_size=4, stride=4)       # torch.Size([108, 108])
            )

        ######################################  Reconstruction

        self.hourglass_1_encoder = nn.Sequential(
                nn.Conv2d(8, 8, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.Conv2d(8, 16, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(kernel_size=4, stride=4),       # torch.Size([27, 27])

                nn.Conv2d(16, 32, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(kernel_size=2, stride=2),       # torch.Size([9, 9])

                nn.Conv2d(32, 64, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(kernel_size=5, stride=5),       # torch.Size([3, 3])
            )

        self.hourglass_1_decoder = nn.Sequential(
                nn.Upsample(scale_factor=5),
                nn.ConvTranspose2d(64, 32, kernel_size=3, padding=1),
                nn.ReLU(),

                nn.Upsample(scale_factor=2),
                nn.ConvTranspose2d(32, 16, kernel_size=3, padding=1),
                nn.ReLU(),

                nn.Upsample(scale_factor=4),
                nn.ConvTranspose2d(16, 8, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.ConvTranspose2d(8, 8, kernel_size=3, padding=1),
                nn.ReLU(),
            )

        ######################################

        self.hourglass_2_encoder = nn.Sequential(
                nn.Conv2d(8, 8, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.Conv2d(8, 16, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(kernel_size=4, stride=4),       # torch.Size([27, 27])

                nn.Conv2d(16, 32, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(kernel_size=2, stride=2),       # torch.Size([9, 9])

                nn.Conv2d(32, 64, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(kernel_size=5, stride=5),       # torch.Size([3, 3])
            )

        self.hourglass_2_decoder = nn.Sequential(
                nn.Upsample(scale_factor=5),
                nn.ConvTranspose2d(64, 32, kernel_size=3, padding=1),
                nn.ReLU(),

                nn.Upsample(scale_factor=2),
                nn.ConvTranspose2d(32, 16, kernel_size=3, padding=1),
                nn.ReLU(),

                nn.Upsample(scale_factor=4),
                nn.ConvTranspose2d(16, 8, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.ConvTranspose2d(8, 8, kernel_size=3, padding=1),
                nn.ReLU(),
            )

        ######################################

        self.hourglass_3_encoder = nn.Sequential(
                nn.Conv2d(8, 8, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.Conv2d(8, 16, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(kernel_size=4, stride=4),       # torch.Size([27, 27])

                nn.Conv2d(16, 32, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(kernel_size=2, stride=2),       # torch.Size([9, 9])

                nn.Conv2d(32, 64, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(kernel_size=5, stride=5),       # torch.Size([3, 3])
            )

        self.hourglass_3_decoder = nn.Sequential(
                nn.Upsample(scale_factor=5),
                nn.ConvTranspose2d(64, 32, kernel_size=3, padding=1),
                nn.ReLU(),

                nn.Upsample(scale_factor=2),
                nn.ConvTranspose2d(32, 16, kernel_size=3, padding=1),
                nn.ReLU(),

                nn.Upsample(scale_factor=4),
                nn.ConvTranspose2d(16, 8, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.ConvTranspose2d(8, 8, kernel_size=3, padding=1),
                nn.ReLU(),
            )

        ######################################

        self.reconstruct_head = nn.Sequential(
                nn.Upsample(scale_factor=4),
                nn.Conv2d(8, 4, kernel_size=3, padding=1),
                nn.Conv2d(4, 3, kernel_size=1, padding=0),
            )

        self.depth_head = nn.Sequential(
                nn.Upsample(scale_factor=4),
                nn.Conv2d(8, 4, kernel_size=3, padding=1),
                nn.Conv2d(4, 1, kernel_size=1, padding=0),
            )



    def forward(self, x):
        x = self.base(x)
        # print 'base:', x.shape

        embedding_1 = self.hourglass_1_encoder(x)
        # print 'embed1:', embedding_1.shape
        x = self.hourglass_1_decoder(embedding_1)
        # print 'up1:', x.shape

        reconstruction = self.reconstruct_head(x)
        # print 'recons:', reconstruction.shape

        embedding_2 = self.hourglass_2_encoder(x)
        # print 'embed2:', embedding_2.shape
        x = self.hourglass_2_decoder(embedding_1 + embedding_2)
        # print 'up2:', x.shape
        
        embedding_3 = self.hourglass_3_encoder(x)
        # print 'embed3:', embedding_3.shape
        x = self.hourglass_3_decoder(embedding_1 + embedding_2 + embedding_3)
        # print 'up3:', x.shape
        
        depth = self.depth_head(x)
        # print 'depth:', depth.shape

        return reconstruction, depth