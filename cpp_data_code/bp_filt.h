#ifndef _BP_FILT_H_
#define _BP_FILT_H_

#include <vector>
using namespace std;

void bp_filt(double *data,double *filtered_samples, double lp_cutoff, double hp_cutoff,double sample_rate);


#endif
