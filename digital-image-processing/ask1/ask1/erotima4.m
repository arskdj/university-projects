[a1_4_panses_mean, a1_4_panses_median] = thorivos(pan);
save('apotelesmata/a1_4_panses_mean.mat','a1_4_panses_mean');
save('apotelesmata/a1_4_panses_median.mat','a1_4_panses_median');

figure('Name','Αφαίρεση θορύβου - Εικόνα panses');
subplot(1,3,1);
imshow(uint8(pan));
title('Αρχική');

subplot(1,3,2);
imshow(uint8(a1_4_panses_mean));
title('Φίλτρο Mean');

subplot(1,3,3);
imshow(uint8(a1_4_panses_median));
title('Φίλτρο Median');


[a1_4_lena_mean, a1_4_lena_median] = thorivos(x_le);
save('apotelesmata/a1_4_lena_mean.mat','a1_4_lena_mean');
save('apotelesmata/a1_4_lena_median.mat','a1_4_lena_median');

figure('Name','Αφαίρεση θορύβου - Εικόνα lena');
subplot(1,3,1);
imshow(uint8(x_le));
title('Αρχική');

subplot(1,3,2);
imshow(uint8(a1_4_lena_mean));
title('Φίλτρο Mean');

subplot(1,3,3);
imshow(uint8(a1_4_lena_median));
title('Φίλτρο Median');