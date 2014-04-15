#include "server.h"
#include <numeric>
#include "pulse_detect.h"
#include "bp_filt.h"
#include "wavelet_transform.h"
#include <stdio.h>
#include <cstdlib>


#define FFT_SIZE (4096)

int main (int argc, char * argv[]) {

	//give command line input: any 4 digit number

	//inputs
	int num_coeff = 20; // number of coefficients used to reconstruct the signal
	int num_level = 1; //number of decomposition levels for wavelet transform
	//double data_array [4096];
	double zero_pad [432] = {0}; 
	double lp = 0.8; //low pass frequency
	double hp = 2.5; //high pass frequency
	double s_rate = 122.0; //sample rate
	double n = 3664; //number of incoming samples
	int threshold_magnitude = 0;
	int threshold_wavelet = 500;
	int counter = 0;
	int average_array_transformed [4] = {0};
	int average_transform = 0;
	int average_array_filtered [4] = {0};
	int average_filt = 0;
	int BPM_filtered = 0;
	int BPM_transformed = 0;
	
	int newsockfd;
	serverSetup(argv[1], newsockfd);

	//move into while loop and safely delete at the end-------------
	//init all new arrays with 0s--------------
	//check for shallow copies, ptr = ptr, deep copy data-------------(the function wavelet_transform)------------------

	//pass in the arrays as pointsers unt function, mke function void------
	//check for double pointers, dont want that----------
	
	
	while(1) { 
		double *filtered_data = new double[4096]();
		uint16_t *buff = new uint16_t[3664]();
		double *transformed_data = new double[4096]();
		double *data_array = new double[4096]();
		// read from buffer
		cout << "Reading...\n";
		int n = read(newsockfd, buff, sizeof(uint16_t)*3664);
		if (n < 0) printf("ERROR reading from socket");
		
		//std::copy(buff,buff+3664,data_array); //concerned about cast to double
		int i = 0;
		for( i = 0; i< 3664; i++) {
			data_array[i] = buff[i];
		}
		
		/* // for testing: calculate sum & print to terminal
		double sum = std::accumulate(buff,buff+3664,0);
		std::cout << sum <<std::endl;
		// for rest of project
		*/

		// filter 
		bp_filt(data_array,filtered_data,lp, hp,s_rate);
		BPM_filtered = 2*pulse_detect(threshold_magnitude, 			 										  filtered_data, 4096);
		std::cout << "Filtered BPM : " << BPM_filtered << std::endl;
		
		/* //wavelet transform
		transformed_data = wavelet_transform(filtered_data,transformed_data,num_level,4096,num_coeff); 
		BPM_transformed = 2*pulse_detect(500,transformed_data,4096);
		std::cout << "Transformed BPM : " << BPM_transformed << std::endl;
		*/
		
		//output to screen an average of 4 batches to the screen
		average_filt = 0;
		average_array_filtered[counter] = BPM_filtered;
		//average_array_transformed[counter] = BPM_transformed;
		//average_transform = 0;
		for (i = 0; i < 4; ++i)	{
			//average_transform += average_array_transformed[i];
			average_filt += average_array_filtered[i];
		}
		counter ++;
		if (counter ==4){
			counter = 0;}
		//average_transform = average_transform/4;
		average_filt = average_filt/4;
		std::cout << "Average Filtered BPM is : " << average_filt << std::endl;
		//std::cout << "Average Transformed BPM is : " << average_transform << std::endl;
		
		//delete the arrays
		delete [] transformed_data;
		delete [] filtered_data;
		delete [] buff;
		delete [] data_array;
		//break;
		}	
	return 0;	
}
