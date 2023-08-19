/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: ICU.h
 *
 * Description: types for AVR
 *
 * Date Created: 9/10/2022
 *
 * Author: Moustafa Ahmed
 *
 *******************************************************************************/

#ifndef ICU_H_
#define ICU_H_

/**-------------------------INCLUDES Section------------------------**/
#include "std_types.h"

/**-------------------------Definitions & Config Section------------**/

#define ICU_PORT_ID		PORTD_ID
#define ICU_PIN_ID		PIN6_ID

/**-------------------------Enum Section----------------------------**/
/* Compare Output Mode for channel A */
typedef enum
{
	Normal_A,Toggle_A,Clear_A,Set_A
}ICU_CompareModeA;
/*-------------------------------------------------------------------*/

/* Compare Output Mode for channel B */
typedef enum
{
	Normal_B,Toggle_B,Clear_B,Set_B
}ICU_CompareModeB;
/*-------------------------------------------------------------------*/

/* Force Output Compare for channel A*/
typedef enum
{
	Channel_A_OFF,Channel_A_ON
}ICU_ForceCompareA;
/*-------------------------------------------------------------------*/

/* Force Output Compare for channel B*/
typedef enum
{
	Channel_B_OFF,Channel_B_ON
}ICU_ForceCompareB;
/*-------------------------------------------------------------------*/

/* Input capture noise canceler */
typedef enum
{
	NOISE_CANCELER_OFF,NOISE_CANCELER_ON
}ICU_NoiseControl;
/*-------------------------------------------------------------------*/

/* Input capture edge select */
typedef enum
{
	FALLING_EDGE,RAISING_EDGE
}ICU_EdgeControl;
/*-------------------------------------------------------------------*/

/* Controlling the waveform generation */
typedef enum
{
	NORMAL,PHASE_CORRECT_8,PHASE_CORRECT_9,PHASE_CORRECT_10,CTC_OCR1A,
	FAST_PWM_8,
	FAST_PWM_9,FAST_PWM_10,PWM_P_F_CORRECT_ICR1,PWM_P_F_CORRECT_OCR1A,
	PWM_PHASE_CORRECT_ICR1,PWM_PHASE_CORRECT_OCR1A,CTC_ICR1,RESERVED,
	FAST_PWM_OCR1,
	FAST_PWM_OCR1A

}ICU_WaveForm;
/*-------------------------------------------------------------------*/

/* Clock Select pre-scaling */
typedef enum
{
	NO_CLOCK,NO_PRESCALING,F_ICU8,F_ICU64,F_ICU256,F_ICU1024,EX_FALLING,
	EX_RISING
}ICU_ClockSelect;
/*-------------------------------------------------------------------*/

/* Interrupt Register */
typedef enum
{
	DISABLE_INTERRUPT, ENABLE_INTERRUPT
}ICU_InterruptActivate;

/**-------------------------Struct Section--------------------------**/

/* Config Structure */
typedef struct
{
	ICU_CompareModeA CompareModeA;
	ICU_CompareModeB CompareModeB;
	ICU_ForceCompareA ForceCompareA;
	ICU_ForceCompareB ForceCompareB;
	ICU_EdgeControl EdgeControl;
	ICU_NoiseControl NoiseControl;
	ICU_ClockSelect F_ICU_CLOCK;
	ICU_WaveForm WaveForm;
	ICU_InterruptActivate InterruptActivate;

}ICU_ConfigType;
/**-------------------------Function Dec. Section-------------------**/

/* Initializing ICU */
void Icu_init(const ICU_ConfigType * Config_Ptr);
/*-------------------------------------------------------------------*/

/* Description: Function to set the Call Back function address. */
void Icu_setCallBack(void(*a_ptr)(void));
/*-------------------------------------------------------------------*/

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 Icu_getInputCaptureValue(void);
/*-------------------------------------------------------------------*/

/* Description: Function to set the required edge detection.*/
void Icu_setEdgeDetectionType(const uint8 edgeType);
/*-------------------------------------------------------------------*/

/* Description: Function to clear the Timer1 Value to start count from ZERO */
void Icu_clearTimerValue(void);
/*-------------------------------------------------------------------*/

/* Description: Function to disable the Timer1 to stop the ICU Driver */
void Icu_DeInit(void);

/**-------------------------END-------------------------------------**/


#endif /* ICU_H_ */
