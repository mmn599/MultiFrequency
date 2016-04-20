/*
 * rf.h
 *
 *  Created on: Nov 18, 2015
 *      Author: matthew
 */

#ifndef MULTIFREQUENCY_RF_H_
#define MULTIFREQUENCY_RF_H_

#include "driverlib.h"

void sendDFTUART(uint16_t* data_buff, float* power_k, uint32_t data_size);
void sendDataBuffUART(uint16_t* data_buff, uint32_t data_size);
void sendGoertzDataUART(uint32_t num, float* real, float* imag);

#endif /* MULTIFREQUENCY_RF_H_ */
