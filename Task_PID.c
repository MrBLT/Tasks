/*
 * Task_PID.c
 *
 *  Created on: Apr 1, 2016
 *      Author: Brice Thrower
 *
 * 		Organization:	KU/EECS/EECS 690
 *
 *      Description: PID module to adjust duty cycle for a heater to control temperature
 *
 *      Notes:	This module will continuously calculate an error value (e) as
 *      	the difference between a desired temperature (Setpoint SP) and a
 *      	current temperature (Process Variable PV). The module will attempt
 *      	to minimize the error over time by adjusting the duty cycle (Manipulated
 *      	Variable MV) using a weighted sum.
 *
 *      Inputs: desired temperature (SP)
 *      		current temperature (PV)
 *
 *      Output: duty cycle (MV)
 *
 */

/*
   Psuedo-Code Algorithm for PID Controller
 
  	Read desired temperature (SP)
  	Read current temperature (PV)
   	
        Calculate error (e), update a running sum for (I), update a rate of change of e, 
   	
	    e = SP - PV;
	   
	Update a running sum for use in (I)

	    sum_e += e;

	Update the rate of change of e for use in (D)
	    
	    de = e - e_prev;

	Store e for later use

	    e_prev = e;

	Calculate output duty cycle (MV) by summing each component
	    (P) Proportional Control: MV is set in proportion to the existing e
	    
	        P = P_Gain * e;

	    (I) Integral Action: increase or decrease MV in small persistent steps that are 
	                         proportional to the current error. Over time the steps accumulate
			         and add up dependent on past errors
			     
		I = I_Gain * (integral or sum of past errors from 0 to t)

	    (D) Derivative Action: consider the rate of change of e, increase or decrease MV 
	                           depending on how fast the error is approaching zero
				   
		D = D_Gain * (derivative or rate of change of e)
 */

#include	"FreeRTOS.h"
#include	"task.h"

#include	"stdio.h"

//
// Global Subroutines and Variables
//

// Reference Desired Temp and Current Temp
float Desired_Temp = 31.5;
extern float Current_Temp;

// Initiate global output duty cycle
float MV;
float P_Gain = 1.1;
float I_Gain = 1;
float D_Gain = 1;

extern void Task_PID( void *pvParameters ) {

	float SP, PV, e, sum_e, de, prev_e = 0, P, I, D;

	while (1) {

		SP = Desired_Temp;
		PV = Current_Temp;
		e  = SP - PV;
		sum_e += e;
		de = e - prev_e;
		prev_e = e;

		P = P_Gain * e;
		I = I_Gain * sum_e;
		D = D_Gain * de;

		MV = P + I + D;

		printf("%6.2f, %6.2f, %6.2f, %6.2f, %6.2f, %6.2f, %6.2\n", e, sum_e, de, P, I, D, MV);
		vTaskDelay((configTICK_RATE_HZ));

	}
}

