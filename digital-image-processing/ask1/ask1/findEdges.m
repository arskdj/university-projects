function [ M ] = findEdges( im, katofli )
im = rgb2gray(im);
w1 = [ 1 2 1; 0 0 0; -1 -2 -1];
w2 = [ 1 0 -1; 2 0 -2; 1 0 -1];
gx = conv2(im,w1,'same');
gy = conv2(im,w2,'same');
M = sqrt(gx.^2 + gy.^2);
max(gx(:))
max(gy(:))
for i = 1:length(M(:))
    if M(i) <= katofli
        M(i) = 0;
    else
        M(i) = 255;
    end
end

end

