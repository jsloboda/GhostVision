% load('data_via_UART_USB_mar22.mat')
% 
% % write to text file 
% fileID = fopen('data1.txt','w');
% fprintf(fileID,'%f \r\n',data1);
% fclose(fileID);
% 
% % write to text file 
% fileID = fopen('data2.txt','w');
% fprintf(fileID,'%f \r\n',data2);
% fclose(fileID);
% 
% % write to text file 
% fileID = fopen('data3.txt','w');
% fprintf(fileID,'%f \r\n',data3);
% fclose(fileID);
% 
% % write to text file 
% fileID = fopen('data4.txt','w');
% fprintf(fileID,'%f \r\n',data4);
% fclose(fileID);
% 
% % write to text file 
% fileID = fopen('data5.txt','w');
% fprintf(fileID,'%f \r\n',data5);
% fclose(fileID);


load('/home/jenn/Documents/W14/452/project/code/ourdata/bbb/newCircuitComponents/data_UART_Filtered_downsampled.mat')

% write to text file 
fileID = fopen('data1fs.txt','w');
fprintf(fileID,'%f \r\n',data1fs);
fclose(fileID);

% write to text file 
fileID = fopen('data2fs.txt','w');
fprintf(fileID,'%f \r\n',data2fs);
fclose(fileID);

% write to text file 
fileID = fopen('data3fs.txt','w');
fprintf(fileID,'%f \r\n',data3fs);
fclose(fileID);

% write to text file 
fileID = fopen('data4fs.txt','w');
fprintf(fileID,'%f \r\n',data4fs);
fclose(fileID);

% write to text file 
fileID = fopen('data5fs.txt','w');
fprintf(fileID,'%f \r\n',data5fs);
fclose(fileID);