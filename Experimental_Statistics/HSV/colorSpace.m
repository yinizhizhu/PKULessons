clear;
clc;

str=pwd;
index_dir=findstr(str,'\');
str_temp=str(1:index_dir(end)-1);

fileNames = fopen([str_temp '\src\zzz.txt'], 'r');

colorhist = zeros(1,256);

tmp = [];
tmp_names = {};

h_h = [];
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
    h_h(i, :) = h_s;
    s_h(i, :) = s_s;
    v_h(i, :) = v_s;
%     colorhist = colorhist + gethsv(f);
    i = i + 1;
end
fclose(fileNames);

% Show the similarity between hue
% s1 = '0.044822';
% s2 = '0.045986'; 
% s3 = '0.047918';
showHSVSimilar(h_h, str_temp, tmp_names, 'Similar_h', 7, 26, 26, 50, 26, 61);
% s1 = '0.184473';
% s2 = '0.293852'; 
% s3 = '0.767887';
showHSVSimilar(h_h, str_temp, tmp_names, 'Similar_h', 120, 131, 32, 124, 117, 130);

% Show the similarity between saturation
% s1 = '0.016351';
% s2 = '0.017146'; 
% s3 = '0.017293';
showHSVSimilar(s_h, str_temp, tmp_names, 'Similar_s', 70, 103, 8, 84, 22, 99);
% s1 = '0.110453';
% s2 = '0.214342'; 
% s3 = '0.568175';
showHSVSimilar(s_h, str_temp, tmp_names, 'Similar_s', 88, 132, 45, 70, 9, 36);

% Show the similarity between saturation
% s1 = '0.013452';
% s2 = '0.016165'; 
% s3 = '0.017313';
showHSVSimilar(v_h, str_temp, tmp_names, 'Similar_v', 14, 96, 96, 112, 7, 135);
% s1 = '0.072984';
% s2 = '0.158329'; 
% s3 = '0.416436';
showHSVSimilar(v_h, str_temp, tmp_names, 'Similar_v', 33, 76, 44, 100, 118, 139);

% 
% figure('numbertitle','off','name','Color');
% bar(colorhist);
% 
% % show the bar
% for i=1:145
%     figure('numbertitle','off','name', sprintf('Hue %d', i));
%     bar(h_h(i, :));
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
    check =  sum(h_h(i, :))-tmp(i);
    if check
        fprintf('Oh on! %d %d\n',i, check);
    end
    
    fprintf(hf, '%s %f', tmp_names{1,i}, h_h(i, 1)/tmp(i));
    for j=2:360
        fprintf(hf, ' %f', h_h(i, j)/tmp(i));
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
            bar(h_h(imgI, :));
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


out = fopen('similar\h_similar.txt', 'w');
for i=1:144
    for j=i+1:145
        distance = 0;
        for k=1:360
            part = h_h(i, k)/tmp(i) - h_h(j, k)/tmp(j);
            distance = distance + part*part;
        end
        fprintf(out, '%d %d %f %s %s\n', i, j, sqrt(distance), tmp_names{1, i}, tmp_names{1,j});
    end
end
fclose(out);

out = fopen('similar\s_similar.txt', 'w');
for i=1:144
    for j=i+1:145
        distance = 0;
        for k=1:256
            part = s_h(i, k)/tmp(i) - s_h(j, k)/tmp(j);
            distance = distance + part*part;
        end
        fprintf(out, '%d %d %f %s %s\n', i, j, sqrt(distance), tmp_names{1, i}, tmp_names{1,j});
    end
end
fclose(out);

out = fopen('similar\v_similar.txt', 'w');
for i=1:144
    for j=i+1:145
        distance = 0;
        for k=1:256
            part = v_h(i, k)/tmp(i) - v_h(j, k)/tmp(j);
            distance = distance + part*part;
        end
        fprintf(out, '%d %d %f %s %s\n', i, j, sqrt(distance), tmp_names{1, i}, tmp_names{1,j});
    end
end
fclose(out);
