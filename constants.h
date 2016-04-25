/*
 * constants.h
 *
 *  Created on: Nov 18, 2015
 *      Author: matthew
 */

#ifndef MULTIFREQUENCY_CONSTANTS_H_
#define MULTIFREQUENCY_CONSTANTS_H_

#define NUM_DATA_IN_PERIOD 128
#define NUM_BINS 1
#define NUM_PERIODS 2
#define NUM_DATA NUM_DATA_IN_PERIOD * NUM_PERIODS

#include "driverlib.h"

extern const uint8_t DacTable_128_1[128];
extern const uint8_t DacTable_128_1_3_5[128];
extern const uint8_t DacTable_256_1[256];
extern const uint8_t DacTable_256_1_3_5[256];
//extern const uint8_t DacTable_296_1_3_5[296];
//extern const uint8_t DacTable_296_1[296];
//extern const uint8_t DacTable_100_1[100];

#endif /* MULTIFREQUENCY_CONSTANTS_H_ */
