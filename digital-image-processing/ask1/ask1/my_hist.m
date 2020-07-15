function res = my_hist( im )
    arr = im(:);
    n = length(arr);
    res = zeros(1,256);
    
    for i = 0:255;
        p = find(im == i);
        res(i+1) = length(p)/n;
    end
    plot(0:255,res);
    
end

