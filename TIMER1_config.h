/********************		Author: TAHER MOHAMED	**************/
/********************		Layer: MCAL				**************/
/********************		SWC: TIMER1				**************/
/********************		Version: 1.00			**************/
/********************		Date: 28-8-2020			**************/
/*****************************************************************/
/*****************************************************************/
#ifndef TIMER1_CONFIG_H_
#define TIMER1_CONFIG_H_

//Waveform Generation Mode
	/*
		Normal  							1
		PWM, Phase Correct, 8-bit			2
		PWM, Phase Correct, 9-bit			3
		PWM, Phase Correct, 10-bit			4
		CTC									5
		Fast PWM, 8-bit						6
		Fast PWM, 9-bit						7
		Fast PWM, 10-bit					8
		PWM, Phase and Frequency Correct	9
		PWM, Phase and Frequency Correct	10
		PWM, Phase Correct					11
		PWM, Phase Correct					12
		CTC									13
		Fast PWM							14
		Fast PWM							15
												*/

#define TIMER0_MODE         PWM_FAST_MODE
//clock select
	/*
		no_source :  0
		normal	  :  1
		clock/8   :  2
		clock/64  :  3
		clock/256 :  4
		clock/1024:  5
		E_S_T0_F_E:  6		External clock source on T0 pin. Clock on falling edge
		E_S_T0_R_E:  7		External clock source on T0 pin. Clock on raising edge
						*/
#define TIMER1_CLK_PRE      2

/*ctc outbut oc1a1__oc1b1*/
	/* 
		oc1a1/oc1b1 disconected  1
		oc1a1/oc1b1 toggle       2
		oc1a1/oc1b1 clear        3
		oc1a1/oc1b1 set          4
							*/

#define TIMER1_CTC_OC1   2

/*pwm FAST Mode*/
   /*
		oc1a1/oc1b1 disconected  								1
		Clear oc1a1/oc1b1 on compare match, set oc1a1/oc1b1 at TOP      2
		set oc1a1/oc1b1 on compare match, clear oc1a1/oc1b1 at TOP		3
															*/
#define TIMER1_PWM_F_MODE_OC1   2

/*Phase Correct PWM Mode*/
   /*
		oc1a1/oc1b1 disconected  																			1
		Clear oc1a1/oc1b1 on compare match when up-counting. Set oc1a1/oc1b1 on compare match when downcounting     2
		Set oc1a1/oc1b1 on compare match when up-counting. Clear oc1a1/oc1b1 on comparematch when downcounting		3
															*/
#define TIMER1_PWM_PH_MODE_OC1   2
				
#endif