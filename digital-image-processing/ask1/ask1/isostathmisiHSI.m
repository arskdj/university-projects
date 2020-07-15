function [ out ] = isostathmisiHSI( im )
im = double(im);
out = im;
out = rgb2hsv(im);
out(:,:,3) = isostathmisi(out(:,:,3));
out = hsv2rgb(out);
end

