/***********************************************************************/
/***********************************************************************/
/*****************    AUTHOR: TAHER MOHAMED   **************************/
/*****************    LAYER:  MCAL            **************************/
/*****************    SWC:    GIE             **************************/
/*****************    VERSION:1.00            **************************/
/***********************************************************************/
/***********************************************************************/
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "GIE_register.h"
#include "GIE_interface.h"


void GIF_voidEnable(void)
{
	SET_BIT(SREG,SREG_I);
}
void GIF_voidDisable(void)
{
	CLR_BIT(SREG,SREG_I);
}
