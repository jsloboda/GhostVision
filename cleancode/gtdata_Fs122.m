%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Algorithm
%  1. get recorded data
%  2. pass filtered data into Gabor Transform function
%  3. plot:
%     (1) dowsampled data
%     (2) magnitude of Gabor coefficients
%     (3) magnitude of SELECTED gabor coefficients
%     (4) reconstructed signal, using selected coefficients
%     (5) reconstructed signal, using all coefficients
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% initialize simulation parameters
Fs = 122; % Hz



%% get data

%load('sampledata.mat')
% down-sample: keep every 80th sample to go from 8000->100 Hz
%data = downsample(data3, 80);
% eliminate first 100 samples (motion artifacts in certain data files)
%data = data(100:end);
data = data1f;
figure('Name','signal');
plot(data)


%% Gabor Transform Data

a = 1;    %length of time shift for dgt/idgt, must be positive integer
M = 1220; %number of channels for dgt/idgt. 
          % frequency resolution = Fs/M = 122/1220 = 0.1   
         
[data_gt_coeffs, Ls] = dgt(data,'gauss',a,M);
% Gabor Transform (from ltfat toolbox)
%    DGT(f,g,a,M) computes the Gabor coefficients of the input
%    signal f with respect to the window g and parameters a and M. The
%    output is a vector/matrix in a rectangular layout.
%    Input parameters:
%          f     : Input data
%          g     : Window function.
%          a     : Length of time shift.
%          M     : Number of channels.
%          L     : Length of transform to do.
%   Output parameters:
%          c     : M*N array of coefficients.
%          Ls    : Length of input signal.
%
%    References:
%    K. Gröchenig. Foundations of Time-Frequency Analysis. Birkhäuser, 
%    2001.
%      
%    H. G. Feichtinger and T. Strohmer, editors. Gabor Analysis and
%    Algorithms. Birkhäuser, Boston, 1998.
%     
%      Demos:  demo_dgt

%% plot coefficients

figure('Name', 'complete transform coefficients')
plotdgt(data_gt_coeffs, a, M);
% data_gt_coeffs [1000x1000] complex, 
% 0 to 500 "hz" (each row is .1 hz), 1000 time bins (10 sec, Fs = 100)
% use row 8 for 0.65 to 0.75
% rows 1-500 are positive freq, rows 501-1000 are negative freq
% use row 994 also for -0.65 to -0.75 Hz 

% plotdgt(coef,a) plots the Gabor coefficients coef. The coefficients must
% have been produced with a time shift of a.
% 
% plotdgt(coef,a,fs) does the same assuming a sampling rate of fs Hz 
% of the original signal.


%% choose coefficients for between 8/12 and 5/6 Hz  (.6666 - .714...)
c = zeros(size(data_gt_coeffs));
%c(7:8,:) = data_gt_coeffs(7:8,:);  % 0.55 to 0.75
%c(1214:1215,:) = data_gt_coeffs(1214:1215,:);  %  -0.55 to -0.75
c(8,:) = data_gt_coeffs(8,:);  % 0.65 to 0.75 (39 to 45 bpm)
c(1214,:) = data_gt_coeffs(1214,:);  %  -0.65 to -0.75
%c(9:20,:) = data_gt_coeffs(9:20,:);  % 0.75 to 1.95
%c(1202:1213,:) = data_gt_coeffs(1202:1213,:);  %  -0.75 to -1.95
%c(9:15,:) = data_gt_coeffs(9:15,:);  % 0.75 to 1.45 (45 to 87 bpm) 
%c(1207:1213,:) = data_gt_coeffs(1207:1213,:);  %  -0.75 to -1.45
%m = freq, n = time for c(m,n)

figure('Name', 'selected transform coefficients')
plotdgt(c, 1, Fs);
ylim([-2 2])

%% reconstruct a signal using just those coefficients

figure('Name','partial reconstructed signal');
data_reconstd=idgt(c,'gauss',a,Ls);
plot(data_reconstd/100);

%% reconstruct a signal using all coefficients
figure('Name','complete reconstructed signal');
data_reconstd=idgt(data_gt_coeffs,'gauss',a,Ls);
plot(data_reconstd/100);

%save('data1f_65to75_reconstd.mat','data_reconstd');

% idgt(c,g,a) computes the Gabor expansion of the input coefficients c 
% with respect to the window g and time shift a. The number of channels 
% is deduced from the size of the coefficients c.

%% unused: spectrogram of signal
%figure('Name','spectrogram');
%data_sgram=sgram(data,Fs,'lin');
%title('Spectrogram of the data signal');

%    SGRAM(f,sr) plots a spectrogram of f using a DGT for a signal with 
%    sampling rate sr (sampled with sr samples per second)



