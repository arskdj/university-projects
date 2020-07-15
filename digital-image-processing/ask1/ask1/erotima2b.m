a1_2b_dscn1078 = isostathmisiHSI(DSCN1078);
save('apotelesmata/a1_2b_dscn1078','a1_2b_dscn1078');

a1_2b_museum = isostathmisiHSI(museum);
save('apotelesmata/a1_2b_museum','a1_2b_museum');

figure('Name','Ευθυγράμμιση ιστογράμματος HSI - Εικόνα DSCN1078');
subplot(2,3,1);
my_hist(DSCN1078(:,:,1)); hold on; 
my_hist(a1_2b_dscn1078(:,:,1)); 
title('Red');
legend('Αρχική','Ισοσταθμισμένη');

subplot(2,3,2);
my_hist(DSCN1078(:,:,2)); hold on;
my_hist(a1_2b_dscn1078(:,:,2));
title('Green');
legend('Αρχική','Ισοσταθμισμένη');

subplot(2,3,3);
my_hist(DSCN1078(:,:,3)); hold on;
my_hist(a1_2b_dscn1078(:,:,3));
title('Blue');
legend('Αρχική','Ισοσταθμισμένη');

subplot(2,3,4);
imshow(uint8(DSCN1078));
title('Αρχική');

subplot(2,3,5);
imshow(uint8(a1_2b_dscn1078));
title('Ισοσταθμισμένη');


figure('Name','Ευθυγράμμιση ιστογράμματος HSI - Εικόνα museum');
subplot(2,3,1);
my_hist(museum(:,:,1)); hold on; 
my_hist(a1_2b_museum(:,:,1)); 
title('Red');
legend('Αρχική','Ισοσταθμισμένη');

subplot(2,3,2);
my_hist(museum(:,:,2)); hold on;
my_hist(a1_2b_museum(:,:,2));
title('Green');
legend('Αρχική','Ισοσταθμισμένη');

subplot(2,3,3);
my_hist(museum(:,:,3)); hold on;
my_hist(a1_2b_museum(:,:,3));
title('Blue');
legend('Αρχική','Ισοσταθμισμένη');

subplot(2,3,4);
imshow(uint8(museum));
title('Αρχική');

subplot(2,3,5);
imshow(uint8(a1_2b_museum));
title('Ισοσταθμισμένη');