clear;
clc;

fileNames = fopen('src\zzz.txt', 'r');

colorhist = zeros(1,256);

h = zeros(1, 256);
s = zeros(1, 256);
v = zeros(1, 256);

i = 1;
while feof(fileNames) == 0
    fprintf('The %dth iteration...\n', i);
    fileName = ['src\' fgetl(fileNames)];
    f = imread(fileName);
    [h, s, v] = hsv(h, s, v, f);
    colorhist = colorhist + gethsv(f);
    i = i + 1;
end
fclose(fileNames);

figure('numbertitle','off','name','Color');
bar(colorhist);

figure('numbertitle','off','name','Hue');
bar(h);

figure('numbertitle','off','name','Saturation');
bar(s);

figure('numbertitle','off','name','Value');
bar(v);