/*--Task_ReportTime.c
 *
 *  Author:			Brice Thrower
 *	Organization:	KU/EECS/EECS 690
 *  Date:			March 31, 2016
 *
 *  Description:	Converts global variable ADC_Value_Avg to Temperature in Celsius
 *
 *	Notes:			Uses global int Run_Time to initialize the conversion
 */


#include	"FreeRTOS.h"
#include	"task.h"

#include	"stdio.h"

//
// Global Subroutines and Variables
//
float Current_Temp;
extern uint32_t ADC_Value_Avg;
//
//	Reference SysTickCount
//
extern volatile uint32_t xPortSysTickCount;

float Get_Voltage(uint32_t ADC_Value_Avg){
	return ((ADC_Value_Avg*3.3)/4095);
}

extern void Task_Temp_Calc( void *pvParameters ) {

	while ( 1 ) {
		while(ADC_Value_Avg == 0){};
		Current_Temp = 91.9307 - (30.4555*Get_Voltage(ADC_Value_Avg));
		printf("%4.3f\n", Current_Temp);
		vTaskDelay( (configTICK_RATE_HZ) );
	}
}
