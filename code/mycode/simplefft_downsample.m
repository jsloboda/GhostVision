for i=1:5
    name = sprintf('data%i', i);
    %load('sampledata.mat');
    y_orig = eval(name);
    % down-sample: keep every 80th sample to go from 8000->100 Hz
    y = downsample(y_orig, 80);
    Fs = 100;
    T = 1/Fs;
    L = length(y);
    NFFT = 2^nextpow2(L);
    t = (0:L-1)*T;

    Y = fft(y,NFFT)/L;
    f = Fs/2*linspace(0,1,NFFT/2+1);
    Yss = 2*abs(Y(1:NFFT/2+1));

    % Plot single-sided amplitude spectrum.
    figure('Name',name);
    plot(f,Yss) 
    title('Single-Sided Amplitude Spectrum of y(t)')
    xlabel('Frequency (Hz)')
    ylabel('|Y(f)|')
    xlim([0 10])

    % extract peaks
    [pks,locs] = findpeaks(Yss,'MINPEAKHEIGHT',1*10^-4);
    [max_pk_val,idx] = max(pks);
    max_pk_loc = locs(idx);
    max_pk_freq = f(max_pk_loc)
    
end