
%     name = sprintf('data%i', i);
%     %load('sampledata.mat');
%     y_orig = eval(name);
%     % down-sample: keep every 80th sample to go from 8000->100 Hz
%     y = downsample(y_orig, 80);
    y = load('ps_data.mat');
    y = y.ps_data;
    Fs = 150;
    T = 1/Fs;
    L = length(y);
    NFFT = 2^nextpow2(L);
    t = (0:L-1)*T;

    Y = fft(y,NFFT)/L;
    f = Fs/2*linspace(0,1,NFFT/2+1);
    Yss = 2*abs(Y(1:NFFT/2+1));

    % Plot single-sided amplitude spectrum.
    figure('Name','pulse sensor data');
    plot(f,Yss) 
    title('Single-Sided Amplitude Spectrum of y(t)')
    xlabel('Frequency (Hz)')
    ylabel('|Y(f)|')
    xlim([0 1])

    % extract peaks
    [pks,locs] = findpeaks(Yss,'MINPEAKHEIGHT',1*10^-4);
    [max_pk_val,idx] = max(pks);
    max_pk_loc = locs(idx);
    max_pk_freq = f(max_pk_loc)
    
    figure();
    plot(y);
    hold on
    grid on
    sim = 50*sin(2*pi*f(locs(2))*t)+300;
    plot(sim);

    
    %11000 is max t of recording
    % periods of 124 115 117 119
    % 1/120 = 0.0083
    
%     figure;
% plot(y)
% hold on
%     sim_data = 50*sin(2*pi*.0083*100*t)+300;
% plot(sim_data)
% grid on