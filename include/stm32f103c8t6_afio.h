/**
 * @Author			:			John Atia  Nafady
 * @Date			:			20-5-2021
 * @Version			:			V03
 */

#ifndef _AFIO_H_
#define _AFIO_H_

#define PA	0
#define PB	1
#define PC	2

typedef struct{

	volatile u32 EVCR;
	volatile u32 MAPR;
	volatile u32 EXTICR[4];
	volatile u32 MAPR2;


}AFIO_TypeDef;

typedef enum
{
	EnableSWD_EnableJTAG 				= 0b000 ,
	EnableSWD_EnableJTAG_WithoutNJTRST	= 0b001 ,
	EnableSWD_DisableJTAG   			= 0b010 ,
	DisableSWD_DisableJTAG 				= 0b100
}DebugPort_t;

#define AFIO 	((AFIO_TypeDef*)0x40010000)


void AFIO_voidSetEXTIConfig(u8 Copy_u8Line , u8 Copy_u8PortMap);
/*
 * Copy_u8PortMap could be: PA, PB or PC
 */

/*
 * Copy_u8Line = 0 : 15
 */
//void AFIO_voidTimerRemapChannel(TIM_t Timer , TIM_REMAP_t TIM_REMAP);


void AFIO_voidConfigDebugPort(DebugPort_t SWD_JTAG);



#endif
