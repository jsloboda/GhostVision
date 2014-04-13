//*Peak Detector for Pulse Sensor Data*//
//Thresholds small peaks and counts periodic peaks to output number of beats for reference//
//arg 1 - file
//arg 2 - threshold value (after looking at some files we can visually figure which value is substantial and if not we can write an algorithm that selects highest peaks)

#include <cstdlib>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <list>
#include <stdio.h>
#include <math.h>

int pulse_detect(int threshold_magnitdue, double* transform_data, int count)
{
	
  	int i,j;
	float threshold_magnitude;
	//convert from array to dynamic vector
	//std::vector<double> data(std::begin(transform_data), std::end(transform_data)); // error
	std::vector<double> data(transform_data, transform_data + count); //count = fft_size
	std::vector<double> filtered_data;
	std::vector<double> threshold_data;
	std::vector<double> peaks;
	
	bool finish = false;
	double datum;
		
	//threshold out lower amplitudes
	int index = 0;
    for (j = 0; j < count; ++j)	{
		if (data[j] > threshold_magnitude)	{
			index ++;
			threshold_data.push_back(data[index]);
		}
	}
		
	//find the peaks
	int num_peaks = threshold_data.size();
	int index_2 = 0;
  
  		for (i = 1; i < num_peaks-1; i++)
		{
      		if (threshold_data[i] != 0 && (threshold_data[i-1] < threshold_data[i]) && (threshold_data[i+1] < threshold_data[i]))	{		
				index_2 ++;
				peaks.push_back(threshold_data[index_2]);
			}
    	}

	//free(data);
	return peaks.size(); //number of peaks
}




