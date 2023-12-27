/********************		Author: TAHER MOHAMED	**************/
/********************		Layer: MCAL				**************/
/********************		SWC: TIMER1				**************/
/********************		Version: 1.00			**************/
/********************		Date: 28-8-2020			**************/
/*****************************************************************/
/*****************************************************************/
#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#define ICU_RISING_EDGE        1
#define ICU_FALLING_EDGE       0

u8 TIMER1_u8SetCallBack(void (*copy_pvCallBackFunc)(void));

void TIMER1_voidInitFastPWM(void);
void TIMER1_voidInitnorm(void);
void Timer1_voidSetTopValue(u16 u16_CopyValue);
void Timer1_voidSetChannelACompValue(u16 u16_CopyValue);
void Timer1_voidSetChannelBCompValue(u16 u16_CopyValue);
void TIMER1_voidSetRegisterValue(u16 u16Copy_Value );
u16 TIMER1_voidReadRegisterValue(void);



void ICU_voidInit(void);
void ICU_voidSetTriggerEdge(u8 Copy_edge);
void ICU_EnableINT(void);
void ICU_DisableINT(void);
u16 ICU_u16ReadInputCapture(void);
void ICU_voidSetCallBack(void (*copy_pvCallBackFunc)(void));

void servo(void);
void Timer1_voidSetTopValue(u16 u16_CopyValue);


#endif
