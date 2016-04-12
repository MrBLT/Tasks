//*****************************************************************************
//
//	Set up ADC_0 Channel_0 to sample voltage and report.
//
//		Author: 		Gary J. Minden
//		Organization:	KU/EECS/EECS 388
//		Date:			2016-02-29 (B60229)
//		Version:		1.0
//
//		Description:	Sample ADC_0_Channel_0 every 0.1 seconds, average 10 samples
//
//		Notes:
//
//*****************************************************************************
//

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#include "driverlib/sysctl.h"
#include "driverlib/adc.h"

#include "FreeRTOS.h"
#include "task.h"

#include "stdio.h"

//
//	Gloabal subroutines and variables
//
uint32_t ADC_Value_Avg = 0;

extern void Task_Simple_ADC0_Ch0( void *pvParameters ) {

	//
	//	Measured voltage value
	//
	uint32_t	ADC_Value;
	/*uint32_t	ADC_Value_Array[10];
	uint32_t 		ADC_Value_Position = 0;
	uint32_t 		i;
	uint32_t 		sum;*/
	float alpha = 0.3;
	uint32_t Old_ADC_Value_Avg = 0;


	//
	//	Enable (power-on) ADC0
	//
	SysCtlPeripheralEnable( SYSCTL_PERIPH_ADC0 );

	//
	// Enable the first sample sequencer to capture the value of channel 0 when
	// the processor trigger occurs.
	//
	ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);

	ADCSequenceStepConfigure( ADC0_BASE, 0, 0,
								ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0 );

	ADCSequenceEnable( ADC0_BASE, 0 );

//	printf( ">>>>ADC Initialized.\n");

	while ( 1 ) {

		//
		// Trigger the sample sequence.
		//
		ADCProcessorTrigger(ADC0_BASE, 0);

		//
		// Wait until the sample sequence has completed.
		//
		while( !ADCIntStatus( ADC0_BASE, 0, false )) {
		}

		//
		// Read the value from the ADC.
		//
		ADCSequenceDataGet(ADC0_BASE, 0, &ADC_Value);
		ADCIntClear( ADC0_BASE, 0 );
/*
		//
		// Insert the value into a position in the array
		//
		if( ADC_Value_Position == 9) {
			ADC_Value_Array[ADC_Value_Position] = ADC_Value;

			sum = 0;
			for(i = 0; i <= 9; i++){
				sum += ADC_Value_Array[i];
			}
			ADC_Value_Avg = sum/10;
			ADC_Value_Position = 0;
			//
			//	Print ADC_Value
			//

			//printf( "ADC_Value_Avg: %6d, ", ADC_Value_Avg );
		} else {
			ADC_Value_Array[ADC_Value_Position] = ADC_Value;
			ADC_Value_Position++;
		}
*/
		//
		// Update Running Average
		//
		if(Old_ADC_Value_Avg == 0){
			ADC_Value_Avg = ADC_Value;
		} else {
			ADC_Value_Avg = alpha*ADC_Value + (1 - alpha)*Old_ADC_Value_Avg;
		}

		Old_ADC_Value_Avg = ADC_Value_Avg;

		//printf("%6d, ", ADC_Value_Avg);
		//
		//	Delay 100 ms.
		//
		vTaskDelay( (configTICK_RATE_HZ) );
	}
}
