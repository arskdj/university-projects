function [ new_im ] = ltr( im, dmin, dmax )
%metasmimatismos contrast
% dmin, dmax epi8imitos evros

    imin = min(im(:));
    imax = max(im(:));
    
    % w1*imin + w2 = dmin
    % w1*imax + w2 = dmax
    
    w1 = (dmax-dmin)/(imax-imin);
    w2 = dmin - w1 * imin;
    
    % or
    % A = [imin 1; imax 1]
    % B = [dmin ; dmax]
    % W = inv(A)*B
    
    new_im = round(w1*im+w2);
end

