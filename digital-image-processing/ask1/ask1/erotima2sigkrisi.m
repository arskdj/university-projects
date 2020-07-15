figure('Name','Σύγκριση Ισοστάθμισης RGB, HSI - Εικόνα DSCN1078');
subplot(1,3,1);
imshow(uint8(DSCN1078));
title('Αρχική');

subplot(1,3,2);
imshow(uint8(isostathmisiRGB(DSCN1078)));
title('Ισοσταθμιση RGB');

subplot(1,3,3);
imshow(uint8(isostathmisiHSI(DSCN1078)));
title('Ισοσταθμιση HSI');

figure('Name','Σύγκριση Ισοστάθμισης RGB, HSI - Εικόνα museum');
subplot(1,3,1);
imshow(uint8(museum));
title('Αρχική');

subplot(1,3,2);
imshow(uint8(isostathmisiRGB(museum)));
title('Ισοσταθμιση RGB');

subplot(1,3,3);
imshow(uint8(isostathmisiHSI(museum)));
title('Ισοσταθμιση HSI');
