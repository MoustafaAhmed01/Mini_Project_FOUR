/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: ICU.c
 *
 * Description: types for AVR
 *
 * Date Created: 9/10/2022
 *
 * Author: Moustafa Ahmed
 *
 *******************************************************************************/

/**-------------------------INCLUDES Section------------------------**/
#include "Libraries.h"
#include "GPIO.h"
#include "icu.h"

/**-------------------------Global Variables Section----------------**/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/**-------------------------Interrupt Section-----------------------**/
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/**-------------------------Function Definition Section-------------**/

/* Initializing ICU */
void Icu_init(const ICU_ConfigType * Config_Ptr)
{
	/* Setting the pin direction */
	GPIO_setupPinDirection(ICU_PORT_ID,ICU_PIN_ID,PIN_INPUT);

	/* Compare Output Mode for channel A */
	TCCR1A = (TCCR1A & 0x7F) | (Config_Ptr->CompareModeA<<6);

	/* Compare Output Mode for channel B */
	TCCR1A = (TCCR1A & 0xBF) | (Config_Ptr->CompareModeB<<4);

	/* Force Output Compare for Channel A */
	TCCR1A = (TCCR1A & 0xF7) | (Config_Ptr->ForceCompareA<<3);

	/* Force Output Compare for Channel B */
	TCCR1A = (TCCR1A & 0xFB) | (Config_Ptr->ForceCompareB<<2);

	/* Setting the waveform */
	TCCR1A = (TCCR1A & 0xFC) | ((Config_Ptr->WaveForm<<6)>>6); /* Getting the first 2 bits only */
	TCCR1B = (TCCR1B & 0xE7) | ((Config_Ptr->WaveForm>>2)<<3); /* Getting bit 2 and 3 only*/

	/* Noise Canceler */
	TCCR1B = (TCCR1B & 0x7F) | ((Config_Ptr->NoiseControl)<<7);

	/* Clock Selection */
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->F_ICU_CLOCK);

	/* insert the required edge type in ICES1 bit in TCCR1B Register */
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->EdgeControl)<<6);

	/* Enable the Input Capture interrupt to generate an interrupt when edge is detected on ICP1/PD6 pin */
	TIMSK = (TIMSK & 0xDF) | ((Config_Ptr->InterruptActivate)<<5);

	/* Initial Value for Timer1 */
	TCNT1 = 0;

	/* Initial Value for the input capture register */
	ICR1 = 0;
}

/*----------------------------------------------------------------------------*/

/* Description: Function to set the Call Back function address. */
void Icu_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
/*-------------------------------------------------------------------*/

/* Description: Function to set the required edge detection.*/
void Icu_setEdgeDetectionType(const uint8 edgeType)
{
	/* Input Capture Edge select */
	TCCR1B = (TCCR1B & 0xBF) | ((edgeType)<<6);
}
/*-------------------------------------------------------------------*/

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 Icu_getInputCaptureValue(void)
{
	return ICR1;
}
/*-------------------------------------------------------------------*/

/* Description: Function to clear the Timer1 Value to start count from ZERO */
void Icu_clearTimerValue(void)
{
	TCNT1 = 0;
}
/*-------------------------------------------------------------------*/

/* Description: Function to disable the Timer1 to stop the ICU Driver */
void Icu_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
}
/**---------------------------------END-----------------------------**/
