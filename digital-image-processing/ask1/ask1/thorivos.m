function [ im2, im3] = thorivos( im )
l = length(im(:));
[x,y] = size(im);

tixeoi = randn(x,y);
aspro = find(tixeoi>0.95);
im(aspro) = 255;

en8 = im;
save('en8.mat', 'en8')

mavro = find(tixeoi<0.1);
im(mavro) = 0;



%filtro mean
%3x3
n = 3;
p(1:n,1:n) =1;
m1 = (1/n^2) * p;
im2 = conv2(im,m1,'same');

im3 = im;

%filtro median
n = 5;
d = floor(n/2);
for i = 1+d:x-d
    for j= 1+d:y-d
        temp = im(i-d:i+d,j-d:j+d);
        s = sort(temp(:));
        m = round(length(s)/2);
        im3(i,j) = s(m);
    end
end



end

