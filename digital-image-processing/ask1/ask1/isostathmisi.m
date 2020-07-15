function [newim] = isostathmisi(im)
[x,y] = size(im);
n = x*y;
p = zeros(1,256);
    
% Συνάρτηση πιθανότητας
for k = 0:255
    c = length(find(im == k));
    p(k+1) = c/n;
end

% p: συνάρτηση κατανομής
his = zeros(1,256);
his = round(255*cumsum(p));

% αντικαθιστώ κάθε στοιχείο με το ανάλογη τιμή στο his

newim = zeros(x,y);

for i = 0:255
    temp = find(im==i);
    newim(temp) = his(i+1);
end

end