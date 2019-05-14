import torch, time
from my_dataset import DepthDataset
from model import DepthNet
import matplotlib.image
from torchvision.transforms import ToPILImage

test_dir = '/home/lee/Downloads/3D/Project/data/nyu2_test.csv'
# test_dir = '/home/lee/Downloads/3D/Project/data/nyu2_train.csv'

test_dataset = DepthDataset(img_dir=test_dir, is_train=False)
print 'Testing Data - Done!'
test_loader = torch.utils.data.DataLoader(test_dataset,
                                          batch_size=1, shuffle=False, drop_last=False)

model = torch.load('model_recons.pth').cuda()
# model = torch.load('model.pth').cuda()


def visualize():
    model.eval()
    with torch.no_grad():
        for id, img in enumerate(test_loader):
            if id >= 654:
                break
            print id,
            img = img.cuda()
            reconstruction, depth = model(img)

            reconstruction = reconstruction.squeeze(0).cpu()
            reconstruction = torch.clamp(reconstruction, 0.0, 1.0)
            depth = depth.squeeze(0).cpu()
            depth = torch.clamp(depth, 0.0, 1.0)

            # matplotlib.image.imsave('Output/depth_%03d_0.png'%id,
            #                         reconstruction.view(reconstruction.size(2), reconstruction.size(3)).data.numpy())
            #
            # matplotlib.image.imsave('Output/depth_%03d_0.png'%id,
            #                         depth.view(depth.size(2), depth.size(3)).data.numpy())
            #
            recons = ToPILImage()(reconstruction)
            recons.save('Output/depth_%03d_0.png'%id)

            dep = ToPILImage()(depth)
            dep.save('Output/depth_%03d_1.png'%id)

s = time.time()
try:
    visualize()
except KeyboardInterrupt:
    print 'Time consuming:', time.time() - s
    print ''
    print '-' * 90
    print 'Existing from training early.'