/* gt.c : gabor tranform


*/


#include <gsl/gsl_matrix.h>
#include <gsl/gsl_fft_complex.h>

#define L 100 /* length of window, in samples */
#define L_SIG 500  /* manually input length of original signal, in samples */

int main () {

	double signal [L_SIG];
	double signal_windowed [L];
	double gaussian_window [L];
	int x;

	x = gsl_fft_complex_radix2_forward(signal);
	

	return 0;
}