clear;
clc;

str=pwd;
index_dir=findstr(str,'\');
str_temp=str(1:index_dir(end)-1);

fileNames = fopen([str_temp '\src\zzz.txt'], 'r');

colorhist = zeros(1,256);

tmp = [];
tmp_names = {};

t_h = [];
s_h = [];
v_h = [];

i = 1;
while feof(fileNames) == 0
    fprintf('The %dth iteration...\n', i);
    name = fgetl(fileNames);
    tmp_names(i) = {name};
    fileName = [str_temp '\src\' name];
    f = imread(fileName);
    tmp(i) = size(f, 1)*size(f,2);
%     imshow(f);
    [h_s, s_s, v_s] = hsv(f);
    t_h(i, :) = h_s;
    s_h(i, :) = s_s;
    v_h(i, :) = v_s;
%     colorhist = colorhist + gethsv(f);
    i = i + 1;
end
fclose(fileNames);

% figure('numbertitle','off','name','Color');
% bar(colorhist);
% 
% % show the bar
% for i=1:145
%     figure('numbertitle','off','name', sprintf('Hue %d', i));
%     bar(t_h(i, :));
% end
% 
% for i=1:145
%     figure('numbertitle','off','name', sprintf('Saturation %d', i));
%     bar(s_h(i, :));
% end
% 
% for i=1:145
%     figure('numbertitle','off','name', sprintf('Value %d', i));
%     bar(v_h(i, :));
% end


% output the bar into the text file
hf = fopen('data\h.txt', 'w');
fprintf('Checking the hue...\n');
for i=1:145
    check =  sum(t_h(i, :))-tmp(i);
    if check
        fprintf('Oh on! %d %d\n',i, check);
    end
    
    fprintf(hf, '%s %f', tmp_names{1,i}, t_h(i, 1)/tmp(i));
    for j=2:360
        fprintf(hf, ' %f', t_h(i, j)/tmp(i));
    end
    fprintf(hf, ' \n');
end
fclose(hf);

sf = fopen('data\s.txt', 'w');
fprintf('Checking the saturation...\n');
for i=1:145
    check =  sum(s_h(i, :))-tmp(i);
    if check
        fprintf('Oh on! %d %d\n',i, check);
    end
    
    fprintf(sf, '%s %f', tmp_names{1,i}, s_h(i, 1)/tmp(i));
    for j=2:256
        fprintf(sf, ' %f', s_h(i, j)/tmp(i));
    end
    fprintf(sf, ' \n');
end
fclose(sf);

vf = fopen('data\v.txt', 'w');
fprintf('Checking the value...\n');
for i=1:145
    check =  sum(v_h(i, :))-tmp(i);
    if check
        fprintf('Oh on! %d %d\n',i, check);
    end
    
    fprintf(vf, '%s %f', tmp_names{1,i}, v_h(i, 1)/tmp(i));
    for j=2:256
        fprintf(vf, ' %f', v_h(i, j)/tmp(i));
    end
    fprintf(vf, ' \n');
end
fclose(vf);



plotName = fopen('cluster\h_.txt', 'r');
while feof(plotName) == 0
    word = fgetl(plotName);
    if size(name, 2) > 0
        if word == '*'
            word = fgetl(plotName);
            [N, M] = getN_M(str2num(word)*2);
            fprintf('\n%s*2: %d * %d:\n', word, N, M);
            i = 1;
            figure();
        else
            imgI = str2num(word);
            fileName = [str_temp '\src\' tmp_names{1,imgI}];
            fprintf('%d, %s\n', imgI, fileName);
            f = imread(fileName);
            subplot(N, M, i);
            imshow(f);
            subplot(N, M, i+1);
            bar(t_h(imgI, :));
            i = i + 2;
        end
    end
end
fclose(plotName);



plotName = fopen('cluster\s_.txt', 'r');
while feof(plotName) == 0
    word = fgetl(plotName);
    if size(name, 2) > 0
        if word == '*'
            word = fgetl(plotName);
            [N, M] = getN_M(str2num(word)*2);
            fprintf('\n%s*2: %d * %d:\n', word, N, M);
            i = 1;
            figure();
        else
            imgI = str2num(word);
            fileName = [str_temp '\src\' tmp_names{1,imgI}];
            fprintf('%d, %s\n', imgI, fileName);
            f = imread(fileName);
            subplot(N, M, i);
            imshow(f);
            subplot(N, M, i+1);
            bar(s_h(imgI, :));
            i = i + 2;
        end
    end
end
fclose(plotName);


plotName = fopen('cluster\v_.txt', 'r');
while feof(plotName) == 0
    word = fgetl(plotName);
    if size(name, 2) > 0
        if word == '*'
            word = fgetl(plotName);
            [N, M] = getN_M(str2num(word)*2);
            fprintf('\n%s*2: %d * %d:\n', word, N, M);
            i = 1;
            figure();
        else
            imgI = str2num(word);
            fileName = [str_temp '\src\' tmp_names{1,imgI}];
            fprintf('%d, %s\n', imgI, fileName);
            f = imread(fileName);
            subplot(N, M, i);
            imshow(f);
            subplot(N, M, i+1);
            bar(v_h(imgI, :));
            i = i + 2;
        end
    end
end
fclose(plotName);
