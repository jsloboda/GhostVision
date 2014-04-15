#include <vector>
#include "wavelet_transform.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <cstdlib>


#define INCLUDE_GSLWAVELET (1)
#if INCLUDE_GSLWAVELET
#include <gsl/gsl_sort.h>
#include <gsl/gsl_wavelet.h>

//num_coeff : number of coefficients to reconstruct the signal
double* wavelet_transform(double* filtered_data, double* transformed_data,double num_level,int fft_size,int num_coeff)
{




  gsl_wavelet *w;
  gsl_wavelet_workspace *work;
  int i,j;
  double *abscoeff = (double*)malloc (fft_size * sizeof (double));
  size_t *p = (size_t*)malloc (fft_size * sizeof (size_t));
  w = gsl_wavelet_alloc (gsl_wavelet_daubechies, 4);
  work = gsl_wavelet_workspace_alloc (fft_size);
  double* new_array= new double[4096];
  transformed_data = filtered_data;
  gsl_wavelet_transform_forward (w,transformed_data, num_level, fft_size, work);

  for (i = 0; i < fft_size; i++)
    {
      abscoeff[i] = fabs (transformed_data[i]);
    }
  
  gsl_sort_index (p, abscoeff, 1, fft_size);
  
  for (j = 0; (j + num_coeff) < fft_size; j++)	{
    transformed_data[p[j]] = 0;
	}

  gsl_wavelet_transform_inverse (w, transformed_data, 1, fft_size, work);

  std::copy(transformed_data,transformed_data+4096,new_array);
  
  gsl_wavelet_free(w);
  gsl_wavelet_workspace_free(work);

  
  free (abscoeff);
  free (p);
  return new_array;
 

}

#endif

