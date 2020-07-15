img = im;

[M,N] = size(img);

% zero padding
fp = zeros(2*M,2*N);
fp(1:M,1:N) = img;

% sintetagmenes
[X,Y]=find(fp==fp);

% metatopisi fourier sto kentro
g = fftshift(fp);

%logari8mizo
g = log(1+g);

% fourier
G = fft2(g);



% apostasi
D = zeros(size(fp));
D(:) = sqrt((X-M).^2 + (Y-N).^2);

% highpass filtro
% d0 : aktina kiklou filtru
% D : apostaseis 
gl = 0.25;
c = 1;
gh = 1.7;
d0 = 80;

H = (gh-gl).*( 1 - exp( -c .*( D.^2./(d0^2) ) ) ) + gl;

% filtrarisma
S = G.*H;

% antistrofos fourrier
S = real(ifft2(S));

% ln^-1
S = expm1(S);

% metatopisi stis arxikes 8eseis
S = ifftshift(S);

%smikrinsi ikonas stis arxikes diastaseis
S=S(1:M,1:N);

% grammikos metasximatismos
S=ltr(S,0,255);

figure;
imshowpair(uint8(img),uint8(S),'montage');
title('Ομοιομορφικό φιλτράρισμα');
figure;
plot(D(:),H(:));
title('Σύγκριση φίλτρου με την αρχική');



