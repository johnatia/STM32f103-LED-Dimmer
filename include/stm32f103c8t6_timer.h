/**
 * @ Author 	: 	John Atia Nafady
 * @ Date 		: 	5-5-2021
 * @ Version	:	V03
 *
 */

#ifndef _TIMER_H_
#define _TIMER_H_

/**
 * @Register of TIMERs in STM32f103c8t6
 */

typedef struct{
	volatile u32 CR1		;
	volatile u32 CR2		;
	volatile u32 SMCR		;
	volatile u32 DIER		;
	volatile u32 SR			;
	volatile u32 EGR    	;
	volatile u32 CCMR1  	;
    volatile u32 CCMR2  	;
    volatile u32 CCER   	;
    volatile u32 CNT    	;
    volatile u32 PSC    	;
    volatile u32 ARR    	;
	volatile u32 RCR		;		//This Register is for Timer 1 only and Reserved for Timer 2 , 3 , 4
    volatile u32 CCR[4]   	;
//    volatile u32 CCR2   	;
//    volatile u32 CCR3   	;
//    volatile u32 CCR4   	;
    volatile u32 BDTR 		;		//This Register is for Timer 1 only and Reserved for Timer 2 , 3 , 4
	volatile u32 DCR    	;
	volatile u32 DMAR   	;
}TIMx_TypeDef;
#define 		TIM1_BASE_ADDRESS				0x40012C00
#define 		TIM2_BASE_ADDRESS				0x40000000
#define 		TIM3_BASE_ADDRESS				0x40000400
#define 		TIM4_BASE_ADDRESS				0x40000800
#define 		TIM1							((TIMx_TypeDef*)(TIM1_BASE_ADDRESS))
#define 		TIM2							((TIMx_TypeDef*)(TIM2_BASE_ADDRESS))
#define 		TIM3							((TIMx_TypeDef*)(TIM3_BASE_ADDRESS))
#define 		TIM4							((TIMx_TypeDef*)(TIM4_BASE_ADDRESS))
#define 		SINGLE_INTERVAL					0
#define 		PERIODIC_INTERVAL				1

/**
 * @Enums for Configurations
 *
 */

typedef enum
{
	TIM_NoClkDivison 		= 0b00,
	TIM_SysClkDivisonBy_2 	= 0b01,
	TIM_SysClkDivisonBy_4 	= 0b10
}TIM_SysClkDivison_t;
typedef enum
{
	UP_COUNTER   = 0,
	DOWN_COUNTER = 1
}COUNTER_Mode_t;
typedef	enum
{
	TIM_CHANNEL_1,
	TIM_CHANNEL_2,
	TIM_CHANNEL_3,
	TIM_CHANNEL_4
}TIM_Channel_t;
typedef enum
{
	//For Timer2:
	//TIM2_NoRemap is TIM2_CH1_ETR on PA0, TIM2_CH2 on PA1, TIM2_CH3 on PA2, TIM2_CH4 on PA3
	TIM2_NoRemap = 0b00,
	//TIM2_REMAP1 is TIM2_CH1_ETR on PA15, TIM2_CH2 on PB3, TIM2_CH3 on PA2, TIM2_CH4 on PA3
	TIM2_Remap1  = 0b01,
	//TIM2_REMAP2 is  TIM2_CH1_ETR on PA0, TIM2_CH2 on PA1, TIM2_CH3 on PB10, TIM2_CH4 on PB11
	TIM2_Remap2  = 0b10,
	//TIM2_REMAP3 is TIM2_CH1_ETR on PA15, TIM2_CH2 on PB3, TIM2_CH3 on PB10, TIM2_CH4 on PB11
	TIM2_Remap3  = 0b11
}TIM_REMAP_t;

typedef enum
{
	ActiveHigh = 0,
	ActiveLow

}TIM_ChannelPolarity_t;

typedef enum
{
	PWM_MODE_1 = 1,
	PWM_MODE_2
}PWM_Mode_t;



typedef enum
{
	TIMER1 = 0,
	TIMER2,
	TIMER3,
	TIMER4
}TIMERx_t;

/**
 * @Timers Functions
 */
void TIM_voidInit(TIMERx_t TIMERx , TIM_SysClkDivison_t TIM_SysClkDivison , COUNTER_Mode_t COUNTER_Mode);
void TIM_voidDelay(TIMERx_t TIMERx , u16 TIM_u16Prescaler , u16 TIM_u16Ticks );
void TIM_voidSetSingleInterval(TIMERx_t TIMERx, u16 TIM_u16Prescaler ,  u16 TIM_u16Ticks , void(*PtrToFunc)(void) );
void TIM_voidSetPeriodicInterval(TIMERx_t TIMERx ,  u16 TIM_u16Prescaler , u16 TIM_u16Ticks , void(*PtrToFunc)(void) );
u16  TIM_u16GetElapsedTime(TIMERx_t TIMERx);
u16  TIM_u16GetRemainingTime(TIMERx_t TIMERx);
void TIM_voidRemapChannel(TIMERx_t TIMERx,TIM_REMAP_t TIM_REMAP);
void TIM_voidConfigurePWM(TIMERx_t TIMERx, TIM_Channel_t TIM_Channel_x , TIM_ChannelPolarity_t TIM_ChannelPolarity , PWM_Mode_t PWM_Mode_x);
void TIM_voidSetDutyCycle(TIMERx_t TIMERx, TIM_Channel_t TIM_Channel_x , u16 TIM_u16DutyCycle );
void TIM_voidStartPWM(TIMERx_t TIMERx, u16 TIM_u16Prescaler , u16 TIM_u16Period);



#endif
