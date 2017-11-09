function colorhist = gethsv(rgb)  
  
if size(rgb,3) ~= 3  
    error('3 components are needed for histogram');  
end  
  
% globals  
H_BITS = 4; S_BITS =2; V_BITS = 2;  
% rgb2hsv¿ÉÓÃrgb2hsi´úÌæ  
hsv = uint8(255*rgb2hsv(rgb));  

% histogram  
for i = 1 : 2^H_BITS  
    for j = 1 : 2^S_BITS  
        for k = 1 : 2^V_BITS  
            colorhist(i,j,k) = sum(sum(bitshift(hsv(:,:,1),-(8-H_BITS))==i-1 & bitshift(hsv(:,:,2),-(8-S_BITS))==j-1 & bitshift(hsv(:,:,3),-(8-V_BITS))==k-1));  
        end  
    end  
end  
colorhist = reshape(colorhist, 1, 2^(H_BITS+S_BITS+V_BITS));  
%normalize  
colorhist = colorhist/sum(colorhist);  
end