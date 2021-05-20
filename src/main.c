/**
 * @Author					:			John Atia Nafady
 * @Date					: 			20-4-2021
 * @Version					:			V02
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "stm32f103c8t6_rcc.h"
#include "stm32f103c8t6_nvic.h"
#include "stm32f103c8t6_gpio.h"
#include "stm32f103c8t6_afio.h"
#include "stm32f103c8t6_exti.h"
#include "stm23f103c8t6_dma.h"
#include "stm32f103c8t6_timer.h"
#include "stm32f103c8t6_usart.h"
#include "stm32f103c8t6_spi.h"


volatile s16 x =0;
volatile u8 bool = 0;
void BlinkLED(void)
{
	GPIO_voidSetPinValue(GPIOC , PIN13 , bool);
	GPIO_voidSetPinValue(GPIOB , PIN3 , bool);
	bool ^= (1<<0);

}

void main(void)
{
	s16 x = 0;
	/* Initialize Clock */
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2, 2); 	//Enable RCC for GPIOA
	RCC_voidEnableClock(RCC_APB2, 3); 	//Enable RCC for GPIOB
	RCC_voidEnableClock(RCC_APB2, 4); 	//Enable RCC for GPIOC
	RCC_voidEnableClock(RCC_APB2, 0); 	//Enable RCC for AFIO
	RCC_voidEnableClock(RCC_APB2, 11);	//Enable RCC for TIMER1
	RCC_voidEnableClock(RCC_APB1 , 0);	//Enable RCC for GPTimer2
	RCC_voidEnableClock(RCC_APB1 , 1);	//Enable RCC for GPTIMER3
	RCC_voidEnableClock(RCC_APB1 , 2);	//Enable RCC for GPTIMER4

	AFIO_voidConfigDebugPort(EnableSWD_DisableJTAG);

	//AFIO_voidTimerRemapPin(TIMER2, TIM2_REMAP1);
	TIM_voidInit(TIMER1, TIM_NoClkDivison, UP_COUNTER);
	TIM_voidInit(TIMER2, TIM_NoClkDivison, UP_COUNTER);
	TIM_voidInit(TIMER3, TIM_NoClkDivison, UP_COUNTER);
	TIM_voidInit(TIMER4, TIM_NoClkDivison, UP_COUNTER);

	/* GPIO Initialization */
	GPIO_voidSetPinDir(GPIOC , PIN13 , OUT_PUSHPULL_2MHz);
	GPIO_voidSetPinDir(GPIOA , PIN0 , ALTRNATIVE_FUNC_PUSHPULL);
	//Timer2 Channel-1
	GPIO_voidSetPinDir(GPIOA , PIN15 , ALTRNATIVE_FUNC_PUSHPULL);	/*JTAG PIN*/
	//Timer2 Channel-2
	GPIO_voidSetPinDir(GPIOB , PIN3 , ALTRNATIVE_FUNC_PUSHPULL);	/*JTAG PIN*/
	//Timer2 Channel-3
	GPIO_voidSetPinDir(GPIOA , PIN2 , ALTRNATIVE_FUNC_PUSHPULL);
	//Timer2 Channel-4
	GPIO_voidSetPinDir(GPIOA , PIN3 , ALTRNATIVE_FUNC_PUSHPULL);

	MNVIC_voidEnableInterrupt(25);	//Enable NVIC for Timer1 Update Interrupt
	MNVIC_voidEnableInterrupt(28);	//Enable NVIC for GPTimer2
	MNVIC_voidEnableInterrupt(29);	//Enable NVIC for GPTimer3
	MNVIC_voidEnableInterrupt(30);	//Enable NVIC for GPTimer4

	TIM_voidSetPeriodicInterval(TIMER4 , 8000 , 1000 , BlinkLED);

	TIM_voidConfigurePWM(TIMER2, TIM_CHANNEL_1  , ActiveHigh , PWM_MODE_1);
	TIM_voidConfigurePWM(TIMER2, TIM_CHANNEL_2  , ActiveHigh , PWM_MODE_1);
	TIM_voidStartPWM(TIMER2 , 8 , 1000);

//	TIM_voidSetDutyCycle(TIMER2 ,TIM_CHANNEL_1 , 1000);

	while(1)
	{
		for(x = 0; x <=1000; x++)
		{
			TIM_voidSetDutyCycle(TIMER2 ,TIM_CHANNEL_1 ,x);
			TIM_voidSetDutyCycle(TIMER2 ,TIM_CHANNEL_2 ,x);
			TIM_voidDelay(TIMER3 , 8, 1000);
		}

		for(x = 1000; x >= 0; x--)
		{
			TIM_voidSetDutyCycle(TIMER2 ,TIM_CHANNEL_1 ,x);
			TIM_voidSetDutyCycle(TIMER2 ,TIM_CHANNEL_2 , x);
			TIM_voidDelay(TIMER3 , 8 , 1000);
		}
	}
}


