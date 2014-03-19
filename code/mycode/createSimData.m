function [ sim_data ] = createSimData( option, Fs )
%createSimData  create simulated heartbeat data
%    Simulated Data Options: 
%    1. noiseless sine wave
%    2. sine wave + awg noise
%    3. noiseless ECG data
%    4. ECG data + awg noise
%    5. noiseless ECG data + respiration data
%    6. ECG + respiration data + awg noise
%   
%    input: option is an integer
%    output: simulated data, sampled at Fs

%initialize random number generator
randseed = 100;
%randn('state',randseed);

% initialize simulated data parameters
f = 1.5; % frequency of sine wave generated (in Hz)
N = 300; % number of samples of sine wave generated
snr = 10; % signal to noise ratio

switch option
    case 1
        t = (1:N)*(1/Fs);
        sim_data = sin(2*pi*f*t);
        h1 = figure('Name','Simulated Data');
        plot(t, sim_data);
        xlabel('time (s)')
        ylabel('amplitude')
        title_str = sprintf('Simulated Data (f = %1.2f Hz)', f);
        title(title_str);
    case 2
        t = (1:N)*(1/Fs);
        sim_data = awgn(sin(2*pi*f*t), snr, 'measured', randseed);
        h1 = figure('Name','Simulated Data');
        plot(t, sim_data);
        xlabel('time (s)')
        ylabel('amplitude')
        title_str = sprintf('Simulated Data (f = %1.2f Hz, snr = %1.2f)', f, snr);
        title(title_str); 
    case 3
        printf('option not yet available');        
    case 4
        printf('option not yet available'); 
    case 5
        printf('option not yet available'); 
    case 6
        printf('option not yet available'); 
    otherwise
        printf('choose an option between 1 and 6');
        exit
end
        
end

