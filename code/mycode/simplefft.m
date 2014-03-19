%load('sampledata.mat');
y = data2;
Fs = 8000;
T = 1/Fs;
L = length(y);
NFFT = 2^nextpow2(L);
t = (0:L-1)*T;

Y = fft(y,NFFT)/L;
f = Fs/2*linspace(0,1,NFFT/2+1);
Yss = 2*abs(Y(1:NFFT/2+1));

% Plot single-sided amplitude spectrum.
figure();
plot(f,Yss) 
title('Single-Sided Amplitude Spectrum of y(t)')
xlabel('Frequency (Hz)')
ylabel('|Y(f)|')
xlim([0 10])

% extract peaks
[pks,locs] = findpeaks(Yss,'MINPEAKHEIGHT',1*10^-4);
[max_pk_val,idx] = max(pks);
max_pk_loc = locs(idx);
max_pk_freq = f(max_pk_loc);