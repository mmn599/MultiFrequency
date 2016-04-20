#ifndef MULTIFREQUENCY_DSP_H_
#define MULTIFREQUENCY_DSP_H_

#include "driverlib.h"
#include "constants.h"
#include <math.h>

void dft_float(uint16_t* data, uint32_t data_size, float* realresults, float* imagresults, float* powerresults);
void goertzels_float(uint16_t* data_buff, uint32_t data_size, uint32_t* bins, uint8_t bin_count, float* real, float* imag);
void goertzels_fixed(uint16_t* data, uint32_t data_size, uint32_t* bins, uint8_t bin_count, int32_t* real, int32_t* imag);


#endif /* MULTIFREQUENCY_DSP_H_ */
