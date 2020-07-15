function [ out ] = isostathmisiRGB( im )
im = double(im);
%red
out(:,:,1) = isostathmisi(im(:,:,1));
%green
out(:,:,2) = isostathmisi(im(:,:,2));
%blue
out(:,:,3) = isostathmisi(im(:,:,3));


end
