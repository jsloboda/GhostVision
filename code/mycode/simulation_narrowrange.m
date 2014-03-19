%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Simulated Data Options: 
%  1. noiseless sine wave
%  2. sine wave + awg noise
%  3. noiseless ECG data
%  4. ECG data + awg noise
%  5. noiseless ECG data + respiration data
%  6. ECG + respiration data + awg noise
%  
%  Data Options:
%  1. Test target data
%  2. Test target data + respiration data + awg noise
%  3. Actual person data (5 prelim recordings)
%  4. Pulse Sensor data
%
%  Algorithm
%  1. create simulated data  (given from input)
%  2. band pass filter 0.5 - 10 Hz (done in hardware)
%  3. pass filtered data into Gabor Transform function
%  4. plot input vs. output data.
%  (5. calculate measure of accuracy? - not yet implemented)
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% initialize simulation parameters
Fs = 100; % Hz

% MAGUNITS='dB';
% BPfiltDesign = fdesign.bandpass('Fst1,Fp1,Fp2,Fst2,Ast1,Ap,Ast2', ...
%                                  0.008,0.01,0.2,0.202,60, 1, 80  , Fs,MAGUNITS);
%                                 %0.008,0.01,0.2,0.202,60, 1, 60  , Fs,MAGUNITS);
%                % non-normalized: 0.4, 0.5,10, 10.1, 60, 1, 60
% BPfilt = design(BPfiltDesign, 'butter', 'MatchExactly', 'passband');
% how much does it matter how this is designed?
% can't design a equiripple


%% create & BP filter data
data_recorded = recordedData( 3, Fs ); %Fs = 150; % if option 4
%data_created = createSimData(1, Fs);
% data = filter(BPfilt, data_created);
%     % plot it for a security check
%     h2 = figure('Name','Filtered Data');
%     plot(data);
%     xlabel('time (s)')
%     ylabel('amplitude')
%     title('Filtered Data'); 
      %issue: plots nothing, even when generate 0.1 Hz sine wave
%data = data_created; 
data = data_recorded;

figure('Name','signal');
plot(data)


%% Transform Data to extract mean frequency per time interval

a = 1; %length of time shift for dgt/idgt, must be positive integer
M = 1000; %number of channels for dgt/idgt. 
         % frequency resolution = Fs/M = 100/500 = 0.2
         % 100/1000 = 0.1   (so can look at 0.6 to 0.8 Hz range for c)

% Gabor Transform (from ltfat toolbox)
[data_gt_coeffs, Ls] = dgt(data,'gauss',a,M);
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
% row 1 is  to .05 hz, row 2: 0.05 - 0.15, 3: .15, 4: .25, 5:.35, 6:
% .45, 7:.55, 8:.65, 9:.75, 10:
% use row 8 for 0.65 to 0.75
% rows 1-500 are positive freq, rows 501-1000 are negative freq
% use row 994 also for -0.65 to -0.75 Hz 

% plotdgt(coef,a) plots the Gabor coefficients coef. The coefficients
% must have been produced with a time shift of a.
% 
% plotdgt(coef,a,fs) does the same assuming a sampling rate of fs Hz 
% of the original signal.


%% choose coefficients for between 8/12 and 5/6 Hz  (.6666 - .714...)
c = zeros(size(data_gt_coeffs));
c(8,:) = data_gt_coeffs(8,:);
c(994,:) = data_gt_coeffs(994,:);
%m = freq, n = time for c(m,n)

figure('Name', 'selected transform coefficients')
plotdgt(c, 1, Fs);

%% reconstruct a signal using just those coefficients

figure('Name','partial reconstructed signal');
data_reconstd=idgt(c,'gauss',a,Ls);
plot(data_reconstd/100);

%% reconstruct a signal using all coefficients
figure('Name','complete reconstructed signal');
data_reconstd=idgt(data_gt_coeffs,'gauss',a,Ls);
plot(data_reconstd/100);

% idgt(c,g,a) computes the Gabor expansion of the input coefficients c 
% with respect to the window g and time shift a. The number of channels 
% is deduced from the size of the coefficients c.


%figure('Name','spectrogram');
%data_sgram=sgram(data,Fs,'lin');
%title('Spectrogram of the data signal');

%    SGRAM(f,sr) plots a spectrogram of f using a DGT for a signal with 
%    sampling rate sr (sampled with sr samples per second)



