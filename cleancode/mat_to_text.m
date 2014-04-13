load('data_via_UART_USB_mar22.mat')

% write to text file 
fileID = fopen('data1.txt','w');
fprintf(fileID,'%f \r\n',data1);
fclose(fileID);

% write to text file 
fileID = fopen('data2.txt','w');
fprintf(fileID,'%f \r\n',data2);
fclose(fileID);

% write to text file 
fileID = fopen('data3.txt','w');
fprintf(fileID,'%f \r\n',data3);
fclose(fileID);

% write to text file 
fileID = fopen('data4.txt','w');
fprintf(fileID,'%f \r\n',data4);
fclose(fileID);

% write to text file 
fileID = fopen('data5.txt','w');
fprintf(fileID,'%f \r\n',data5);
fclose(fileID);