/*
 * Task_PID.c
 *
 *  Created on: Apr 1, 2016
 *      Author: Brice Thrower
 *
 *      Description: PID module to adjust duty cycle for a heater to control temperature
 *
 *      Notes:	This module will continuously calculate an error value (e) as
 *      	the difference between a desired temperature (Setpoint SP) and a
 *      	current temperature (Process Variable PV). The module will attempt
 *      	to minimize the error over time by adjusting the duty cycle (Manipulated
 *      	Variable MV) using a weighted sum.
 *
 *      Inputs:
 *
 *      Output:
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
