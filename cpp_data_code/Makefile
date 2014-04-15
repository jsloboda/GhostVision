ALL:
	
	#g++ -g pulse_detect.cpp wavelet_transform.cpp bp_filt.cpp main.cpp `pkg-config --cflags --libs gsl` -o main
	#./main $(FILE) $(LEVEL) $(THRESHOLD_FILTER) $(THRESHOLD_WAVELET) $(NUM_COEFF)
	#graph -T ps -x 0 4096 32 -h 0.3 -a dwt.dat > dwt.ps
	g++ -g server.cpp pulse_detect.cpp wavelet_transform.cpp bp_filt.cpp data_main.cpp -o data_main -lgsl -lgslcblas -lm -I/usr/include -L/usr/bin 
	#./data_main $(SOCKET_NUM)
		



