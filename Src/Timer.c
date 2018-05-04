#include "Timer.h"
#include "main.h"
#include "LED.h"
#include "USRAT.h"
#include "Flash.h"
#include "LCD.h"
#include "keypad.h"




/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
 TIM_HandleTypeDef TimHandle3,TimHandle4,TimHandle5,TimHandle8;
	
 TIM_OC_InitTypeDef Tim3Pwm,Tim8Pwm;
	
	
    uint32_t nTime_Flage = 0;
    uint32_t nTime_Flage_500us = 0;
	uint32_t nTime_Flage_100us = 0;
	uint32_t nLedPrintf_Flag = 0;
	
	uint32_t nLcdPrintf_Cnt = 0;
	

/*****************************************************************************
   Initialize TIM3 peripheral as follow:
       + Period = 10000 - 1
       + Prescaler = ((SystemCoreClock/2)/10000) - 1          
       + ClockDivision = 0
       + Counter direction = Up
       + TIM1 , 9 , 10, 11 번은 최대 168MHZ
       + TIM 2,3,4,5 12,13,14, 6,7 최대 84MHZ 
       + 따라서 클럭 속도 계산 식도 다르다.
       + 타이머 속도는 = 1/(SystemCoreClock / Period / Prescaler );
       
   Time               Period        Prescaler
   1000(500)ms       10000-1       ((SystemCoreClock /2)/10000) - 1    
   100(50)  ms       10000-1       ((SystemCoreClock /2)/100000) - 1
   10(5)    ms       10000-1       ((SystemCoreClock /2)/1000000) - 1(84)
   1000(500)us       10000-1       ((SystemCoreClock /2)/10000000) - 1(7)
   100(50)  us       1000 -1       ((SystemCoreClock /2)/10000000) - 1 (7)
   10(5)    us       100-1         ((SystemCoreClock /2)/10000000) - 1 (7)
 //1000ns  10-1          ((SystemCoreClock /2)/10000000) - 1 (7)
******************************************************************************/
    uint32_t uwPrescalerValue_Time3 = 0;
    uint32_t uwPrescalerValue_Time4 = 0;
	uint32_t uwPrescalerValue_Time5 = 0;
	uint32_t uwPrescalerValue_Time8 = 0;

void Timer_init(void)
{

	
  /*##-1- Configure the TIM peripheral #######################################*/
  /* -----------------------------------------------------------------------
  TIM4 Configuration: generate 4 PWM signals with 4 different duty cycles.

    In this example TIM4 input clock (TIM4CLK) is set to APB1 clock x 2,
    since APB1 prescaler is equal to 2.
      TIM4CLK = APB1CLK*2
      APB1CLK = HCLK/2
      => TIM4CLK = HCLK = SystemCoreClock

    To get TIM4 counter clock at 16 MHz, the prescaler is computed as follows:
       Prescaler = (TIM4CLK / TIM4 counter clock) - 1
       Prescaler = ((SystemCoreClock) /16 MHz) - 1

    To get TIM4 output clock at 24 KHz, the period (ARR)) is computed as follows:
       ARR = (TIM4 counter clock / TIM4 output clock) - 1
           = 665

    TIM4 Channel1 duty cycle = (TIM4_CCR1/ TIM4_ARR + 1)* 100 = 50%
    TIM4 Channel2 duty cycle = (TIM4_CCR2/ TIM4_ARR + 1)* 100 = 37.5%
    TIM4 Channel3 duty cycle = (TIM4_CCR3/ TIM4_ARR + 1)* 100 = 25%
    TIM4 Channel4 duty cycle = (TIM4_CCR4/ TIM4_ARR + 1)* 100 = 12.5%

    Note:
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
     Each time the core clock (HCLK) changes, user had to update SystemCoreClock
     variable value. Otherwise, any configuration based on this variable will be incorrect.
     This variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
  ----------------------------------------------------------------------- */

  /* Initialize TIMx peripheral as follows:
       + Prescaler = (SystemCoreClock / 16000000) - 1
       + Period = (666 - 1)
       + ClockDivision = 0
       + Counter direction = Up
  */


//    //TIM3는 최대 84MHZ 이므로 속도 값이 크다.(500ms)
//    /* Compute the prescaler value to have TIM3 counter clock equal to 10 KHz */
//    uwPrescalerValue_Time3 = (uint32_t) ((SystemCoreClock /2)/10000000) - 1;


//    /* Set TIMx instance */
//    TimHandle3.Instance = TIM3;

//    TimHandle3.Init.Period = 1000-1; //주기.
//    TimHandle3.Init.Prescaler = uwPrescalerValue_Time3; //분주
//    TimHandle3.Init.ClockDivision = 0;
//    TimHandle3.Init.CounterMode = TIM_COUNTERMODE_UP;
//	TimHandle3.Init.RepetitionCounter = 0;
//	
//	HAL_TIM_PWM_Init(&TimHandle3);
//	
////    HAL_TIM_Base_Init(&TimHandle3);
////    HAL_TIM_Base_Start_IT(&TimHandle3);

///*##-2- Configure the PWM channels #########################################*/
//  /* Common configuration for all channels */
//  Tim3Pwm.OCMode       = TIM_OCMODE_PWM1;
//  Tim3Pwm.OCPolarity   = TIM_OCPOLARITY_HIGH;
//  Tim3Pwm.OCFastMode   = TIM_OCFAST_DISABLE;
//  Tim3Pwm.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
//  Tim3Pwm.OCNIdleState = TIM_OCNIDLESTATE_RESET;

//  Tim3Pwm.OCIdleState  = TIM_OCIDLESTATE_RESET;

//  /* Set the pulse value for channel 1 */
//  Tim3Pwm.Pulse = 0; // Green
//  if (HAL_TIM_PWM_ConfigChannel(&TimHandle3, &Tim3Pwm, TIM_CHANNEL_1) != HAL_OK)
//  {
//    /* Configuration Error */
//    Timer_Error_Handler();
//  }

//  /* Set the pulse value for channel 2 */
//  Tim3Pwm.Pulse = 20; //Blue
//  if (HAL_TIM_PWM_ConfigChannel(&TimHandle3, &Tim3Pwm, TIM_CHANNEL_2) != HAL_OK)
//  {
//    /* Configuration Error */
//    Timer_Error_Handler();
//  }

//  /* Set the pulse value for channel 3 */
//  Tim3Pwm.Pulse = 50; //RED
//  if (HAL_TIM_PWM_ConfigChannel(&TimHandle3, &Tim3Pwm, TIM_CHANNEL_3) != HAL_OK)
//  {
//    /* Configuration Error */
//    Timer_Error_Handler();
//  }


//  /*##-3- Start PWM signals generation #######################################*/
//  /* Start channel 1 */
//  if (HAL_TIM_PWM_Start(&TimHandle3, TIM_CHANNEL_1) != HAL_OK)
//  {
//    /* PWM Generation Error */
//    Timer_Error_Handler();
//  }
//  /* Start channel 2 */
//  if (HAL_TIM_PWM_Start(&TimHandle3, TIM_CHANNEL_2) != HAL_OK)
//  {
//    /* PWM Generation Error */
//    Timer_Error_Handler();
//  }
//  /* Start channel 3 */
//  if (HAL_TIM_PWM_Start(&TimHandle3, TIM_CHANNEL_3) != HAL_OK)
//  {
//    /* PWM generation Error */
//    Timer_Error_Handler();
//  }



    
/************************************TIM4***********************************************************/    
    //TIM4은 최대 84MHz 이므로 속도 값이 더 작다.(1ms)
    /* Compute the prescaler value to have TIM3 counter clock equal to 10 KHz */
    uwPrescalerValue_Time4 = (uint32_t) ((SystemCoreClock/2)/10000000) - 1;

    /* Set TIMx instance */
    TimHandle4.Instance = TIM4;

    TimHandle4.Init.Period = 10000-1;
    TimHandle4.Init.Prescaler = uwPrescalerValue_Time4;
    TimHandle4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TimHandle4.Init.CounterMode = TIM_COUNTERMODE_UP;

    HAL_TIM_Base_Init(&TimHandle4);
    HAL_TIM_Base_Start_IT(&TimHandle4);
	
	
/*****************************TIM5******************************************************************/    	
	 //TIM5는 최대 84MHZ 이므로 속도 값이 크다.(500ms)
    /* Compute the prescaler value to have TIM3 counter clock equal to 10 KHz */
    uwPrescalerValue_Time5 = (uint32_t) ((SystemCoreClock /2)/10000000) - 1;

    /* Set TIMx instance */
    TimHandle5.Instance = TIM5;

    TimHandle5.Init.Period = 10000-1; //주기.
    TimHandle5.Init.Prescaler = uwPrescalerValue_Time5;
    TimHandle5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TimHandle5.Init.CounterMode = TIM_COUNTERMODE_UP;

    HAL_TIM_Base_Init(&TimHandle5);
    HAL_TIM_Base_Start_IT(&TimHandle5);
	
	
	
/**********************TIM8*************************************************************************/   	
	
// //TIM8는 최대 84MHZ 이므로 속도 값이 크다.(500ms)
//    /* Compute the prescaler value to have TIM3 counter clock equal to 10 KHz */
//    uwPrescalerValue_Time8 = (uint32_t) ((SystemCoreClock)/10000000) - 1;

//    /* Set TIMx instance */
//    TimHandle8.Instance = TIM8;

//    TimHandle8.Init.Period = 1000-1; //주기.
//    TimHandle8.Init.Prescaler = uwPrescalerValue_Time8; //분주
//    TimHandle8.Init.ClockDivision = 0;
//    TimHandle8.Init.CounterMode = TIM_COUNTERMODE_UP;
//	TimHandle8.Init.RepetitionCounter = 0;
//	
//	HAL_TIM_PWM_Init(&TimHandle8);
//	
////    HAL_TIM_Base_Init(&TimHandle3);
////    HAL_TIM_Base_Start_IT(&TimHandle3);

///*##-2- Configure the PWM channels #########################################*/
//  /* Common configuration for all channels */
//  Tim8Pwm.OCMode       = TIM_OCMODE_PWM1;
//  Tim8Pwm.OCPolarity   = TIM_OCPOLARITY_HIGH;
//  Tim8Pwm.OCFastMode   = TIM_OCFAST_DISABLE;
//  Tim8Pwm.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
//  Tim8Pwm.OCNIdleState = TIM_OCNIDLESTATE_RESET;

//  Tim8Pwm.OCIdleState  = TIM_OCIDLESTATE_RESET;

//  /* Set the pulse value for channel 1 */
//  Tim8Pwm.Pulse = 70;
//  if (HAL_TIM_PWM_ConfigChannel(&TimHandle8, &Tim8Pwm, TIM_CHANNEL_1) != HAL_OK)
//  {
//    /* Configuration Error */
//    Timer_Error_Handler();
//  }

//  /* Set the pulse value for channel 2 */
//  Tim8Pwm.Pulse = 50;
//  if (HAL_TIM_PWM_ConfigChannel(&TimHandle8, &Tim8Pwm, TIM_CHANNEL_2) != HAL_OK)
//  {
//    /* Configuration Error */
//    Timer_Error_Handler();
//  }

//  /* Set the pulse value for channel 3 */
//  Tim8Pwm.Pulse = 0;
//  if (HAL_TIM_PWM_ConfigChannel(&TimHandle8, &Tim8Pwm, TIM_CHANNEL_3) != HAL_OK)
//  {
//    /* Configuration Error */
//    Timer_Error_Handler();
//  }


//  /*##-3- Start PWM signals generation #######################################*/
//  /* Start channel 1 */
//  if (HAL_TIM_PWM_Start(&TimHandle8, TIM_CHANNEL_1) != HAL_OK)
//  {
//    /* PWM Generation Error */
//    Timer_Error_Handler();
//  }
//  /* Start channel 2 */
//  if (HAL_TIM_PWM_Start(&TimHandle8, TIM_CHANNEL_2) != HAL_OK)
//  {
//    /* PWM Generation Error */
//    Timer_Error_Handler();
//  }
//  /* Start channel 3 */
//  if (HAL_TIM_PWM_Start(&TimHandle8, TIM_CHANNEL_3) != HAL_OK)
//  {
//    /* PWM generation Error */
//    Timer_Error_Handler();
//  }
//  


}


/*****************************************************************************
* @brief - 100 micro  타이머 
* @param -
* @retval-
******************************************************************************/

void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle3);
  

}


/*****************************************************************************
* @brief - 1ms 타이머 
* @param -
* @retval-
******************************************************************************/
void TIM4_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle4);

}


/*****************************************************************************
* @brief - 100 micro 타이머 
* @param -
* @retval-
******************************************************************************/
void TIM5_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle5);

}


/*****************************************************************************
* @brief - 타이머 인터럽트 함수
* @param -
* @retval-
******************************************************************************/
int dTimerCnt4 = 0;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    if (htim->Instance == TIM3) // 100us
    {
		
		
		
    }  	
	else if(htim->Instance == TIM4) //1ms
    {
        nTime_Flage_500us = 1;

        USART_TIM();
		Flash_TIM();
		MAIN_TIM();
		
		nLcdPrintf_Cnt++;
		
		// LCD 스케일 부분.
		if(!((nLcdPrintf_Cnt+10)%10000)) // 1- 처음에는 디스플레이 지우는 것을 한다.
		{
			//instruction_out(0x01); // 디스플레이 지우기
			//instruction_out(0x06); // 엔트리 모두
		}
		else if(!((nLcdPrintf_Cnt+5)%10000)) //5ms 후에 2-번째 스탭 "Return home" 을 한다.
		{
			//instruction_out(0x06); // 엔트리 모두
		}
		else if(!(nLcdPrintf_Cnt%10000)) // 추가로 5ms 후에 전체 화면 출력을 한다.
		{
			//instruction_out(0x01); // 디스플레이 지우기
			
			//instruction_out(0x02); //Retun home
		}
		else if(!(nLcdPrintf_Cnt%500))
		{

			
//			if(!nLineSelectFlg)
//			{
//				
//				lcd_putstr(0,0,&mLCDPrintBuf[0][0]);
//				lcd_putstr(0,1,&mLCDPrintBuf[1][0]);
//				lcd_putstr(0,2,&mLCDPrintBuf[2][0]);
//				lcd_putstr(0,3,&mLCDPrintBuf[3][0]);
//				
//				lcd_putstr(0,0,&mLCDPrintBuf[0][0]);
//			}
//			else 
//			{
//				lcd_putstr(0,0,&mLCDPrintBuf[0][0]);
//				lcd_putstr(0,1,&mLCDPrintBuf[1][0]);
//				lcd_putstr(0,2,&mLCDPrintBuf[2][0]);
//				lcd_putstr(0,3,&mLCDPrintBuf[3][0]);
//				
//				
//				lcd_putstr(0,1,&mLCDPrintBuf[1][0]);
//			}
			
			
		}
		

    }
	else if(htim->Instance == TIM5) //100 us
	{
		
		nTime_Flage_100us++;
		
		//if(!(nTime_Flage_100us%3))
		//{
			nLedPrintf_Flag = 1;
		//	LED_init(); // LED 디스 플레이 함수.
		//}
		
		
	}
	
    
}

/*****************************************************************************
* @brief - 타이머 인터럽트 함수
* @param -
* @retval-
******************************************************************************/

static void Timer_Error_Handler(void)
{
  /* Turn LED5 on */
  while(1)
  {
  }
}





