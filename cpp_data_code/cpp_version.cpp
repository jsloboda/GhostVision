#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_sort.h>
#include <gsl/gsl_wavelet.h>
//using namespace std;
int
main (int argc, char **argv)
{

  int nc = atoi(argv[4]); //# of highest coefficient for reconstruction
  int num_level = atoi(argv[2]);
  int n = atoi(argv[3]); //note: originally n = 256	
  int i; /*, nc = 20;*/
  double *data = (double*)malloc(n*sizeof(double));
  double *data_decimated = (double*)malloc (n * sizeof (double));
  double *abscoeff = (double*)malloc (n * sizeof (double));
  size_t *p = (size_t*)malloc (n * sizeof (size_t));
  std::vector<double> filtered_data;
  FILE * f;
  gsl_wavelet *w;
  gsl_wavelet_workspace *work;

  w = gsl_wavelet_alloc (gsl_wavelet_daubechies, 4);
  work = gsl_wavelet_workspace_alloc (n);

  f = fopen (argv[1], "r");
  for (i = 0; i < n; i++)
    {
      fscanf (f, "%lg", &data[i]);
    }
  fclose (f);


 

  gsl_wavelet_transform_forward (w, data, num_level, n, work);
  std::vector<double> threshold_data;
  for (i = 0; i < n; i++)
    {
	  if (data[i] > nc) {
	  printf ("%g\n", data[i]);
	  threshold_data.push_back(data[i]);
	}
    }

  int size_of_new = threshold_data.size();
//we can feed this into peak counting
  //std::cout << size_of_new << std::endl;
  gsl_wavelet_free (w);
  gsl_wavelet_workspace_free (work);

  free (data);
  free (abscoeff);
  free (p);
  return 0;
}



