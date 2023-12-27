 /*system
			1-USART
			    RX____PORTD_PIN0_DIR  input   0
			    TX____PORTD_PIN1_DIR  output  0
			2-EXTI
				INT0__PORTD_PIN2_DIR  input   1
			3-CLCD
				DATA_PORTA           output   0

			4-ultrasonic sensor
			    echo___PORTD_PIN6    input    0
			    trig___portd_pin7    output   0

			5-keypad
				PORTC                 input   1
			6_servo   __D_5           output  0

			6-2_leds
			    __D_4                output   0
			    __B_4                output   0
 */
//======================================================================================================================
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "USART_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"
#include "KEYPAD_interface.h"
#include "TIMER1_interface.h"
#include <util/delay.h>

//========================================================================================================================

//function to received interrupt
void UART_RECIEVED_INTERRUPT(u8 copy_u8received);

//function if received 1
void Fun1(void);
//function if received 2
void Fun2(void);
//function if received 3
void Fun3(void);
//function if received name + 0
void DISPLAY_NAME(u8 COPY);
//switch interrupt
void SW_INTERRUPT(void);
void trigger(void);
void ICU_HW(void);
//servo
void servon (void);
//============================================================================================================================
void main(void)
{
	PORT_voidInit();
	CLCD_voidInit();

	USART_voidRecieveSetCallBack(UART_RECIEVED_INTERRUPT);
	USART_voidInit();
	TIMER1_voidInitnorm();
	ICU_voidSetCallBack(ICU_HW);
	ICU_voidInit();
	EXTI_u8Int0SetCallBack(SW_INTERRUPT);
	EXTI_voidInt0Init();
	GIF_voidEnable();

	while(1)
	{
trigger();
		//do nothing
	}
}


//===============================================================================================================================

void UART_RECIEVED_INTERRUPT(u8 copy_u8received)
{
	switch(copy_u8received)
	{
	case '1':Fun1()            ; break;
	case '2':Fun2()            ; break;
	case '3':Fun3()            ; break;
	default:DISPLAY_NAME(copy_u8received); break;
	}
}


//switch interrupt
void SW_INTERRUPT(void)
{
	u8 ps[4]={1,2,3,4};
	u8 PS_COUNTER=0;
	u8 PS_VALEO[4];
	u8 KEY_P;
	CLCD_voidClearDisplay();
	CLCD_voidSendString("ENTER PASWORD");

	while(PS_COUNTER==4)
	{
		KEY_P=KPD_u8PressedKey();
		if(KEY_P!=0xff)
		{
			PS_VALEO[PS_COUNTER]=KEY_P;

			PS_COUNTER++;
			if(KEY_P==16)
			{

				if((PS_VALEO[0]==ps[0])&&(PS_VALEO[1]==ps[1])&&(PS_VALEO[2]==ps[2])&&(PS_VALEO[3]==ps[3]))
				{
					CLCD_voidClearDisplay();
					CLCD_voidSendString("correct PSW");
				}
				else
				{
					CLCD_voidClearDisplay();
					CLCD_voidSendString("wrong PSW");
					SW_INTERRUPT();

				}
			}
		}
	}
}




void Fun1(void)
	{
//open gate
		CLCD_voidClearDisplay();
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8PIN_HIGH);

		servon();
		_delay_ms(2000);
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8PIN_LOW);

	}
void Fun2(void)
	{
	//
		CLCD_voidClearDisplay();
		CLCD_voidSendString(" take of mask");
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_HIGH);
		_delay_ms(2000);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_LOW);
	}
void Fun3(void)
	{
		CLCD_voidClearDisplay();
		CLCD_voidSendString("wear mask");
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_HIGH);
		_delay_ms(2000);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_LOW);
	}
void DISPLAY_NAME(u8 COPY)
	{
		static u8 NAME_COUNT=0;
		if (NAME_COUNT==0)
		{
			CLCD_voidClearDisplay();
			CLCD_voidSendString("welcome ");
			CLCD_voidSendData(COPY);
			NAME_COUNT++;
		}
		else if (COPY=='0')
		{
			NAME_COUNT=0;
		}
		else
		{
			CLCD_voidSendData(COPY);
		}
	}
void trigger(void)
{
 DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);
 DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_HIGH);
 _delay_us(10);
 DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);
}

void ICU_HW()
{
	static u32 reading1,reading2;
	static count=0;
	u32 ontime=0;
	u32 disteance=0;
	if (count==0)
	{
		reading1=ICU_u16ReadInputCapture();
		count++;
		ICU_voidSetTriggerEdge(ICU_FALLING_EDGE);
	}
	else if (count==1)
	{
		reading2=ICU_u16ReadInputCapture();
		ICU_voidSetTriggerEdge(ICU_RISING_EDGE);
		ontime=reading2-reading1;
		disteance=ontime/57;
		if(disteance>3)
		{
			USART_voidSend('1');
		}
		else
		{
			USART_voidSend('0');
		}
		count=0;
	}
}

void servon(void)
{

	GIF_voidEnable();
	servo();
	Timer1_voidSetTopValue(20000);

		Timer1_voidSetChannelACompValue(0);
			_delay_ms(500);
			Timer1_voidSetChannelACompValue(1500);
			_delay_ms(500);
			Timer1_voidSetChannelACompValue(0);
			_delay_ms(500);
			Timer1_voidSetChannelACompValue(1500);
			_delay_ms(500);


	TIMER1_voidInitnorm();
}
