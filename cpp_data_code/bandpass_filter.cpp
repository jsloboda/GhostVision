#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_real_inverse.h>

#include <cstdlib>


//using namespace std;
double bandpass_filter(double data, double lp_cutoff, double hp_cutoff,double sample_rate, int num_samples)	{




	int fft_size = FFT_SIZE;
	double filtered_samples [num_samples];
	double zero_array [432] = {0};
	
	//std::fill( array, array+432, 0);
	double *buffer_data = new double[fft_size];
	
	std::copy(data,data+num_samples,buffer_data);
	std::copy(zero_array,zero_array+432,buffer_data+num_samples);
	
   	gsl_fft_real_radix2_transform (buffer_data,1,fft_size);
	int lc_index = (int)((lp_cutoff*num_samples/sample_rate)+0.5);
	int hc_index = (int)((hp_cutoff*num_samples/sample_rate)+0.5);
	
	for (int i = 0; i < fft_size; ++i)	{
	
		
		if ((i >= lc_index) && (i <= hc_index))	{
		
			filtered_samples[i] = buffer_data[i];
			}
		else if ((i <= (fft_size-lc_index)) && (i >= (fft_size-hc_index)))	{
		
			filtered_samples[i] = buffer_data[i];
			}
	}
			
	 gsl_fft_real_radix2_inverse (filtered_samples,1,fft_size);
	 return filtered_samples;

	
	
	



}

int main()	{
		
		
		
		
		
		return 0;
		}
