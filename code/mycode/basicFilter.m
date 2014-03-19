%Filter3     Perform Low-pass, High-pass and Band-pass filters on data
%Assumes data is given in a column vector, z

z = recordedData( 3, 100 ); %createSimData(1, Fs)'; %data1;

Fs= 100; %input('Enter sampling rate  ');   % Fs = sampling rate
Ts=1/Fs;
Lz=length(z);
n=[0:Lz-1]';
t=n*Ts;

%Frequency domain filtering assumes kth-fft-point = (k-1)*Fs/N Hz;
%Find N = fft size as a nearest integer power of 2
done=0;
Np2 = nextpow2(Lz);   % Np2 = nearest power of 2
N = 2^Np2;   %N = fft size
Ftype = 1; %input('Select filter type (1/2/3 for LP/HP/BP) ');
if (Ftype == 1)
%Implement LP Filter (with lower cut-off at LC Hz)
  LC = 3; %input('Enter Lower Cut-off Freqeuncy in Hz ');
  KLC = round(1 + LC*N/Fs);
  IKLC = N-KLC + 1;
  H = ones(N,1);
  H(KLC:IKLC)=zeros(IKLC-KLC+1,1);
    
elseif (Ftype == 2)
%Implement HP Filter (with upper cut-off at UC Hz)

  UC = input('Enter Upper Cut-off Freqeuncy in Hz ');
  KUC = round(1 + UC*N/Fs);
  IKUC = N-KUC + 1;
  H = zeros(N,1);
  H(KUC:IKUC)=ones(IKUC-KUC+1,1);

elseif (Ftype == 3)
%Implement BP Filter (with lower cut-off at LC Hz and upper cut-off at UC Hz)

  LC = 1; %input('Enter Lower Cut-off Frequency in Hz ');
  UC = 11; %input('Enter Upper Cut-off Frequency in Hz ');
  KLC = round(1 + LC*N/Fs);
  IKLC = N-KLC + 1;
  KUC = round(1 + UC*N/Fs);
  IKUC = N-KUC + 1;
  H = zeros(N,1);
  H(KLC:KUC)=ones(KUC-KLC+1,1);
  H(IKUC:IKLC)=ones(IKLC-IKUC+1,1);

end

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
% fileID = fopen('data5.txt','w');
% fprintf(fileID,'%f \r\n',datf);
% fclose(fileID);























