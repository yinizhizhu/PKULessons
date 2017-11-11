clear;
clc;
N = 145;    %number of the images
Nfeatures = 512;
names = {};
store = zeros(N, N);
gists = zeros(N, Nfeatures);

str=pwd;
index_dir=findstr(str,'\');
str_temp=str(1:index_dir(end)-1);

i = 1;
fileNames = fopen([str_temp '\src\zzz.txt'], 'r');

param.imageSize = [1080 1920];
param.orientationsPerScale = [8 8 8 8];
param.numberBlocks = 4;
param.fc_prefilt = 4;

while feof(fileNames) == 0
    fileName = [str_temp '\src\' fgetl(fileNames)];
    names(i) = {fileName};
    fprintf('%d: %s is moving on...\n', i, fileName);
    f = imread(fileName);
    [res, tmp] = LMgist(f, '', param);
    gists(i,:) = res;
    i = i+1;
end
fclose(fileNames);

output = fopen('data\similar.txt', 'w');
for i=1:N-1
    fprintf('%d\n', i);
    for j=i+1:N 
%     for j=i+1:i+1
        score = differ(gists(i,:), gists(j,:));
        store(i, j) = score;
        store(j, i) = score;
        fprintf(output, '%d %d %f %s %s\n', i, j, score, names{1, i}, names{1, j});
    end
end
fclose(output);

xa = 1:N;
ya = 1:N;
[x,y] = meshgrid(xa, ya);
mesh(x, y, store);