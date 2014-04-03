function data = data_convert(filename)

input = fopen(filename, 'r');
data = textscan(input, '%s');
fclose(input);

data = hex2dec(data{:});
plot(data)