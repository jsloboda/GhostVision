%Filter3     Perform Low-pass filter on data

load('sampledata.mat');
% down-sample: keep every 80th sample to go from 8000->100 Hz
data = downsample(data3, 80);
% eliminate first 100 samples (motion artifacts in certain data files)
z = data(100:end);

Fs= 100; 
Ts=1/Fs;
Lz=length(z);
n=[0:Lz-1]';
t=n*Ts;

%Frequency domain filtering assumes kth-fft-point = (k-1)*Fs/N Hz;
%Find N = fft size as a nearest integer power of 2
Np2 = nextpow2(Lz);   % Np2 = nearest power of 2
N = 2^Np2;   %N = fft size
Ftype = 1; %input('Select filter type (1/2/3 for LP/HP/BP) ');

%Implement LP Filter (with lower cut-off at LC Hz)
  LC = 3; %input('Enter Lower Cut-off Freqeuncy in Hz ');
  KLC = round(1 + LC*N/Fs);
  IKLC = N-KLC + 1;
  H = ones(N,1);
  H(KLC:IKLC)=zeros(IKLC-KLC+1,1);

dat=z;
dat = dat - sum(dat)/length(dat);
datK = fft(dat,N);
datKH = datK.*H;
datf = real(ifft(datKH));  %dataf = filtered data
datf = datf(1:length(z));

% Plot results
figure(1)
subplot(311)
plot(t,dat)
grid
title('Original data')
Freq=[0:1:N-1]*Fs/N;
subplot(312)
plot(Freq,H)
axis([0 N*Fs/N 0 1.5])
grid
title('Frequency Response of the Filter ')
subplot(313)
plot(t,datf)
title('Filtered data');
grid


% write to text file 
% fileID = fopen('data_filtered.txt','w');
% fprintf(fileID,'%f \r\n',datf);
% fclose(fileID);























