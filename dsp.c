#include "dsp.h"

#define PI 3.1415926535897932

/**
 * function dft_float
 * 		Calculates the DFT of the input data
 * 		Inputs:
 * 			data: unsigned 16 bit integers sampled from ADC
 * 			data_size: size of data to operate on
 * 		Outputs:
 * 			realresults: pointer to store real DFT values
 * 			imagresults: pointer to store imaginary DFT values
 * 			powerresults: pointer to store magnitude DFT values ( sqrt(real^2 + imag^2) )
 */
void dft_float(uint16_t* data, uint32_t data_size, float* realresults, float* imagresults, float* powerresults) {
	int i = 0;
	//calculate mean of data to renormalize
	float sum = 0;
	for(i=0;i<data_size;i++) {
		sum = sum + (float)data[i];
	}
	float mean = sum/(float)data_size;

	//calculate DFT coefficients
	int k;
	for(k=0;k<data_size;k++) {
		int n;
		float real_sum = 0;
		float imag_sum = 0;
		for(n=0;n<data_size;n++) {
			float n_value = (float)data[n] - mean;
			float cos_value = cos(2.0*3.14159*(float)k*(float)n/(float)data_size);
			float sin_value = sin(2.0*3.14159*(float)k*(float)n/(float)data_size);
			real_sum += n_value*cos_value;
			imag_sum += (-1)*n_value*sin_value;
		}
		realresults[k] = real_sum;
		imagresults[k] = imag_sum;
		float val = sqrtf(real_sum*real_sum + imag_sum*imag_sum);
		powerresults[k] = val;
	}
}

/**
 * function Goertzel's float
 * 		A floating point implementation of Goertzel's algorithm, which efficiently computes a single bin of the DFT.
 * 		This function performs Goertzel's on multiple bins, depending on how many frequencies we are measuring.
 * 		Inputs:
 * 			data_buff: unsigned 16 bit integers sampled from ADC
 * 			data_size: size of data to operate on
 * 			bins: list of which DFT bins we care about
 * 			bin_count: number of bins we care about
 * 		Outputs:
 * 			real: pointer to store real values for each desired bin
 * 			imagresults: pointer to store imaginary values for each desired bin
 */
void goertzels_float(uint16_t* data_buff, uint32_t data_size, uint32_t* bins, uint8_t bin_count, float* real, float* imag) {
	int b;
	for(b=0;b<bin_count;b++) {

		float w0 = 2.0*3.1415926535897932*bins[b]/data_size;
		float cosvalue = cos(w0);
		float sinvalue = sin(w0);
		float coeff = 2*cosvalue;

		float q0 = 	0;
		float q1 = 0;
		float q2 = 0;

		int i;
		for(i=0;i<data_size;i++) {
			float value = (float)data_buff[i];
			q0 = coeff*q1 - q2 + value;
			q2 = q1;
			q1 = q0;
		}

		real[b] = (q1*cosvalue - q2);
		imag[b] = q1*sinvalue;
	}
}


// ===============================================================
// BELOW CODE IS A WORK IN PROGRESS
//


/*
 * index 0...bin 1
 * index 1...bin 3
 * index 2...bin 5
 */
const int32_t COS_NUM[5] = {0,620,1174};
const int32_t COS_DEN[5] = {0,623,1197};
const int32_t SIN_NUM[5] = {0,173,151};
const int32_t SIN_DEN[5] = {0,1765,774};
const int32_t COEFF_NUM[5] = {0,826,2348};
const int32_t COEFF_DEN[5] = {0,415,1197};

const int32_t MAX_Z1_VAL = 9999999;
const int32_t Z1_SHIFT_VAL = 4;

void goertzels_fixed(uint16_t* data, uint32_t data_size, uint32_t* bins, uint8_t bin_count, int32_t* real, int32_t* imag) {
    int b;
    for(b=0;b<bin_count;b++) {
        int32_t z0, z1, z2, z1_shift;
        uint32_t n;

        int32_t cos_num = COS_NUM[bins[b]];
        int32_t cos_den = COS_DEN[bins[b]];
        int32_t sin_num = SIN_NUM[bins[b]];
        int32_t sin_den = SIN_DEN[bins[b]];
        int32_t coeff_num = COEFF_NUM[bins[b]];
        int32_t coeff_den = COEFF_DEN[bins[b]];

        z1 = 0;
        z2 = 0;

        for(n=0; n<data_size; n++) {
        	if(z1>MAX_Z1_VAL) {
        		z1_shift = Z1_SHIFT_VAL;
        	}
        	else {
        		z1_shift = 0;
        	}
        	z0 = ((coeff_num*(z1>>z1_shift)<<z1_shift)/coeff_den) - z2 + data[n];
        	z2 = z1;
        	z1 = z0;
        }

    	real[b] = (z1*cos_num)/cos_den - z2;
    	imag[b] = (z1*sin_num)/sin_den;
    }
}
