/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: ultrasonic.c
 *
 * Description: types for AVR
 *
 * Date Created: 10/10/2022
 *
 * Author: Moustafa Ahmed
 *
 *******************************************************************************/

/**-------------------------INCLUDES Section------------------------**/
#include "Libraries.h"
#include "GPIO.h"
#include "icu.h"
#include "ultrasonic.h"

/**-------------------------Global Variables Section----------------**/
uint8 	g_edgeCount = 0;
uint16 	g_timeHigh	= 0;
/**-------------------------Function Definition Section-------------**/
/*
 * Description:
 * Initialize the ICU driver as required
 * Setup the ICU callback function
 * Setting pin's directions
 */
void Ultrasonic_init(void)
{
	/*
	 * Setting the ICU as required
	 *  Normal Mode for channel A and B
	 *  Activate Force compare for channel A and B
	 *  Detect on raising edge
	 *  De-activate noise canceler
	 *  clock = F_CPU/8
	 *  Normal WaveForm
	 *  Enable Interrupt
	 */
	ICU_ConfigType Config = {Normal_A,Normal_B,Channel_A_ON,Channel_B_ON,RAISING_EDGE,NOISE_CANCELER_OFF,F_ICU8,NORMAL,ENABLE_INTERRUPT};
	Icu_init(&Config);

	/* Setting the callback function */
	Icu_setCallBack(Ultrasonic_edgeProcessing);

	/* Setting Trigger Pin as output Pin */
	GPIO_setupPinDirection(US_TriggerPort_ID, US_TriggerPin_ID, PIN_OUTPUT);

	/* Initializing g_edgeCount  */
	g_edgeCount = 0;

}
/*-------------------------------------------------------------------*/

/*
 * Description: Sends the trigger pulse to ultrasonic
 */
void Ultrasonic_Trigger(void)
{
	/* Activating the trigger pin for 10 micro-second */
	GPIO_writePin(US_TriggerPort_ID, US_TriggerPin_ID, LOGIC_HIGH);
	_delay_ms(10);
	GPIO_writePin(US_TriggerPort_ID, US_TriggerPin_ID, LOGIC_LOW);
}
/*-------------------------------------------------------------------*/
/*
 * Description: Sends the trigger pulse to UltraSonics Trigger function
 * start the measurement by the ICU from this moment
 * returns the measured distance in cm
 */
uint16 Ultrasonic_readDistance(void)
{
	/* Sending the trigger pulse to Ultra-sonic trigger function */
	Ultrasonic_Trigger();


	/* Calculating the distance */
		return ((g_timeHigh)/57.8);
}
/*-------------------------------------------------------------------*/

/*
 * Description:
 * This is the callback function called by the icu driver
 * used to calculate the high time pulse
 */
void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING_EDGE);
	}
	else if(g_edgeCount == 2)
	{
		g_edgeCount = 0;

		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();

		/* Detect falling edge */
		Icu_setEdgeDetectionType(RAISING_EDGE);

	}
}
/**---------------------------------END-----------------------------**/
