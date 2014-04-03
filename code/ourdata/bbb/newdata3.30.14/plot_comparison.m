for i = 1:5

%     figure();
% 
%     subplot(3,1,1);
%     name1 = sprintf('data%d', i);
%     plot(eval(name1));
%     title('Original Radar Data')
% 
%     subplot(3,1,2);
%     name2 = sprintf('data%df', i);
%     plot(eval(name2));
%     title('Filtered Radar Data')
%     grid on
%     
%     subplot(3,1,3);
%     name3 = sprintf('data%d_pulse', i);
%     plot(eval(name3));
% %     title('Pulse Sensor Data')
%     grid on
    
%     
%     figure();
%     
%     name2 = sprintf('data%df', i);
%     data = eval(name2);     % Define data with peaks
%     [pks,locs] = findpeaks(data);        % Find peaks and their indices
%     plot(data,'Color','blue'); hold on;
%     plot(locs,data(locs),'k^','markerfacecolor',[1 0 0]);
%     numpeaks = length(pks);
    
    
    
    figure();
    
    subplot(2,1,1);
    name2 = sprintf('data%df', i);
    plot(eval(name2));
    title('Filtered Radar Data')
    grid on
    
    subplot(2,1,2);
    name3 = sprintf('data%d_pulse', i);
    plot(eval(name3));
    title('Pulse Sensor Data')
    grid on
    
    
    figure(); %imprecise downsampling
    plot(eval(name2)/10000, 'r')
    hold on
    temp = downsample(eval(name3), 65);
    plot(temp*10 - 1.5,'b--')
    grid on

end

   