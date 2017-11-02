fileNames = fopen('src\zzz.txt', 'r');
output = fopen('data\resolutions.txt', 'w');

gx_lee = fopen('data\gx_lee.txt', 'w');% std_src
gy_lee = fopen('data\gy_lee.txt', 'w');% totalColor
g_lee = fopen('data\g_lee.txt', 'w');   %total

hx=[-1 -2 -1;0 0 0 ;1 2 1];
hy=hx';

std_src = [];
totalColor = [];
total = [];

i = 1;
while feof(fileNames) == 0
    fileName = ['src\' fgetl(fileNames)];
    F = imread(fileName);
    f = F;
    
    [gColor, std_lee] = colorFilter(f);
    fprintf(gx_lee, '%s %d\n', fileName, std_lee);
    totalColor(i) = std_lee;
    
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
    
    gSobel = filter2(hy, filter2(hx, f, 'valid'), 'valid');
    std_lee = std2(gSobel);
    fprintf(g_lee, '%s %d\n', fileName, std_lee);
    total(i) = std_lee;
    i = i+1;
end
fclose(g_lee);
fclose(gy_lee);
fclose(gx_lee);
fclose(output);
fclose(fileNames);

figure('numbertitle','off','name','Rgb2gray');
imshow(f);
figure('numbertitle','off','name','gColor');
imshow(255-gColor);
figure('numbertitle','off','name','gSobel');
imshow(255-gSobel);

x = 1:1:(i-1);

figure('numbertitle','off','name','Spatial information');
subplot(3, 2, 1);
plot(x, std_src, 'ro-');
ylabel('stdSrc');
xlabel('unsorted');
subplot(3, 2, 2);
plot(x, sort(std_src), 'ro-');
xlabel('sorted');

subplot(3, 2, 3);
plot(x, totalColor, 'go-');
ylabel('totalC');
subplot(3, 2, 4);
plot(x, sort(totalColor), 'go-');

subplot(3, 2, 5);
plot(x, total, 'bo-');
ylabel('total');
subplot(3, 2, 6);
plot(x, sort(total), 'bo-');

figure('numbertitle','off','name','Spatial information 2');
subplot(2, 1, 1);
plot(x, std_src, 'ro-');
hold on;
plot(x, totalColor, 'go-');
hold on;
plot(x, total, 'co-');
xlabel('unsorted');
legend('stdSrc','Color','Both');

subplot(2, 1, 2);
plot(x, sort(std_src), 'ro-');
hold on;
plot(x, sort(totalColor), 'go-');
hold on;
plot(x, sort(total), 'co-');
xlabel('sorted');
legend('stdSrc','Color','Both');
