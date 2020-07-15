function [ e ] = entropy( im )

e = 0;
p = 0;
[x,y] = size(im);

for i = 1:255
    p = length(find(im==i))/(x*y);
    if p == 0
        continue
    end
    e = e - p*log2(p);
end

end

