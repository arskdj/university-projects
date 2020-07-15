im = x_fl;
f = []
d = []
range = 0.01:0.01:0.9;

for i = range
   compressed = compressFFT(i,im);
   f = [f, mean2(abs(im - compressed))];
   compressed = compressDCT(i,im);
   d = [d, mean2(abs(im - compressed))];
end

figure('Name','Compression comparison');
plot(range,f);
hold on;
plot(range,d);
legend('FFT','DCT');