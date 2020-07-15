function [ S, outim1, outim2 ] = butterworth( img, n, d0 )
img = double(img);
[M,N] = size(img);

% zero padding
fp = zeros(2*M,2*N);
fp(1:M,1:N) = img;

% sintetagmenes
[X,Y]=find(fp==fp);

% fourier
g = fft2(fp);

% metatopisi fourier sto kentro
G = fftshift(g);

figure('Name','fourier eikonas');
imshow(ltr(G,0,255));

% apostasi
D = zeros(size(fp));
D(:) = sqrt((X-M).^2 + (Y-N).^2);



% Butterworth lowpass
% d0 : aktina kiklou filtru
% D : apostaseis 
H = 1./(1+(D./d0).^(2*n));

figure;imshow(uint8(ltr(H,0,255)));

% filtrarisma
S = G.*H;
% metatopisi stis arxikes 8eseis
S = ifftshift(S);

% antistrofos fourrier
S = real(ifft2(S));

%smikrinsi ikonas stis arxikes diastaseis
S=S(1:M,1:N);

% laplacian filtra o3insis
L1 = [ 0 1 0; 1 -4 1; 0 1 0;];
L2 = [1 1 1 ; 1 -8 1; 1 1 1;];

imL1 = zeros(size(S));
imL2 = zeros(size(S));

imL1 = conv2(S,L1,'same');
imL2 = conv2(S,L2,'same');

outim1 = zeros(size(img));
outim2 = zeros(size(img));

% efarmogi filtron 
outim1 = img - imL1(1:M,1:N);
outim2 = img + imL2(1:M,1:N);


figure('Name','butterworth vs original');
imshowpair(uint8(img),uint8(S),'montage');


figure('Name','Laplacian');
subplot(1,3,1);
imshow(uint8(img)); hold on;
title('Αρχική');

subplot(1,3,2);
imshow(uint8(outim1));hold on;
title('Laplacian 1');

subplot(1,3,3);
imshow(uint8(outim2));
title('Laplacian 2');

save('l1.mat','outim1');

save('l2.mat','outim2');

end

