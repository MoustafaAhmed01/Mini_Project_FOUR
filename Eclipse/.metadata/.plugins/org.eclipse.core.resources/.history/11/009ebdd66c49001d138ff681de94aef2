/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: ADC.h
 *
 * Description: types for AVR
 *
 * Date Created: 3/10/2022
 *
 * Author: Moustafa Ahmed
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/**-------------------------INCLUDES Section------------------------**/
#include "std_types.h"
/**-------------------------Definitions & Config Section------------**/
#define SoundSpeed 				34000
#define US_TriggerPort_ID		PORTB_ID
#define US_TriggerPin_ID		PIN5_ID
/**-------------------------Enum Section----------------------------**/

/**-------------------------Struct Section--------------------------**/

/**-------------------------Function Dec. Section-------------------**/
/*
 * Description:
 * Initialize the ICU driver as required
 * Setup the ICU callback function
 * Setting pin's directions
 */
void Ultrasonic_init(void);
/*-------------------------------------------------------------------*/

/*
 * Description: Sends the trigger pulse to ultrasonic
 */
void Ultrasonic_Trigger(void);
/*-------------------------------------------------------------------*/

/*
 * Description: Sends the trigger pulse to UltraSonics Trigger function
 * start the measurement by the ICU from this moment
 * returns the measured distance in cm
 */
uint16 Ultrasonic_readDistance(void);
/*-------------------------------------------------------------------*/

/*
 * Description:
 * This is the callback function called by the icu driver
 * used to calculate the high time pulse
 */
void Ultrasonic_edgeProcessing(void);
/**-------------------------END-------------------------------------**/


#endif /* ULTRASONIC_H_ */
