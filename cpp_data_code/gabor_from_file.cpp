//g++ gabor_from_file.cpp `pkg-config --cflags --libs gsl`  -std=c++0x  -o gabor.o

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_matrix.h>

#include "data_array1.h"
#include "data_array2.h"
#include "data_array3.h"
#include "data_array4.h"
#include "data_array5.h"

#define WIN_SIZE (122)  // gaussian window size (in samples)

using namespace std;

int main (void) 
{	
	//double* gabor_transform(double * data, int num_samples, int fft_size)
	double * data = data1;
	int num_samples = 3664;
	int fft_size = 4096;
	int sample_rate = 122;

	double hp_cutoff = 8/12;
	double lp_cutoff = 5/7;
	int lc_index = (int)((lp_cutoff*num_samples/sample_rate)+0.5);
	int hc_index = (int)((hp_cutoff*num_samples/sample_rate)+0.5);
	if (hc_index % 2 == 0)	{
		hc_index -= -1;
	}
	if (lc_index % 2 == 0)	{
		lc_index -= -1;
	}

	int i, j = 0;
	double * data_resize = new double [fft_size];
	double window[WIN_SIZE] = {1.0}; // need gaussian function
	double * current_windowed_data = new double [fft_size];
	int columns = (int) (fft_size/WIN_SIZE); //33; //(int)(4096/122); //30; // (int)(3664/122);
	//gsl_matrix * gsl_matrix_calloc (fft_size, columns); // rows: fft, columns: for each window
	double** stft_matrix = new double*[columns];
	for(i = 0; i < columns; ++i) {
    		stft_matrix[i] = new double[fft_size];}
	double *transformed_data = new double[fft_size];  // should be a matrix
	//double zero_array [432] = {0}; // necessary?
	current_windowed_data = {0}; 
	data_resize = {0};

	// create zero-padded data array: data_resize
	std::copy(data,data+num_samples,data_resize);
    //std::copy(zero_array,zero_array+432,data_resize+num_samples); // necessary?

	for (i = 0; i < columns; ++i) // or move by WIN_SIZE/2 and do i < WIN_SIZE*2 - 1
	{
		std::cout<< "i: " << i << std::endl;
		// create vector that is zero everywhere except for in the window's current position
		std::copy(window, window+WIN_SIZE, current_windowed_data+i*WIN_SIZE);
		for (j = 0; j < fft_size; ++j)
		{
			current_windowed_data[j] *= data_resize[j];
		}
	
		//fft
		gsl_fft_real_wavetable * r_table;
  		gsl_fft_halfcomplex_wavetable * hc_table;
  		gsl_fft_real_workspace * r_workspace;
	
		r_workspace = gsl_fft_real_workspace_alloc (fft_size);
   		gsl_fft_real_transform(current_windowed_data,1,fft_size, r_table, r_workspace);
	
		gsl_fft_real_wavetable_free (r_table);

		//choose appropriate coefficients
		for (int i = 0; i < fft_size; ++i)	{	
			if ((i < 2*lc_index) && (i > 2*hc_index))	
			{   // copy real/imaginary pair
				current_windowed_data[i] = 0;
			}
		} 
	
		//ifft
		hc_table = gsl_fft_halfcomplex_wavetable_alloc (fft_size);

  		gsl_fft_halfcomplex_inverse (current_windowed_data, 1, fft_size, hc_table, r_workspace);
  		gsl_fft_halfcomplex_wavetable_free (hc_table);

		// add to stft_matrix
		stft_matrix[i] = current_windowed_data;
	}

	//take each window and copy to transform data (could do in the previous for loop)
	for (i = 0; i < columns; ++i) {
		for (j=0; j < WIN_SIZE; ++j) {
			transformed_data[i*WIN_SIZE+j] = stft_matrix[i][i*WIN_SIZE+j];
		}
	}

	// print data to file
	ofstream myfile ("gabor_output.txt");
  	if (myfile.is_open())
  	{
		for (int c; c < WIN_SIZE*fft_size; ++c)
		{
    		myfile << transformed_data[c] << "\n";
    		myfile.close();
		}
  	}
  	else cout << "Unable to open file";


	// will need to do in main, & thus must pass in double * transformed_data
	delete transformed_data;
	delete current_windowed_data;
	//delete window; //(no need, not declared with new)
	delete data;
	delete data_resize;
	for(i = 0; i < columns; ++i) {
    		delete stft_matrix[i];
	}
	return 0;
}


/*
Algorithm notes

1. Take a small portion of the signal (say 1 second)
2. Window it with a small window (say 5 ms)
3. Compute the 1D fourier transform of the windowed signal.
4. Move the window by a small amount (2.5 ms)
5. Repeat above steps until end of signal.
6. All of this data is entered into a matrix that is then used to create the kind of 3D representation of the signal that shows its decomposition along frequency, amplitude and time.


Implementation notes

Create a window of 122 samples
Create a current_windowed_data[fft_size] = {0}
   set it to window where window index is
      other elements should be non-zero to avoid sync properties
element-wise multiply data & current_windowed_data (put in current_windowed_data)
take fft of current_windowed_data 
   --> returns workspace, wavetable, current_windowed_data
   --> need to keep workspace to do inverse fft
pick out coefficients:
do ifft
put ifft results in matrix to be summed 
increment window by a full window lenght & repeat


*/
