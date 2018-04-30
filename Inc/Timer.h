#include "stm32f4xx_hal.h"


#define TIMx3_IRQHandler                TIM3_IRQHandler
#define TIMx4_IRQHandler                TIM4_IRQHandler


extern uint32_t nTime_Flage;
extern uint32_t nTime_Flage_500us;
extern uint32_t nTime_Flage_100us;
extern uint32_t nLedPrintf_Flag;
extern uint32_t nLcdPrintf_Cnt;


static void Timer_Error_Handler(void);
void TIMx3_IRQHandler(void);
void TIMx4_IRQHandler(void);
void Timer_init(void);


/*
	Written by ChrisP (http://blog.naver.com/lbiith/220767441371)
	Reference: http://stm32f4-discovery.net/
*/

/*	STM32F4 Timers

Timer			Type				Resolution	Prescaler			Channels	MAX INTERFACE CLOCK		MAX TIMER CLOCK*	APB
----------------------------------------------------------------------------------------------------------------------------
TIM1, TIM8		Advanced			16bit		16bit					4		SysClk/2				SysClk				2
TIM2, TIM5		General purpose		32bit		16bit					4		SysClk/4				SysClk, SysClk/2	1
TIM3, TIM4		General purpose		16bit		16bit					4		SysClk/4				SysClk, SysClk/2	1
TIM9			General purpose		16bit		16bit					2		SysClk/2				SysClk				2
TIM10, TIM11	General purpose		16bit		16bit					1		SysClk/2				SysClk				2
TIM12			General purpose		16bit		16bit					2		SysClk/4				SysClk, SysClk/2	1
TIM13, TIM14	General purpose		16bit		16bit					1		SysClk/4				SysClk, SysClk/2	1
TIM6, TIM7		Basic				16bit		16bit					0		SysClk/4				SysClk, SysClk/2	1

MAX TIMER CLOCK*은 어떤 STM32F4xx 칩을 쓰느냐에 따라 달라질 수 있음.
*/

/*	STM32F4 PWM Pin Mapping

Timer		Channels	CH1		CH2		CH3		CH4
-----------------------------------------------------------
TIM1			4		PA7(N)	PB0(N)	PB1(N)
						PA8		PA9		PA10	PA11
						PE8(N)	PE10(N)	PE12(N)
						PE9		PE11	PE13	PE14
						PB13(N)	PB14(N)	PB15(N)
-----------------------------------------------------------
TIM2			4		PA0		PA1		PA2		PA3
						PA5		PB3		PB10	PB11
						PA15
-----------------------------------------------------------
TIM3			4		PA6		PA7		PB0		PB1
						PB4		PB5
						PC6		PC7		PC8		PC9
-----------------------------------------------------------
TIM4			4		PB6		PB7		PB8		PB9
						PD12	PD13	PD14	PD15
-----------------------------------------------------------
TIM5			4		PA0		PA1		PA2		PA3
						PH10	PH11	PH12	PI0
-----------------------------------------------------------
TIM6			0
TIM7			0
-----------------------------------------------------------
TIM8			4		PA5(N)	PB0(N)	PB1(N)
						PA7(N)	PB14(N)	PB15(N)
						PC6		PC7		PC8		PC9
						PH13(N)	PH14(N)	PH15(N)
						PI5		PI6		PI7		PI2
-----------------------------------------------------------
TIM9			2		PA2		PA3
						PE5		PE6
-----------------------------------------------------------
TIM10			1		PB8
						PF6
-----------------------------------------------------------
TIM11			1		PB9
						PF7
-----------------------------------------------------------
TIM12			2		PB14	PB15
						PH6		PH9
-----------------------------------------------------------
TIM13			1		PF8
-----------------------------------------------------------
TIM14			1		PF9
-----------------------------------------------------------
*/