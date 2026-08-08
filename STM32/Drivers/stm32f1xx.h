/*
 * stm32f1xx.h
 *
 *  Created on: Jan 26, 2026
 *      Author: Abdullah Ahmed
 */

#include <stdint.h>

#ifndef STM32F1XX_H_
#define STM32F1XX_H_

#define ENABLE				 1
#define DISABLE				 0

#define APB1_BASE_ADDRESS    0x40000000U
#define APB2_BASE_ADDRESS    0x40010000U

#define TIM2_ADDRESS		 (APB1_BASE_ADDRESS + (0x0000))
#define TIM3_ADDRESS		 (APB1_BASE_ADDRESS + (0x0400))
#define TIM4_ADDRESS		 (APB1_BASE_ADDRESS + (0x0800))
#define TIM5_ADDRESS		 (APB1_BASE_ADDRESS + (0x0C00))

#define USART2_ADDRESS		 (APB1_BASE_ADDRESS + (0x4400))
#define USART3_ADDRESS		 (APB1_BASE_ADDRESS + (0x4800))
#define UART4_ADDRESS		 (APB1_BASE_ADDRESS + (0x4C00))
#define UART5_ADDRESS		 (APB1_BASE_ADDRESS + (0x5000))

#define I2C1_ADDRESS		 (APB1_BASE_ADDRESS + (0x5400))
#define I2C2_ADDRESS		 (APB1_BASE_ADDRESS + (0x5800))

#define AFIO_ADDRESS		 (APB2_BASE_ADDRESS + (0x0000))

#define EXTI_ADDRESS		 (APB2_BASE_ADDRESS + (0x0400))

#define GPIOA_ADDRESS		 (APB2_BASE_ADDRESS + (0x0800))
#define GPIOB_ADDRESS		 (APB2_BASE_ADDRESS + (0x0C00))
#define GPIOC_ADDRESS		 (APB2_BASE_ADDRESS + (0x1000))
#define GPIOD_ADDRESS		 (APB2_BASE_ADDRESS + (0x1400))
#define GPIOE_ADDRESS		 (APB2_BASE_ADDRESS + (0x1800))

#define ADC1_ADDRESS		 (APB2_BASE_ADDRESS + (0x2400))
#define ADC2_ADDRESS		 (APB2_BASE_ADDRESS + (0x2800))

#define USART1_ADDRESS		 (APB2_BASE_ADDRESS + (0x3800))

#define ADC3_ADDRESS		 (APB2_BASE_ADDRESS + (0x3C00))

#define RCC_BASE_ADDRESS	 0x40021000

#define NVIC_BASE_ADDRESS	 0xE000E100

//General Purpose Timers (2 --> 5) Structure Definition
typedef struct
{
	volatile uint32_t CR[2];
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR[2];
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t Reserved1;
	volatile uint32_t CCR[4];
	volatile uint32_t Reserved2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
}GP_TIM_RegDef_t;

#define TIM2				 (GP_TIM_RegDef_t*)TIM2_ADDRESS
#define TIM3				 (GP_TIM_RegDef_t*)TIM3_ADDRESS
#define TIM4				 (GP_TIM_RegDef_t*)TIM4_ADDRESS
#define TIM5				 (GP_TIM_RegDef_t*)TIM5_ADDRESS

//USART Structure Definition
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR[3];
	volatile uint32_t GTPR;
}USART_RegDef_t;

#define USART1				 (USART_RegDef_t*)USART1_ADDRESS
#define USART2				 (USART_RegDef_t*)USART2_ADDRESS
#define USART3				 (USART_RegDef_t*)USART3_ADDRESS
#define UART4				 (USART_RegDef_t*)UART4_ADDRESS
#define UART5				 (USART_RegDef_t*)UART5_ADDRESS

//I2C Register Structure Definition
typedef struct
{
	volatile uint32_t CR[2];
	volatile uint32_t OAR[2];
	volatile uint32_t DR;
	volatile uint32_t SR[2];
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
}I2C_RegDef_t;

#define I2C1				 (I2C_RegDef_t*)I2C1_ADDRESS
#define I2C2				 (I2C_RegDef_t*)I2C2_ADDRESS

//AFIO Register Structure Definition
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t MAPR2;
}AFIO_RegDef_t;

#define AFIO			 	 (AFIO_RegDef_t*)AFIO_ADDRESS

//EXTI Register Structure Definition
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegDef_t;

#define EXTI		 		 (EXTI_RegDef_t*)EXTI_ADDRESS

//GPIO Register Structure Definition
typedef struct
{
	volatile uint32_t CR[2];
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_RegDef_t;

#define GPIOA 				 (GPIO_RegDef_t*)GPIOA_ADDRESS
#define GPIOB 				 (GPIO_RegDef_t*)GPIOB_ADDRESS
#define GPIOC 				 (GPIO_RegDef_t*)GPIOC_ADDRESS
#define GPIOD 				 (GPIO_RegDef_t*)GPIOD_ADDRESS
#define GPIOE 				 (GPIO_RegDef_t*)GPIOE_ADDRESS

//ADC Register Structure Definition
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t CR[2];
	volatile uint32_t SMPR[2];
	volatile uint32_t JOFR[4];
	volatile uint32_t HTR;
	volatile uint32_t LTR;
	volatile uint32_t SQR[3];
	volatile uint32_t JSQR;
	volatile uint32_t JDR[4];
	volatile uint32_t DR;
}ADC_RegDef_t;

#define ADC1				 (ADC_RegDef_t*)ADC1_ADDRESS
#define ADC2				 (ADC_RegDef_t*)ADC2_ADDRESS
#define ADC3				 (ADC_RegDef_t*)ADC3_ADDRESS

//RCC Register Structure Definition
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_RegDef_t;

#define RCC					 (RCC_RegDef_t*)RCC_BASE_ADDRESS

//NVIC Register Structure Definition
typedef struct
{
	volatile uint32_t   ISER[8];     /* Address offset: 0x000 - 0x01C */
	volatile uint32_t  RES0[24];     /* Address offset: 0x020 - 0x07C */
	volatile uint32_t   ICER[8];     /* Address offset: 0x080 - 0x09C */
	volatile uint32_t  RES1[24];     /* Address offset: 0x0A0 - 0x0FC */
	volatile uint32_t   ISPR[8];     /* Address offset: 0x100 - 0x11C */
	volatile uint32_t  RES2[24];     /* Address offset: 0x120 - 0x17C */
	volatile uint32_t   ICPR[8];     /* Address offset: 0x180 - 0x19C */
	volatile uint32_t  RES3[24];     /* Address offset: 0x1A0 - 0x1FC */
	volatile uint32_t   IABR[8];     /* Address offset: 0x200 - 0x21C */
	volatile uint32_t  RES4[56];     /* Address offset: 0x220 - 0x2FC */
	volatile uint8_t   IPR[240];     /* Address offset: 0x300 - 0x3EC */
	volatile uint32_t RES5[644];     /* Address offset: 0x3F0 - 0xEFC */
	volatile uint32_t STIR;    /* Address offset:         0xF00 */
}NVIC_RegDef_t;

#define NVIC				 (NVIC_RegDef_t*)NVIC_BASE_ADDRESS

//Interrupt Number Definition
typedef enum IRQn
{
	NonMaskableInt_IRQn         = -14,    /* 2 Non Maskable Interrupt                             */
	MemoryManagement_IRQn       = -12,    /* 4 Cortex-M3 Memory Management Interrupt              */
	BusFault_IRQn               = -11,    /* 5 Cortex-M3 Bus Fault Interrupt                      */
	UsageFault_IRQn             = -10,    /* 6 Cortex-M3 Usage Fault Interrupt                    */
	SVCall_IRQn                 = -5,     /* 11 Cortex-M3 SV Call Interrupt                       */
	DebugMonitor_IRQn           = -4,     /* 12 Cortex-M3 Debug Monitor Interrupt                 */
	PendSV_IRQn                 = -2,     /* 14 Cortex-M3 Pend SV Interrupt                       */
	SysTick_IRQn                = -1,     /* 15 Cortex-M3 System Tick Interrupt                   */
	WWDG_IRQn                   = 0,      /* Window WatchDog Interrupt                            */
	PVD_IRQn                    = 1,      /* PVD through EXTI Line detection Interrupt            */
	TAMPER_IRQn                 = 2,      /* Tamper Interrupt                                     */
	RTC_IRQn                    = 3,      /* RTC global Interrupt                                 */
	FLASH_IRQn                  = 4,      /* FLASH global Interrupt                               */
	RCC_IRQn                    = 5,      /* RCC global Interrupt                                 */
	EXTI0_IRQn                  = 6,      /* EXTI Line0 Interrupt                                 */
	EXTI1_IRQn                  = 7,      /* EXTI Line1 Interrupt                                 */
	EXTI2_IRQn                  = 8,      /* EXTI Line2 Interrupt                                 */
	EXTI3_IRQn                  = 9,      /* EXTI Line3 Interrupt                                 */
	EXTI4_IRQn                  = 10,     /* EXTI Line4 Interrupt                                 */
	DMA1_Channel1_IRQn          = 11,     /* DMA1 Channel 1 global Interrupt                      */
	DMA1_Channel2_IRQn          = 12,     /* DMA1 Channel 2 global Interrupt                      */
	DMA1_Channel3_IRQn          = 13,     /* DMA1 Channel 3 global Interrupt                      */
	DMA1_Channel4_IRQn          = 14,     /* DMA1 Channel 4 global Interrupt                      */
	DMA1_Channel5_IRQn          = 15,     /* DMA1 Channel 5 global Interrupt                      */
	DMA1_Channel6_IRQn          = 16,     /* DMA1 Channel 6 global Interrupt                      */
	DMA1_Channel7_IRQn          = 17,     /* DMA1 Channel 7 global Interrupt                      */
	ADC1_2_IRQn                 = 18,     /* ADC1 and ADC2 global Interrupt                       */
	CAN1_TX_IRQn                = 19,     /* USB Device High Priority or CAN1 TX Interrupts       */
	CAN1_RX0_IRQn               = 20,     /* USB Device Low Priority or CAN1 RX0 Interrupts       */
	CAN1_RX1_IRQn               = 21,     /* CAN1 RX1 Interrupt                                   */
	CAN1_SCE_IRQn               = 22,     /* CAN1 SCE Interrupt                                   */
	EXTI9_5_IRQn                = 23,     /* External Line[9:5] Interrupts                        */
	TIM1_BRK_IRQn               = 24,     /* TIM1 Break Interrupt                                 */
	TIM1_UP_IRQn                = 25,     /* TIM1 Update Interrupt                                */
	TIM1_TRG_COM_IRQn           = 26,     /* TIM1 Trigger and Commutation Interrupt               */
	TIM1_CC_IRQn                = 27,     /* TIM1 Capture Compare Interrupt                       */
	TIM2_IRQn                   = 28,     /* TIM2 global Interrupt                                */
	TIM3_IRQn                   = 29,     /* TIM3 global Interrupt                                */
	TIM4_IRQn                   = 30,     /* TIM4 global Interrupt                                */
	I2C1_EV_IRQn                = 31,     /* I2C1 Event Interrupt                                 */
	I2C1_ER_IRQn                = 32,     /* I2C1 Error Interrupt                                 */
	I2C2_EV_IRQn                = 33,     /* I2C2 Event Interrupt                                 */
	I2C2_ER_IRQn                = 34,     /* I2C2 Error Interrupt                                 */
	SPI1_IRQn                   = 35,     /* SPI1 global Interrupt                                */
	SPI2_IRQn                   = 36,     /* SPI2 global Interrupt                                */
	USART1_IRQn                 = 37,     /* USART1 global Interrupt                              */
	USART2_IRQn                 = 38,     /* USART2 global Interrupt                              */
	USART3_IRQn                 = 39,     /* USART3 global Interrupt                              */
	EXTI15_10_IRQn              = 40,     /* External Line[15:10] Interrupts                      */
	RTCAlarm_IRQn               = 41,     /* RTC Alarm through EXTI Line Interrupt                */
	OTG_FS_WKUP_IRQn            = 42,     /* USB OTG FS WakeUp from suspend through EXTI Line Int */
	TIM5_IRQn                   = 50,     /* TIM5 global Interrupt                                */
	SPI3_IRQn                   = 51,     /* SPI3 global Interrupt                                */
	UART4_IRQn                  = 52,     /* UART4 global Interrupt                               */
	UART5_IRQn                  = 53,     /* UART5 global Interrupt                               */
	TIM6_IRQn                   = 54,     /* TIM6 global Interrupt                                */
	TIM7_IRQn                   = 55,     /* TIM7 global Interrupt                                */
	DMA2_Channel1_IRQn          = 56,     /* DMA2 Channel 1 global Interrupt                      */
	DMA2_Channel2_IRQn          = 57,     /* DMA2 Channel 2 global Interrupt                      */
	DMA2_Channel3_IRQn          = 58,     /* DMA2 Channel 3 global Interrupt                      */
	DMA2_Channel4_IRQn          = 59,     /* DMA2 Channel 4 global Interrupt                      */
	DMA2_Channel5_IRQn          = 60,     /* DMA2 Channel 5 global Interrupt                      */
	ETH_IRQn                    = 61,     /* Ethernet global Interrupt                            */
	ETH_WKUP_IRQn               = 62,     /* Ethernet Wakeup through EXTI line Interrupt          */
	CAN2_TX_IRQn                = 63,     /* CAN2 TX Interrupt                                    */
	CAN2_RX0_IRQn               = 64,     /* CAN2 RX0 Interrupt                                   */
	CAN2_RX1_IRQn               = 65,     /* CAN2 RX1 Interrupt                                   */
	CAN2_SCE_IRQn               = 66,     /* CAN2 SCE Interrupt                                   */
	OTG_FS_IRQn                 = 67      /* USB OTG FS global Interrupt                          */
} IRQn_type;


//Enable and Disable general purpose timers clocks
#define TIM2_Clk_En()		 ((RCC)->APB1ENR |= (1 << 0))
#define TIM3_Clk_En()		 ((RCC)->APB1ENR |= (1 << 1))
#define TIM4_Clk_En()		 ((RCC)->APB1ENR |= (1 << 2))
#define TIM5_Clk_En()		 ((RCC)->APB1ENR |= (1 << 3))

#define TIM2_Clk_Di()		 ((RCC)->APB1ENR &= ~(1 << 0))
#define TIM3_Clk_Di()		 ((RCC)->APB1ENR &= ~(1 << 1))
#define TIM4_Clk_Di()		 ((RCC)->APB1ENR &= ~(1 << 2))
#define TIM5_Clk_Di()		 ((RCC)->APB1ENR &= ~(1 << 3))

//Enable and Disable USART clocks
#define USART1_Clk_En()		 ((RCC)->APB2ENR |= (1 << 14))
#define USART2_Clk_En()		 ((RCC)->APB1ENR |= (1 << 17))
#define USART3_Clk_En()		 ((RCC)->APB1ENR |= (1 << 18))
#define UART4_Clk_En()		 ((RCC)->APB1ENR |= (1 << 19))
#define UART5_Clk_En()		 ((RCC)->APB1ENR |= (1 << 20))

#define USART1_Clk_Di()		 ((RCC)->APB2ENR &= ~(1 << 14))
#define USART2_Clk_Di()		 ((RCC)->APB1ENR &= ~(1 << 17))
#define USART3_Clk_Di()		 ((RCC)->APB1ENR &= ~(1 << 18))
#define UART4_Clk_Di()		 ((RCC)->APB1ENR &= ~(1 << 19))
#define UART5_Clk_Di()		 ((RCC)->APB1ENR &= ~(1 << 20))

//Enable and Disable I2C clocks
#define I2C1_Clk_En()		 ((RCC)->APB1ENR |= (1 << 21))
#define I2C2_Clk_En()		 ((RCC)->APB1ENR |= (1 << 22))

#define I2C1_Clk_Di()		 ((RCC)->APB1ENR &= ~(1 << 21))
#define I2C2_Clk_Di()		 ((RCC)->APB1ENR &= ~(1 << 22))

//Enable and Disable GPIO clocks
#define GPIOA_Clk_En()		 ((RCC)->APB2ENR |= (1 << 2))
#define GPIOB_Clk_En()		 ((RCC)->APB2ENR |= (1 << 3))
#define GPIOC_Clk_En()		 ((RCC)->APB2ENR |= (1 << 4))
#define GPIOD_Clk_En()		 ((RCC)->APB2ENR |= (1 << 5))
#define GPIOE_Clk_En()		 ((RCC)->APB2ENR |= (1 << 6))

#define GPIOA_Clk_Di()		 ((RCC)->APB2ENR &= ~(1 << 2))
#define GPIOB_Clk_Di()		 ((RCC)->APB2ENR &= ~(1 << 3))
#define GPIOC_Clk_Di()		 ((RCC)->APB2ENR &= ~(1 << 4))
#define GPIOD_Clk_Di()		 ((RCC)->APB2ENR &= ~(1 << 5))
#define GPIOE_Clk_Di()		 ((RCC)->APB2ENR &= ~(1 << 6))

//Enable and Disable ADC clocks
#define ADC1_Clk_En()		 ((RCC)->APB2ENR |= (1 << 9))
#define ADC2_Clk_En()		 ((RCC)->APB2ENR |= (1 << 10))

#define ADC1_Clk_Di()		 ((RCC)->APB2ENR &= ~(1 << 9))
#define ADC2_Clk_Di()		 ((RCC)->APB2ENR &= ~(1 << 10))

//Enable and Disable AFIO clock
#define AFIO_Clk_En()		 ((RCC)->APB2ENR |= (1 << 0))
#define AFIO_Clk_Di()		 ((RCC)->APB2ENR &= ~(1 << 0))

//General Purpose Timers Interrupt Modes
#define GP_TIM_UPDATE				0
#define GP_TIM_CAPTURE_COMPARE1		1
#define GP_TIM_CAPTURE_COMPARE2		2
#define GP_TIM_CAPTURE_COMPARE3		3
#define GP_TIM_CAPTURE_COMPARE4		4

//GPIO Pin Modes
#define INPUT_ANALOG		 0
#define OUTPUT_GP_PP_10MHz	 1
#define OUTPUT_GP_PP_2MHz	 2
#define OUTPUT_GP_PP_50MHz	 3
#define INPUT_FLOATING	 	 4
#define OUTPUT_GP_OD_10MHz	 5
#define OUTPUT_GP_OD_2MHz	 6
#define OUTPUT_GP_OD_50MHz	 7
#define INPUT_PUPD	 	     8
#define OUTPUT_AF_PP_10MHz	 9
#define OUTPUT_AF_PP_2MHz	 10
#define OUTPUT_AF_PP_50MHz	 11
#define OUTPUT_AF_OD_10MHz	 13
#define OUTPUT_AF_OD_2MHz	 14
#define OUTPUT_AF_OD_50MHz	 15

#endif /* STM32F1XX_H_ */
