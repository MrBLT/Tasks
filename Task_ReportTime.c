/*--Task_ReportTime.c
 *
 *  Author:			Gary J. Minden
 *	Organization:	KU/EECS/EECS 388
 *  Date:			February 23, 2016
 *
 *  Description:	Reports SysTickCount via printf.
 *
 */


#include	<stddef.h>
#include	<stdbool.h>
#include	<stdint.h>
#include	<stdarg.h>

#include	"FreeRTOS.h"
#include	"task.h"

#include	"stdio.h"

//
//	Reference SysTickCount
//
extern volatile uint32_t xPortSysTickCount;

extern void Task_ReportTime( void *pvParameters ) {

	//
	//	No set-up necessary
	//

	//
	//	Enter task loop
	//
	while ( 1 ) {
		printf( "%3d,", xPortSysTickCount/1000 );

		vTaskDelay( configTICK_RATE_HZ );
	}
}
