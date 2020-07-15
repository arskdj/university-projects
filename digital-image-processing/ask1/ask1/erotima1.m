a1_1_church = isostathmisi(ch);
save('apotelesmata/a1_1_church.mat','a1_1_church');
a1_1_image1 = isostathmisi(im);
save('apotelesmata/a1_1_image1.mat','a1_1_image1');

figure('Name','Ευθυγράμμιση ιστογράμματος εικόνας church');
subplot(2,2,1:2);
my_hist(ch); hold on; 
my_hist(a1_1_church);
legend('Αρχική','Ισοσταθμισμένη');

subplot(2,2,3);
imshow(uint8(ch));
title('Αρχική');
subplot(2,2,4);
imshow(uint8(a1_1_church));title('Ισοσταθμισμένη');

figure('Name','Ευθυγράμμιση ιστογράμματος εικόνας image1');
subplot(2,2,1:2);
my_hist(im); hold on; 
my_hist(a1_1_image1);
legend('Αρχική','Ισοσταθμισμένη');

subplot(2,2,3);
imshow(uint8(im));
title('Αρχική');
subplot(2,2,4);
imshow(uint8(a1_1_image1));title('Ισοσταθμισμένη');