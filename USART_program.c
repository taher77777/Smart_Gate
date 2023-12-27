#include "STD_TYPE.h"
#include "BIT_MATH.h"

#include "USART_register.h"
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

/*Global pointer to function to hold receive ISR address*/
void (*USART_pvReceiveFunc)(u8 copy_u8received)=NULL;

void USART_voidInit(void)
{
	if (INTERRUPT==UART_WITH_INTERRUPT)
	{
		u8 Local_u8UCSRCValue=0;
		/*open interrupt to Receive Complete */
		SET_BIT(UCSRB,UCSRB_RXCIE);
		/*open interrupt to transmit Complete */
		SET_BIT(UCSRB,UCSRB_TXCIE);

		//****** we cannot use get and set bit with ucsrc we will create variable help us ****//

		//to use UCSRC
		SET_BIT(Local_u8UCSRCValue,UCSRC_URSEL);

		//set to 8 bit send and receive
		CLR_BIT(UCSRB,UCSRB_UCSZ2);
		SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
		SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);

		/* mode select
		 	 	 	      1-Synchronous
		 	 	 	      2-ASynchronous */
		//ASynchronous
		CLR_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);

		// now will set this value in UCSRC at same time
		UCSRC=Local_u8UCSRCValue;

		//boudrate now 9600 with 8Mhz
		UBRRL=UART_BOUDRATE;

		//enable pins recieve & transmit
		SET_BIT(UCSRB,UCSRB_TXEN);
		SET_BIT(UCSRB,UCSRB_RXEN);

	}
	else if (INTERRUPT==UART_WITHOUT_INTERRUPT)
	{
	/*we can not use set bit or clr bit here because it want in same time so we will creat a variable*/
	u8 Local_u8UCSRCValue=0;
	SET_BIT(Local_u8UCSRCValue,UCSRC_URSEL);  //to use UCSRC
	//set to 8 bit send and receive
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	// now will set this value in UCSRC at same time
	UCSRC=Local_u8UCSRCValue;
	//boudrate now 9600 with 8Mhz
	UBRRL=UART_BOUDRATE;
	
	//enable
	SET_BIT(UCSRB,UCSRB_TXEN);   //tx enable
	SET_BIT(UCSRB,UCSRB_RXEN);   //rx enable
	}
}


//function to receive data no 8bit
u8 USART_u8Receive(void)
{
	//wait until be low by default it high when receive become low
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);
	//return the receive data
	return UDR;
}

void USART_voidSend(u8 Copy_u8data)
{
	//wait until transmit data empty
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
	UDR=Copy_u8data;   //transmit data
}

//send string
void USART_voidSendString(u8 *str)
{
        u8 i;
        for(i=0;i<100;i++) {
                if((*(str+i))==0)
                        break;
                UDR=*(str+i);
        }
}

/*part of interrupt*/

void USART_voidRecieveSetCallBack(void (*Copy_pvRecieveFunc)(u8 copy_u8received))
{
	USART_pvReceiveFunc=Copy_pvRecieveFunc;
}


void __vector_13 (void)  __attribute__((signal));
void __vector_13 (void)
{
	if(USART_pvReceiveFunc != NULL)
	{
		USART_pvReceiveFunc(UDR);
	}
	else
	{
		/*Do nothing*/
	}
}

