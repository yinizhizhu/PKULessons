import torch, time
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt
from my_dataset import DepthDataset
from model import DepthNet
from tensorboardX import SummaryWriter

learning_rate = 5e-4
weight_decay = 1e-6
epoch_num = 9
batch_size = 16
alpha = 0.5

train_dir = '/home/lee/Downloads/3D/Project/data/nyu2_train.csv'

train_dataset = DepthDataset(img_dir=train_dir, is_train=True)
print 'Training Data - Done!'
train_loader = torch.utils.data.DataLoader(train_dataset,
    batch_size=batch_size, shuffle=True, drop_last=True)

model = DepthNet().cuda()

optimizer = optim.Adam(model.parameters(), 
    lr=learning_rate, weight_decay=weight_decay)

criterion = nn.MSELoss()
# criterion = nn.L1Loss()

writer = SummaryWriter()


def train():

    epoch_id = 0
    step_id = 0

    head = time.time()
    while epoch_id < epoch_num:
        step = 1
        start = time.time()
        for batch_id, (img, gt) in enumerate(train_loader):

            img = img.cuda()
            gt = gt.cuda()
            # print img.shape, gt.shape

            pred_img, pred_depth = model(img)
            # print pred_img.shape, pred_depth.shape
            # raw_input('Continue?')

            loss_reconstruction = criterion(pred_img, img)
            loss_depth = criterion(pred_depth, gt)
            loss = alpha * loss_reconstruction + loss_depth

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            step_id += 1

            print ' ', epoch_id, '-', step, '-', loss.item()
            writer.add_scalar('step_loss', loss.item(), step_id)
            writer.add_scalar('reconstruction_loss', loss_reconstruction.item(), step_id)
            writer.add_scalar('depth_loss', loss_depth.item(), step_id)
            step += 1

        epoch_id += 1
        
        torch.save(model, 'model_recons.pth')
        print '     For %th epoch:', time.time() - start
    print 'Time-consuming:', time.time() - head

s = time.time()
try:
    train()
    writer.close()
except KeyboardInterrupt:
    writer.close()
    print 'Time consuming:', time.time()-s
    print ''
    print '-'*90
    print 'Existing from training early.'