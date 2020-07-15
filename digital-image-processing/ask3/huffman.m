function [ per, c , red ] = huffman( im )

p = my_hist(im);

[dict,avglen] = huffmandict(0:255,p);

compressed = huffmanenco(im(:),dict);

p2 = my_hist(compressed);
[dict2,avglen2] = huffmandict(0:255,p2);

per = entropy(im)/avglen;
c = avglen2/avglen;
red = 1 - 1/c;

end

