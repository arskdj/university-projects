function [ compressed ] = compressDCT( perc, im )
im = double(im);
[x,y] = size(im);
I1 = dct2(im);
I2 = abs(I1);

sorted = sort(I2(:));
l = length(sorted);
threshold = sorted(floor(l-l*perc + 1));
indexes = find(I2 > threshold);

compressed = zeros(x,y);
compressed(indexes) = I1(indexes);
compressed = idct2(compressed);
end

