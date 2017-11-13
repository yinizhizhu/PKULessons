function showHSVSimilar(t_h, str_temp, tmp_names, title, a, b, c, d, e, f)
%SHOWHSVSIMILAR 此处显示有关此函数的摘要
%   此处显示详细说明

figure('numbertitle','off','name', title);
subplot(3,4,1);
imshow(imread([str_temp '\src\' tmp_names{1, a}]));
subplot(3,4,2);
bar(t_h(a, :));
subplot(3,4,3);
imshow(imread([str_temp '\src\' tmp_names{1,b}]));
subplot(3,4,4);
bar(t_h(b, :));

subplot(3,4,5);
imshow(imread([str_temp '\src\' tmp_names{1, c}]));
subplot(3,4,6);
bar(t_h(c, :));
subplot(3,4,7);
imshow(imread([str_temp '\src\' tmp_names{1, d}]));
subplot(3,4,8);
bar(t_h(d, :));

subplot(3,4,9);
imshow(imread([str_temp '\src\' tmp_names{1, e}]));
subplot(3,4,10);
bar(t_h(e, :));
subplot(3,4,11);
imshow(imread([str_temp '\src\' tmp_names{1, f}]));
subplot(3,4,12);
bar(t_h(f, :));

end

