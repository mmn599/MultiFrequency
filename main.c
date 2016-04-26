#include "driverlib.h"
#include "constants.h"
#include "system.h"
#include "dsp.h"
#include "rf.h"

/*
 * Assembly functions
 */
typedef void ( *sample_function_ptr_t ) (uint16_t*, uint8_t*, uint32_t, uint32_t);
extern sample_function_ptr_t copy_to_ram();
extern void output_and_sample(uint16_t*, uint8_t*, sample_function_ptr_t, uint32_t);
extern void sampleLoop(uint16_t*, uint8_t*, sample_function_ptr_t, uint32_t);

int main(void) {
    WDT_A_holdTimer();

    CS_Init();
    ADC_Init();
    GPIO_Init();
    UART_Init();

    FPU_enableModule();

    uint8_t dac_table[LOOKUP_TABLE_SIZE];

    int i;
    for(i=0;i<LOOKUP_TABLE_SIZE;i++) {
    	dac_table[i] = DacTable_64_1[i];
    }

    sample_function_ptr_t sampleFunctionPointer = copy_to_ram();

    uint16_t data_buff[NUM_DATA];
	uint32_t bins[NUM_BINS] = {7};

	float real[NUM_BINS];
	float imag[NUM_BINS];

	i = 0;

    while(1) {
    	sampleLoop(data_buff, dac_table, sampleFunctionPointer, NUM_DATA);
    	goertzels_float(data_buff + DATA_BEGIN, NUM_DATA - DATA_BEGIN, bins, NUM_BINS, real, imag);
    	i++;
    }
}
