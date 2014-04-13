

% write to text file 
fileID = fopen('data1_pulse.txt','w');
fprintf(fileID,'%f \r\n',data1_pulse);
fclose(fileID);

% write to text file 
fileID = fopen('data2_pulse.txt','w');
fprintf(fileID,'%f \r\n',data2_pulse);
fclose(fileID);

% write to text file 
fileID = fopen('data3_pulse.txt','w');
fprintf(fileID,'%f \r\n',data3_pulse);
fclose(fileID);

% write to text file 
fileID = fopen('data4_pulse.txt','w');
fprintf(fileID,'%f \r\n',data4_pulse);
fclose(fileID);

% write to text file 
fileID = fopen('data5_pulse.txt','w');
fprintf(fileID,'%f \r\n',data5_pulse);
fclose(fileID);