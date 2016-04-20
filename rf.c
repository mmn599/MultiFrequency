#include "rf.h"

void sendDFTUART(uint16_t* data_buff, float* power_k, uint32_t data_size) {
	int dataIdx = 0;
	for(dataIdx = 0; dataIdx < data_size; dataIdx++) {
		uint32_t value = data_buff[dataIdx];
		int i;
		UART_transmitData(EUSCI_A0_BASE, 'a');
		for(i=0;i<4;i++) {
	    	uint8_t data_byte = value>>(i*8);
	    	UART_transmitData(EUSCI_A0_BASE, data_byte);
		}
	}
	for(dataIdx = 0; dataIdx < data_size; dataIdx++) {
		uint32_t value = (uint32_t) power_k[dataIdx];
		int i;
		UART_transmitData(EUSCI_A0_BASE, 'a');
		for(i=0;i<4;i++) {
		    uint8_t data_byte = value>>(i*8);
		    UART_transmitData(EUSCI_A0_BASE, data_byte);
		}
	}
}

void sendDataBuffUART(uint16_t* data_buff, uint32_t data_size) {
	int dataIdx = 0;
	for(dataIdx = 0; dataIdx < data_size; dataIdx++) {
		uint32_t value = data_buff[dataIdx];
		int i;
		UART_transmitData(EUSCI_A0_BASE, 'a');
		for(i=0;i<4;i++) {
	    	uint8_t data_byte = value>>(i*8);
	    	UART_transmitData(EUSCI_A0_BASE, data_byte);
		}
	}
}

void sendGoertzDataUART(uint32_t num, float* real, float* imag) {
	int dataIdx = 0;
	for(dataIdx = 0; dataIdx < num; dataIdx++) {
		int i;
		UART_transmitData(EUSCI_A0_BASE, 'a');
		for(i=0;i<4;i++) {
	    	uint8_t data_byte = 0; //real[dataIdx]>>(i*8);
	    	UART_transmitData(EUSCI_A0_BASE, data_byte);
		}
		UART_transmitData(EUSCI_A0_BASE, 'a');
		for(i=0;i<4;i++) {
			uint8_t data_byte = 0; //imag[dataIdx]>>(i*8);
			UART_transmitData(EUSCI_A0_BASE, data_byte);
		}
	}
}



