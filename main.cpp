#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include "bp_filt.cpp"
#include "wavelet_transform.h"
#include "bp_filt.h"
#include "pulse_detect.h"


int
main (int argc, char **argv)	{	

	FILE *f;

	int i,j,n;
	double *data = (double*)malloc(n*sizeof(double));
	double *filtered_data = (double*)malloc(n*sizeof(double));
	double *transformed_data = (double*)malloc(n*sizeof(double));

	int filtered_peaks;
	int transform_peaks;
	n = 4096;
	//read in data from a file
	f = fopen (argv[1], "r");
	int level = atoi(argv[2]);
	int threshold_filter = atoi(argv[3]);
	int threshold_wavelet = atoi(argv[4]);
  	for (i = 0; i < n; i++)
    		{
      			fscanf (f, "%lg", &data[i]);
    		}	
  	fclose (f);
	//filter the data
	bp_filt(data,filtered_data, 0.8, 2.5,122.0); 
	//count the peaks from filtered data
	filtered_peaks = pulse_detect(threshold_filter, filtered_data, 4096);
	std::cout << "Filtered data peak count: " << filtered_peaks << std::endl;
	//transform the data
	wavelet_transform(filtered_data, transformed_data,level,4096);
	transform_peaks = pulse_detect(threshold_filter,transformed_data,4096);
	std::cout << "Transformed data peak count: " << transform_peaks << std::endl;
	//count the peaks from transformed data

	return 0;

}
