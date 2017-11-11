function [h_s, s_s, v_s] = hsv( f )
%HSV 此处显示有关此函数的摘要
%   此处显示详细说明

h_s = zeros(1, 360);
s_s = zeros(1, 256);
v_s = zeros(1, 256);

hsv = rgb2hsv(f);
h = uint16(hsv(:,:,1)*359);
s = uint8(hsv(:,:,2)*255);
v = uint8(hsv(:,:,3)*255);

[row, col] = size(h);
for i=1:row
    for j=1:col
        index = h(i, j)+1;
%         fprintf('%d\n', index);
        h_s(index) = h_s(index)+1;
    end
end

for i=1:row
    for j=1:col
        index = s(i, j)+1;
        s_s(index) = s_s(index)+1;
    end
end

for i=1:row
    for j=1:col
        index = v(i, j)+1;
        v_s(index) = v_s(index)+1;
    end
end

end

