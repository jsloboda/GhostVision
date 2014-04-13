%Filter3     Perform Low-pass filter on data

 %load('data_using_SD16_SPI.mat');
 

z = vertcat(data2, zeros(4096 - length(data2), 1)); %data1nes(1:366,1);

Fs= 122; 
Ts=1/Fs;
Lz=length(z);
n=[0:Lz-1]';
t=n*Ts;

%Frequency domain filtering assumes kth-fft-point = (k-1)*Fs/N Hz;
%Find N = fft size as a nearest integer power of 2
Np2 = nextpow2(Lz);   % Np2 = nearest power of 2
N = 2^Np2;   %N = fft size

%Implement BP Filter (with lower cut-off at LC Hz and upper cut-off at UC Hz)
  LC = .8; %input('Enter Lower Cut-off Frequency in Hz ');
  UC = 2.5; %input('Enter Upper Cut-off Frequency in Hz ');
  KLC = round(1 + LC*N/Fs);
  IKLC = N-KLC + 1;
  KUC = round(1 + UC*N/Fs);
  IKUC = N-KUC + 1;
  H = zeros(N,1);
  H(KLC:KUC)=ones(KUC-KLC+1,1);
  H(IKUC:IKLC)=ones(IKLC-IKUC+1,1);

dat=z;
%dat = dat - sum(dat)/length(dat);
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

% % write to text file 
% fileID = fopen('data3postfpaper.txt','w');
% fprintf(fileID,'%f \r\n',datf);
% fclose(fileID);
% data3postf = datf;
% 
% save('data3postfpaper.mat', 'data3postf');

%save('data_point8to3.mat', 'data1f', 'data2f', 'data3f', 'data4f', 'data5f');




















