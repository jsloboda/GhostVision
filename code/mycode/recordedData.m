function [ recorded_data ] = recordedData( option, Fs )
%recordedData uses/modifies recorded data from lab
%    Data Options:
%    1. Test target data
%    2. Test target data + respiration data + awg noise
%    3. Actual person data (5 prelim recordings)
%    4. Pulse sensor data

switch option
    case 1
        printf('option not yet available');
    case 2
        printf('option not yet available');
    case 3
        load('sampledata.mat');
        file = 3;
        chosen_file = sprintf('data%i', file);
        % show 5 prelim data samples
%         for i=1:5
%             name = sprintf('data%i', i);
%             figure('Name',name);
%             plot(eval(name));
%         end
        
        % down-sample: keep every 80th sample to go from 8000->100 Hz
        recorded_data = downsample(eval(chosen_file), 80);
        figure('Name',[chosen_file ' downsampled']);
        plot(recorded_data);
        
        % get rid of HF in beginning of file
        recorded_data = recorded_data(100:end);
    case 4
        load('ps_data.mat')
        recorded_data = ps_data;
        % down-sample: keep every to go from 150 Hz -> to 100 Hz
        %recorded_data = downsample( ),
    otherwise
        printf('choose an option between 1 and 4');
        exit
end



end

