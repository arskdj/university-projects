
a1_3_church2_50 = findEdges(church2,50);
a1_3_church2_100 = findEdges(church2,100);
a1_3_san_fransisco_50 = findEdges(San_Francisco,50);
a1_3_san_fransisco_100 = findEdges(San_Francisco,100);

save('apotelesmata/a1_3_church2_50.mat','a1_3_church2_50');
save('apotelesmata/a1_3_church2_100.mat','a1_3_church2_100');
save('apotelesmata/a1_3_san_fransisco_50.mat','a1_3_san_fransisco_50');
save('apotelesmata/a1_3_san_fransisco_100.mat','a1_3_san_fransisco_100');


figure('Name','Ανίχνευση Ακμών - Εικόνα church2');

subplot(1,3,1);
imshow(uint8(church2));
title('Αρχική');

subplot(1,3,2);
imshow(uint8(a1_3_church2_50));
title('Κατώφλι = 50');

subplot(1,3,3);
imshow(uint8(a1_3_church2_100));
title('Κατώφλι = 100');


figure('Name','Ανίχνευση Ακμών - Εικόνα San_Fransisco');

subplot(1,3,1);
imshow(uint8(San_Francisco));
title('Αρχική');

subplot(1,3,2);
imshow(uint8(a1_3_san_fransisco_50));
title('Κατώφλι = 50');

subplot(1,3,3);
imshow(uint8(a1_3_san_fransisco_100));
title('Κατώφλι = 100');
