ALL:

	g++ pulse_detect.cpp wavelet_transform.cpp bp_filt.cpp 
	g++ main.cpp `pkg-config --cflags --libs gsl` -o main
	#g++ -g pulse_detect.cpp `pkg-config --cflags --libs gsl` -o pulse_detect
	./main $(FILE)>dwt.dat $(LEVEL) $(THRESHOLD_FILTER) $(THRESHOLD_WAVE)
	graph -T ps -x 0 4096 32 -h 0.3 -a dwt.dat > dwt.ps
	
		

# works when these commands are run from terminal:
#  g++ pulse_detect.cpp wavelet_transform.cpp bp_filt.cpp main.cpp `pkg-config --cflags --libs gsl` -o main
#
# ./main data1.txt 1 0 100
