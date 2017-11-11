clear;
clc;

str=pwd;
index_dir=findstr(str,'\');
str_temp=str(1:index_dir(end)-1);

fileNames = fopen([str_temp '\src\zzz.txt'], 'r');

colorhist = zeros(1,256);

tmp = [];

t_h = [];
s_h = [];
v_h = [];

i = 1;
while feof(fileNames) == 0
    fprintf('The %dth iteration...\n', i);
    fileName = [str_temp '\src\' fgetl(fileNames)];
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
    
    fprintf(hf, '%d', t_h(i, 1)/tmp(i));
    for j=2:360
        fprintf(hf, ' %d', t_h(i, j)/tmp(i));
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
    
    fprintf(sf, '%f', s_h(i, 1)/tmp(i));
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
    
    fprintf(vf, '%d', v_h(i, 1)/tmp(i));
    for j=2:256
        fprintf(vf, ' %d', v_h(i, j)/tmp(i));
    end
    fprintf(vf, ' \n');
end
fclose(vf);
