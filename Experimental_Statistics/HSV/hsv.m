function [h, s, v] = hsv( h, s, v, f )
%HSV 此处显示有关此函数的摘要
%   此处显示详细说明

hsv = uint8(255*rgb2hsv(f)); 
[row, col, dep] = size(hsv);
for i=1:row
    for j=1:col
        index = hsv(i, j, 1)+1;
        h(index) = h(index)+1;
    end
end

for i=1:row
    for j=1:col
        index = hsv(i, j, 2)+1;
        s(index) = s(index)+1;
    end
end

for i=1:row
    for j=1:col
        index = hsv(i, j, 3)+1;
        v(index) = v(index)+1;
    end
end

end

