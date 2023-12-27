
#include "STD_TYPE.h"
#include "BIT_MATH.h"

#include "TIMER1_register.h"
#include "TIMER1_private.h"
#include "TIMER1_config.h"
#include "TIMER1_interface.h"


static void (*ICU_pvCallBackFunc)(void)=NULL;

void TIMER1_voidInitnorm(void)
{
	//normal mode
	CLR_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

	//prescaler divide by 8
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
}


void TIMER1_voidInitFastPWM(void)
{
	//Compare Output Mode, Fast PWM
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	
	//Waveform Generation Mode fast pwm 
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1B_WGM13);
	
	//prescaler divide by 8
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
	
}


void Timer1_voidSetChannelBCompValue(u16 u16_CopyValue)
{
	OCR1B=u16_CopyValue;
}
void TIMER1_voidSetRegisterValue(u16 u16Copy_Value)
{
	TCNT1=u16Copy_Value;
}
u16 TIMER1_voidReadRegisterValue(void)
{
	return TCNT1 ;
}

void ICU_voidInit(void)
{
	SET_BIT(TCCR1B,TCCR1B_ICES1);
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

void ICU_voidSetTriggerEdge(u8 Copy_edge)
{
	if(Copy_edge==ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if(Copy_edge==ICU_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
}

void ICU_EnableINT(void)
{
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

void ICU_DisableINT(void)
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

u16 ICU_u16ReadInputCapture(void)
{
	return ICR1;
}
void ICU_voidSetCallBack(void (*copy_pvCallBackFunc)(void))
{
	ICU_pvCallBackFunc=copy_pvCallBackFunc;
}
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	if(ICU_pvCallBackFunc!=NULL)
	{
		ICU_pvCallBackFunc();
	}
}

void servo(void)
{
	//Compare Output Mode, Fast PWM
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

	//Waveform Generation Mode fast pwm
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1B_WGM13);

	//prescaler divide by 8
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);



}
void Timer1_voidSetTopValue(u16 u16_CopyValue)
{
	ICR1=u16_CopyValue;
}
void Timer1_voidSetChannelACompValue(u16 u16_CopyValue)
{
	OCR1A=u16_CopyValue;
}
