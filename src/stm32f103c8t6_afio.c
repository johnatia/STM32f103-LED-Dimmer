/**
 * @Author			:			John Atia  Nafady
 * @Date			:			20-5-2021
 * @Version			:			V03
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "stm32f103c8t6_afio.h"

void AFIO_voidConfigDebugPort(DebugPort_t SWD_JTAG)
{
	AFIO->MAPR &=~((1<<25) | (1<<26) | (1<<27) );
	AFIO->MAPR |= (SWD_JTAG<<25);
}


void AFIO_voidSetEXTIConfig(u8 Copy_u8Line , u8 Copy_u8PortMap)
{
	
	u8 local_u8Index = (Copy_u8Line/4);
	Copy_u8Line %= 4;
	AFIO->EXTICR[local_u8Index] &= ~(0b1111<<(Copy_u8Line*4));
	AFIO->EXTICR[local_u8Index] |= (Copy_u8PortMap<<(Copy_u8Line*4));
	
	/*
	AFIO->EXTICR[(Copy_u8Line/4)] &= ~(0b1111<<((Copy_u8Line%4)*4));
	AFIO->EXTICR[(Copy_u8Line/4)] &= ~(0b1111<<((Copy_u8Line%4)*4));
	*/
	
	
}

//void AFIO_voidTimerRemapPin(TIM_t Timer , TIM_REMAP_t TIM_REMAP)
//{
//	if(Timer == 1)
//	{
//		switch(TIM_REMAP)
//		{
//		case TIM2_REMAP1:
//			CLR_BIT(AFIO->MAPR , 9); SET_BIT(AFIO->MAPR , 8);
//			break;
//		case TIM2_REMAP2:
//			SET_BIT(AFIO->MAPR , 9); CLR_BIT(AFIO->MAPR , 8);
//			break;
//		case TIM2_REMAP3:
//			SET_BIT(AFIO->MAPR , 9); SET_BIT(AFIO->MAPR , 8);
//			break;
//
//		}
//	}
//}


