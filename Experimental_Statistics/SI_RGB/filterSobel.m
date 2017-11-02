function a = filterSobel(f, hx, hy)
a = uint8(filter2(hx, f, 'valid'));
a = uint8(filter2(hy, a, 'valid'));
end