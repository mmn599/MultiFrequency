/*
 * constants.h
 *
 *  Created on: Nov 18, 2015
 *      Author: matthew
 */

#ifndef MULTIFREQUENCY_CONSTANTS_H_
#define MULTIFREQUENCY_CONSTANTS_H_

#define NUM_BINS 1

#define DAC_SAMPLE_RATIO 2

#define LOOKUP_TABLE_SIZE 64
#define NUM_PERIODS 8
#define NUM_DATA LOOKUP_TABLE_SIZE * NUM_PERIODS / DAC_SAMPLE_RATIO
#define DATA_BEGIN LOOKUP_TABLE_SIZE / DAC_SAMPLE_RATIO

#include "driverlib.h"

extern const uint8_t DacTable_256_1[256];
extern const uint8_t DacTable_64_1[64];

#endif /* MULTIFREQUENCY_CONSTANTS_H_ */
