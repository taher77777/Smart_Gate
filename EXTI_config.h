/********************		Author: TAHER MOHAMED	**************/
/********************		Layer: MCAL				**************/
/********************		SWC: EXTI				**************/
/********************		Version: 1.00			**************/
/********************		Date: 28-8-2020			**************/
/*****************************************************************/
/*****************************************************************/

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

/*INT0*/
/*Options:		
			1- LOW_LEVEL
			2- ON_CHANGE
			3- FALLING_EDGE	
			4- RISING_EDGE				
								*/		
#define INT0_SENSE			FALLING_EDGE

/*Options:
			1- ENABLED
			2- DISABLED
								*/
#define INT0_INITIAL_STATE	 ENABLED
/*INT1*/

/*Options:		
			1- LOW_LEVEL
			2- ON_CHANGE
			3- FALLING_EDGE	
			4- RISING_EDGE				
								*/		
#define INT1_SENSE			FALLING_EDGE

/*Options:
			1- ENABLED
			2- DISABLED
								*/
#define INT1_INITIAL_STATE	DISABLED

/*INT2*/
/*Options:		
			1- FALLING_EDGE	
			2- RISING_EDGE				
								*/		
#define INT2_SENSE			FALLING_EDGE

/*Options:
			1- ENABLED
			2- DISABLED
								*/
#define INT2_INITIAL_STATE	DISABLED

#endif
