#include "system.h"

const eUSCI_UART_Config uartConfig = {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
			156,                                      // BRDIV = 78
            4,                                       // UCxBRF = 2
            0,                                       // UCxBRS = 0
            EUSCI_A_UART_NO_PARITY,                  // No Parity
            EUSCI_A_UART_LSB_FIRST,                  // MSB First
            EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
            EUSCI_A_UART_MODE,                       // UART mode
			EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

void ADC_Init() {
	ADC14_enableModule();

    /* Configuring GPIOs (5.5 A0) */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN5,
    GPIO_TERTIARY_MODULE_FUNCTION);

	ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1, ADC_NOROUTE);

	ADC14_setResolution(ADC_14BIT);
	ADC14_setSampleHoldTrigger(ADC_TRIGGER_ADCSC, false);
	ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_16, ADC_PULSE_WIDTH_16);

	ADC14_configureSingleSampleMode(ADC_MEM0, false);

	ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A0, false);

	ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
//	ADC14_setPowerMode(ADC_UNRESTRICTED_POWER_MODE);
	ADC14_enableConversion();
	/*
	 * 0b = ADC reference buffer on continuously
	 * BIT 2 (ADC14REFBURST) in ADC14CTL1 register
	 */
//	ADC14CTL1 &= ~(BIT2);
}

void CS_Init() {
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
            GPIO_PIN3 | GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION);
    CS_setExternalClockSourceFrequency(32000,48000000);
    PCM_setPowerState(PCM_AM_LDO_VCORE1);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    CS_startHFXT(false);
    CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_2);
}

void UART_Init() {
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
            GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    UART_initModule(EUSCI_A0_BASE, &uartConfig);
    UART_enableModule(EUSCI_A0_BASE);
}

void GPIO_Init() {
	P4DIR = 0xFF; //make pins 0-5 out
    P4OUT = 0;
}





