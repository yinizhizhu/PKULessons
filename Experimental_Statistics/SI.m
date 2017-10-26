fileNames = fopen('zzz.txt', 'r');

hx=[-1 -2 -1;0 0 0 ;1 2 1];%生产sobel垂直梯度模板
hy=hx';

std_src = [];
totalx = [];
totaly = [];

i = 1;
while feof(fileNames) == 0
    fileName = fgetl(fileNames);
    f = imread(fileName);
    f = rgb2gray(f);
    std_src(i) = std2(f);
    gx = filter2(hx, f, 'same');
    std_lee = std2(gx);
    totalx(i) = std_lee;
    gy = filter2(hy, f, 'same');
    std_lee = std2(gy);
    totaly(i) = std_lee;
    i = i+1;
end
fclose(fileNames);
% disp(i);
x = 1:1:(i-1);
% disp(x);

subplot(3, 2, 1);
plot(x, std_src, 'ro-');
subplot(3, 2, 2);
plot(x, sort(std_src), 'ro-');

subplot(3, 2, 3);
plot(x, totalx, 'go-');
subplot(3, 2, 4);
plot(x, sort(totalx), 'go-');

subplot(3, 2, 5);
plot(x, totaly, 'bo-');
subplot(3, 2, 6);
plot(x, sort(totaly), 'bo-');


% figure();
% plot(x, std_src, 'ro-');
% figure();
% plot(x, sort(std_src), 'ro-');
% 
% figure();
% plot(x, totalx, 'go-');
% figure();
% plot(x, sort(totalx), 'go-');
% 
% figure();
% plot(x, totaly, 'bo-');
% figure();
% plot(x, sort(totaly), 'bo-');
