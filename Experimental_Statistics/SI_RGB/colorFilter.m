function [gColor, stdDeviration] = colorFilter(f)

hx=[-1 -2 -1;0 0 0 ;1 2 1];
hy=hx';

R = f(:,:,1);
G = f(:,:,2);
B = f(:,:,3);

Rxy = filterSobel(R, hx, hy);
Gxy = filterSobel(G, hx, hy);
Bxy = filterSobel(B, hx, hy);

rgbx = cat(3,Rxy,Gxy,Bxy);

gColor = rgb2gray(rgbx);

stdDeviration = std2(gColor);

show(Rxy, Gxy, Bxy, rgbx, gColor);
end

function show(Rxy, Gxy, Bxy, rgbx, gColor)
figure('numbertitle','off','name','Rxy');
imshow(Rxy);
figure('numbertitle','off','name','Gxy');
imshow(Gxy);
figure('numbertitle','off','name','Bxy');
imshow(Bxy);
figure('numbertitle','off','name','rgbx');
imshow(rgbx);

figure('numbertitle','off','name','rgb2gray');
imshow(255-gColor);

end