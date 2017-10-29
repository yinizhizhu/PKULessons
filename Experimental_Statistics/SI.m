fileNames = fopen('zzz.txt', 'r');
output = fopen('resolutions.txt', 'w');

gx_lee = fopen('gx_lee.txt', 'w');
% gx_sort = fopen('gx_sort.txt', 'w');
gy_lee = fopen('gy_lee.txt', 'w');
% gy_sort = fopen('gy_sort.txt', 'w');
g_lee = fopen('g_lee.txt', 'w');
% g_sort = fopen('g_sort.txt', 'w');

hx=[-1 -2 -1;0 0 0 ;1 2 1];
hy=hx';

std_src = [];
totalx = [];
% totalx_sort = [];
totaly = [];
% totaly_sort = [];
total = [];
% total_sort = [];


i = 1;
while feof(fileNames) == 0
    fileName = fgetl(fileNames);
    f = imread(fileName);
    f = rgb2gray(f);
    [row, col] = size(f);
    if (row < col)
        tmp = col;
        col = row;
        row = tmp;
    end
    if row < 1920 || col < 1080
        fprintf(output, '%s: %d * %d\n', fileName, row, col);
    end
    std_src(i) = std2(f);
    
    gx = filter2(hx, f, 'valid');
%     gx = filter2(hx, f, 'same');
    std_lee = std2(gx);
    fprintf(gx_lee, '%s %d\n', fileName, std_lee);
    totalx(i) = std_lee;
%     totalx_sort(i) = struct('name', fileName, 'si', std_lee);
    
    gy = filter2(hy, f, 'valid');
%     gy = filter2(hy, f, 'same');
    std_lee = std2(gy);
    fprintf(gy_lee, '%s %d\n', fileName, std_lee);
    totaly(i) = std_lee;
%     totaly_sort(i) = struct('name', fileName, 'si', std_lee);
    
    g = filter2(hy, gx, 'valid');
%     g = filter2(hy, gx, 'same');
%     g = gx+gy;
    std_lee = std2(g);
    fprintf(g_lee, '%s %d\n', fileName, std_lee);
    total(i) = std_lee;
%     total_sort(i) = struct('name', fileName, 'si', std_lee);
    i = i+1;
end
fclose(g_lee);
fclose(gy_lee);
fclose(gx_lee);
fclose(output);
fclose(fileNames);

% sort(total_sort.si);
% for j=1:1:i
%     fprintf(g_sort, '%s %d\n', total_sort(j).fileName, total_sort(j).si);
% end
% fclose(g_sort);
% sort(totaly_sort.si);
% for j=1:1:i
%     fprintf(gy_sort, '%s %d\n', totaly_sort(j).fileName, totaly_sort(j).si);
% end
% fclose(gy_sort);
% sort(totalx_sort.si);
% for j=1:1:i
%     fprintf(gx_sort, '%s %d\n', totalx_sort(j).fileName, totalx_sort(j).si);
% end
% fclose(gx_sort);

figure('numbertitle','off','name','Rgb2gray');
imshow(f);
figure('numbertitle','off','name','Horizontal');
imshow(255-gx);
figure('numbertitle','off','name','Vertical');
imshow(255-gy);
figure('numbertitle','off','name','Both');
imshow(255-g);

x = 1:1:(i-1);

figure('numbertitle','off','name','Spatial information');
subplot(4, 2, 1);
plot(x, std_src, 'ro-');
ylabel('std_src');
xlabel('unsorted');
subplot(4, 2, 2);
plot(x, sort(std_src), 'ro-');
xlabel('sorted');

subplot(4, 2, 3);
plot(x, totalx, 'go-');
ylabel('totalx');
subplot(4, 2, 4);
plot(x, sort(totalx), 'go-');

subplot(4, 2, 5);
plot(x, totaly, 'bo-');
ylabel('totaly');
subplot(4, 2, 6);
plot(x, sort(totaly), 'bo-');

subplot(4, 2, 7);
plot(x, total, 'co-');
ylabel('total');
subplot(4, 2, 8);
plot(x, sort(total), 'co-');

figure('numbertitle','off','name','Spatial information 2');
subplot(2, 1, 1);
plot(x, std_src, 'ro-');
hold on;
plot(x, totalx, 'go-');
hold on;
plot(x, totaly, 'bo-');
hold on;
plot(x, total, 'co-');
xlabel('unsorted');
legend('stdSrc','Hor','Ver','Both');

subplot(2, 1, 2);
plot(x, sort(std_src), 'ro-');
hold on;
plot(x, sort(totalx), 'go-');
hold on;
plot(x, sort(totaly), 'bo-');
hold on;
plot(x, sort(total), 'co-');
xlabel('sorted');
legend('stdSrc','Hor','Ver','Both','Location','northwest');


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

% f = imread('pure.jpg');
% % % get the pure jpg
% % [row, col, deep] = size(f);
% % for d=1:1:deep
% %     for i=1:1:row
% %         for j=1:1:col
% %             f(i, j, d) = 240;
% %         end
% %     end
% % end
% % imwrite(f, 'pure.jpg', 'jpg');
% % % the same mode
% f = rgb2gray(f);
% gx = filter2(hx, f, 'same');
% gy = filter2(hy, f, 'same');
% g = filter2(hy, gx, 'same');
% % % the valid mode
% % gx = filter2(hx, f, 'valid');
% % gy = filter2(hy, f, 'valid');
% % g = filter2(hy, gx, 'valid');
% 
% figure('numbertitle','off','name','Rgb2gray');
% imshow(f);
% figure('numbertitle','off','name','Horizontal');
% imshow(255-gx);
% figure('numbertitle','off','name','Vertical');
% imshow(255-gy);
% figure('numbertitle','off','name','Both');
% imshow(255-g);