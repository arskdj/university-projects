% 8orivos
8orivos = rand(size(im))

% stin en8orivi eikona efarmozo filtro mesu oru
ones(3,3)./9
% apo8ikevo ton meso oro stin mesi tis nea eikonas

% stin en8orivi eikona efarmozo filtro median
% den ine grammiko opote den mporo na kano sineli3i
% sort gitonia, vrisko kentriko simio tu array ke 
% apo8ikevo to median sti mesi 

% efarmogi filtron
f = pinakas filtou
conv2(im,f,'same');

M = srtq(dx^2 + dy^2)