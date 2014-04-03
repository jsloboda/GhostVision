load('data_via_UART_USB_mar22.mat')



%% filter

z = data1;

Fs= 122; 
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
  LC = 2; %input('Enter Lower Cut-off Freqeuncy in Hz ');
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
fileID = fopen('data1f.txt','w');
fprintf(fileID,'%f \r\n',datf);
fclose(fileID);
data1f = dataf
    
% save('data3_27_filtered.mat', 'data1f', 'data2f', 'data3f', 'data4f', 'data5f');
% 
% 
% % downsample
% %load('data_UART_Filtered.mat');
% 
%     % down-sample: keep every 48th sample to go from 488->100 Hz
%     %data1f = zeros(ceil(length(data1)/4),1);
%     data1fs = downsample(data1f, 12);
%     data2fs = downsample(data2f, 12);
%     data3fs = downsample(data3f, 12);
%     data4fs = downsample(data4f, 12);
%     data5fs = downsample(data5f, 12);
%     
%     save('data_UART_Filtered_downsampled.mat', 'data1fs', 'data2fs', 'data3fs', 'data4fs', 'data5fs');
%     
%     
% % write to text file 
% fileID = fopen('data1fs.txt','w');
% fprintf(fileID,'%f \r\n',data1fs);
% fclose(fileID);
% 
% fileID = fopen('data2fs.txt','w');
% fprintf(fileID,'%f \r\n',data2fs);
% fclose(fileID);
% 
% fileID = fopen('data3fs.txt','w');
% fprintf(fileID,'%f \r\n',data3fs);
% fclose(fileID);
% 
% fileID = fopen('data4fs.txt','w');
% fprintf(fileID,'%f \r\n',data4fs);
% fclose(fileID);
% 
% fileID = fopen('data5fs.txt','w');
% fprintf(fileID,'%f \r\n',data5fs);
% fclose(fileID);
% 
% figure();
% subplot(3,1,1)
% plot(data1)
% subplot(3,1,2)
% plot(data1f)
% subplot(3,1,3)
% plot(data1fs)
