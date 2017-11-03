function si = SI(f)
hx=[-1 -2 -1;0 0 0 ;1 2 1];
hy=hx';

f = rgb2gray(f);

gx = filter2(hx, f, 'valid');
g = filter2(hy, gx, 'valid');

si = std2(g);

end