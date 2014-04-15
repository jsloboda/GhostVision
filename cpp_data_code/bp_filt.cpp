//TO COMPILE: g++ bandpass_filter.cpp `pkg-config --cflags --libs gsl` -o bandpass
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <string.h>
#include <gsl/gsl_errno.h>

#define INCLUDE_GSL_FFT (1)

#if INCLUDE_GSL_FFT
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>


#define num_samples 4096
using namespace std;

void bp_filt(double *data, double *filtered_samples, double lp_cutoff, double hp_cutoff,double sample_rate)	{

	gsl_fft_real_wavetable * real;
  	gsl_fft_halfcomplex_wavetable * hc;
  	gsl_fft_real_workspace * work;	
	work = gsl_fft_real_workspace_alloc (4096);
  	real = gsl_fft_real_wavetable_alloc (4096);
	int fft_size = 4096;
	int i = 0;
	
	for( i = 0; i< 4096; i++) {
		filtered_samples[i] = data[i]; //cout to double check
	}

   	gsl_fft_real_transform (filtered_samples,1,fft_size,real,work);
	gsl_fft_real_wavetable_free (real);
	int lc_index = (int)((lp_cutoff*num_samples/sample_rate)+0.5);
	int hc_index = (int)((hp_cutoff*num_samples/sample_rate)+0.5);

	if (hc_index % 2 == 0)	{
		hc_index -= -1;
	}
	if (lc_index % 2 == 0)	{
		lc_index -= -1;
	}

	for (i = 0; i < fft_size; ++i)	{	
		if ((i < 2*lc_index) || (i > 2*hc_index))	
		{   // copy real/imaginary pair
			filtered_samples[i] = 0;
		}
	} 
	 hc = gsl_fft_halfcomplex_wavetable_alloc (fft_size);		
	 gsl_fft_halfcomplex_inverse (filtered_samples,1,fft_size,hc,work);
	 gsl_fft_halfcomplex_wavetable_free (hc);
	 gsl_fft_real_workspace_free (work);

		}	
#endif	


/*
int main() { return 0;} */
