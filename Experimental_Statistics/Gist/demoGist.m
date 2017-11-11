function demoGist(file1, file2, dis)
% EXAMPLE 1
% Load image
img1 = imread(file1);

% Parameters:
clear param
param.orientationsPerScale = [8 8 8 8];
param.numberBlocks = 4;
param.fc_prefilt = 4;

% Computing gist requires 1) prefilter image, 2) filter image and collect
% output energies
[gist1, param] = LMgist(img1, '', param);

% Visualization
figure();
subplot(2, 2, 1);
imshow(img1);
title(dis);
subplot(2, 2, 2);
showGist(gist1, param);
title('Descriptor');


% EXAMPLE 2
% Load image (this image is not square)
img2 = imread(file2);

% Parameters:
clear param 
%param.imageSize. If we do not specify the image size, the function LMgist
%   will use the current image size. If we specify a size, the function will
%   resize and crop the input to match the specified size. This is better when
%   trying to compute image similarities.
param.orientationsPerScale = [8 8 8 8];
param.numberBlocks = 4;
param.fc_prefilt = 4;

% Computing gist requires 1) prefilter image, 2) filter image and collect
% output energies
[gist2, param] = LMgist(img2, '', param);

% Visualization
subplot(2, 2, 3)
imshow(img2);
subplot(2, 2, 4);
showGist(gist2, param);
end

