/**
  ******************************************************************************
  * @file    GPIO/GPIO_EXTI/Src/main.c 
  * @author  MCD Application Team
  * @version V1.2.7
  * @date    04-November-2016
  * @brief   This example describes how to configure and use GPIOs through 
  *          the STM32F4xx HAL API.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  * 18_0119 버그 수정.
  * 18_0125 보그 수정.(기록 부분에 일부 오류 수정, 기록에 화면 밝기 추가)
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "LCD.h"
#include "LED.h"
#include "Wifi.h"
#include "Keypad.h"
#include "Timer.h"
#include "USRAT.h"
#include "Flash.h"
#include <string.h>
#include "EventRecorder.h"
#include "spi_flash.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_EXTI
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static void SystemClock_Config(void);
static void EXTILine0_Config(void);



char mLCDPrintBuf[4][20];

uint16_t mTimerCnt = 0;

uint32_t m_DebugCn = 0;
uint32_t m_Main_TIM_Cnt = 0;

uint16_t mLCDInitCnt = 0;



char mLCDStatusMessage[4][20] = {"Status: Okay        ",
								 "Status: DRIV Updated",
								 "Status: OCC Updated ",
	                             "Status: CXN Error   "}; 	

								 
 Wifi_TRX_CNT mWifi_TRX_Flag;

uint8_t dTextCnt = 0;

uint8_t mUSART_TX_ReCnt = 0;
uint8_t mUSART_RX_ReCnt = 0;
								 

char RNA_SWVersion[100]={"--RNA-SW Version : 1.02  -- Build date : 04302018 \n\r"};

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;


/* Private define ------------------------------------------------------------*/

uint8_t Tx_Buffer[] = "STM32F10x SPI Firmware Library Example: communication with an M25P64 SPI FLASH";


#define  FLASH_WriteAddress     0x10000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress
#define  M25P64_FLASH_ID        0x202017
#define  BufferSize (countof(Tx_Buffer)-1)


/* Private macro -------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))
	
/* Private variables ---------------------------------------------------------*/

uint8_t Index, Rx_Buffer[BufferSize];
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = PASSED;
__IO uint32_t FLASH_ID = 0;

uint16_t nBufCmapCnt = 0;

/* Private functions ---------------------------------------------------------*/
//TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);




/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
int main(void)
{

    HAL_Init();

    /* Configure the system clock to 168 MHz */
    SystemClock_Config();

    /* Configure EXTI Line0 (connected to PA0 pin) in interrupt mode */
    EXTILine0_Config();
    Keypad_GPIO_Init();
    TextLCD_GPIO_Init();
//    LED_GPIO_Init();  
    Wifi_GPIO_Init();
    
   
    Timer_init();
    Wifi_init();
    
    USRAT_init();
	
    Flash_init();
	
	mWifi_TRX_Flag.nStatusTimeCnt = 60000;

	EventRecorderInitialize ( EventRecordAll , 1);
	EventRecorderEnable ( EventRecordAll , 0, 0xF); 

	
	//HAL_UART_Transmit_IT(&UartHandle1,(uint8_t *)&RNA_SWVersion[0],25);
	
/****************************SPI  *************************************************/	
//	 
//	SPI_FLASH_Init();   /* Initialize the SPI FLASH driver */
//	FLASH_ID = SPI_FLASH_ReadID();  /* Get SPI Flash ID */
//	SPI_FLASH_SectorErase(FLASH_SectorToErase);  	/* Erase SPI FLASH Sector to write on */
//	
////	SPI_Chip_Erase();
//	
//	SPI_FLASH_BufferWrite(Tx_Buffer,FLASH_WriteAddress,BufferSize);    /* Write Tx_Buffer data to SPI FLASH memory */
//	SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);   /* Read data from SPI FLASH memory */
//	nBufCmapCnt = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);   /* Check the corectness of written dada */

////  SPI_FLASH_SectorErase(FLASH_SectorToErase);
////  SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);

/*****************************************************************************/	
	
	if(mFlashFlag)
	{
		memcpy(nKeypad_InputDataRouteBuf,&mFlashMemoyBuf[1],3);
		memcpy(nKeypad_InputDataOperatorBuf,&mFlashMemoyBuf[4],5);
		memcpy(&nKeypad_InputDataBuf[0],&nKeypad_InputDataRouteBuf[0],3);
		
		nLED_Light_Step = mFlashMemoyBuf[9]; // 기록에서 화면 밝기를 불러 온다. 18_0125
		
		memcpy(mFlashMemoySaveBuf,mFlashMemoyBuf,10); // 읽어온 데이타를 저장 기존 값으로 설정한다. 18_0125
		
		// 18_0119 -> 버그 수정(wifi 수신 데이타는 갱신 하는 부분이 없음)
		InputDataRouteNum = ConvAsc2Hex(nKeypad_InputDataBuf[0]);
		InputDataRouteNum = (InputDataRouteNum << 8)|ConvAsc2Hex(nKeypad_InputDataBuf[1]);
		InputDataRouteNum = (InputDataRouteNum << 8)|ConvAsc2Hex(nKeypad_InputDataBuf[2]);
		
	}
	
    memset(mLCDPrintBuf,0x00,sizeof(mLCDPrintBuf[0][0]));
	
	memcpy(&mLCDPrintBuf[3][0],&mLCDStatusMessage[0][0],20);
	

	
    printf("SystemClock  = %d/ AHB(HCLK) : %d / APB1(PCLK1) : %d / APBP2(PCLK2) : %d \n\r", HAL_RCC_GetSysClockFreq(),HAL_RCC_GetHCLKFreq() ,HAL_RCC_GetPCLK1Freq(), HAL_RCC_GetPCLK2Freq());
	
	
    while (1)
    {
 		if(m_Main_TIM_Cnt == 1000) // LCD는 부팅시 500ms 이후에 동작 하도록 하기 위해 1초 후 초기화 하도록 수정.
		{
			m_Main_TIM_Cnt++;
			lcd_init();
			
			LED_init(); // LED 디스 플레이 함수.
		}
		
		// 버번 출력 화면.
		if(m_Main_TIM_Cnt == 20000) 
		{
			m_Main_TIM_Cnt++;
			MyPrintf_USART1(RNA_SWVersion);
			
		}
		
		if(m_Main_TIM_Cnt == 25000) 
		{
			m_Main_TIM_Cnt++;
			MyPrintf(&mFlashMemoyBuf[0],10,"Flash Read Address - %X : mFlashflag - %X :  ",FlashAddressPosion,mFlashFlag);
		}

		
        if(nTime_Flage_500us)
        {
            nTime_Flage_500us = 0;
            
            mTimerCnt++;
            
            if(!(mTimerCnt%5)) // 5ms
            {
            
                Keypad_ScanDo();
				
            }
            
            KeyPad_ScanInput();

        }


        USARTRX_MainPro();
		Flash_Main();
		
   
		if(nTime_Flage && (m_Main_TIM_Cnt >= 1000))
		{
			nTime_Flage = 0;
			
			HAL_GPIO_TogglePin(GPIOI,GPIO_PIN_11); // RUN LED

			m_DebugCn++;
			
			//sprintf(&mLCDPrintBuf[0][0],"[Display Mode]");
			
				if(!((nLcdPrintf_Cnt+10)%5000)) { } // LCD 스케일 함수(타아머 4번) 과 겹치는 부분 없도록 하기 위해 추가.
				else 
				{
					
					  
						sprintf(&mLCDPrintBuf[0][0],"Train    ID : %c%c%c", nKeypad_InputDataRouteBuf[0],nKeypad_InputDataRouteBuf[1],nKeypad_InputDataRouteBuf[2]);
						sprintf(&mLCDPrintBuf[1][0],"Employee ID : %c%c%c%c%c", 
															   nKeypad_InputDataOperatorBuf[0],nKeypad_InputDataOperatorBuf[1],nKeypad_InputDataOperatorBuf[2],nKeypad_InputDataOperatorBuf[3],nKeypad_InputDataOperatorBuf[4]);
						

						sprintf(&mLCDPrintBuf[2][0],"WIFI-SSID : %c%c%c%c%c%c%c",mSSID[0],mSSID[1],mSSID[2],mSSID[3],mSSID[4],mSSID[5],mSSID[6]);
						

							if((((mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt) <= (mWifi_TRX_Flag.nStatus.nWifi_RX_Cnt+2)) ||(mWifi_TRX_Flag.nStatus.nWifi_RX_Cnt_Re != mWifi_TRX_Flag.nStatus.nWifi_RX_Cnt))
							 &&(mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt_Re != mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt))
							{
								mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt_Re = mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt;
								mWifi_TRX_Flag.nStatus.nWifi_RX_Cnt_Re = mWifi_TRX_Flag.nStatus.nWifi_RX_Cnt;
								
								memcpy(&mLCDPrintBuf[3][0],&mLCDStatusMessage[0][0],20);
								
								lcd_putstr(0,3,&mLCDPrintBuf[3][0]);
								
								//printf("%d-Status OKey\n\r",m_DebugCn);
								
								
								if(mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt >= 3)
								{
									mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt = 0;
									mWifi_TRX_Flag.nStatus.nWifi_RX_Cnt = 0;
									
									mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt_Re = 0;
									mWifi_TRX_Flag.nStatus.nWifi_RX_Cnt_Re = 0;
								}
								
								
							}
							else if((((mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt) <= (mWifi_TRX_Flag.nDRIV.nWifi_RX_Cnt+2)) ||(mWifi_TRX_Flag.nDRIV.nWifi_RX_Cnt_Re != mWifi_TRX_Flag.nDRIV.nWifi_RX_Cnt)) 
									 &&(mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt_Re != mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt))
							{
								
								
								mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt_Re = mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt;
								mWifi_TRX_Flag.nDRIV.nWifi_RX_Cnt_Re = mWifi_TRX_Flag.nDRIV.nWifi_RX_Cnt;
								
								memcpy(&mLCDPrintBuf[3][0],&mLCDStatusMessage[1][0],20);
								
								lcd_putstr(0,3,&mLCDPrintBuf[3][0]);
								
								//printf("%d-DRIV OKey\n\r",m_DebugCn);
								
								
								if(mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt >= 3)
								{
									mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt = 0;
									mWifi_TRX_Flag.nDRIV.nWifi_RX_Cnt = 0;
									
									mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt_Re = 0;
									mWifi_TRX_Flag.nDRIV.nWifi_RX_Cnt_Re = 0;
								}
								
							}
							else if(((mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt) <= (mWifi_TRX_Flag.nOCC.nWifi_TX_Cnt+2)) 
									 &&(mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt_Re != mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt))
							{
								mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt_Re = mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt;
								
								memcpy(&mLCDPrintBuf[3][0],&mLCDStatusMessage[2][0],20);
								
								lcd_putstr(0,0,&mLCDPrintBuf[0][0]); //사령에서 TRAIN 변경시 LCD 화면에 한번더 찍어준다.
								
								lcd_putstr(0,3,&mLCDPrintBuf[3][0]);
								
								//printf("%d-OCC OKey\n\r",m_DebugCn);
								
								
								if(mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt >= 3)
								{
									mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt = 0;
									mWifi_TRX_Flag.nOCC.nWifi_TX_Cnt = 0;
									
									mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt_Re = 0;
									mWifi_TRX_Flag.nOCC.nWifi_TX_Cnt_Re = 0;
									
								}
								
								
							}	
							else if(mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt_Re != mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt
									||mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt_Re != mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt 
										||mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt_Re != mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt )
							{
								mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt_Re = mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt;
								mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt_Re = mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt;
								mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt_Re = mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt;
								
								
								
								memcpy(&mLCDPrintBuf[3][0],&mLCDStatusMessage[3][0],20);
								
								lcd_putstr(0,3,&mLCDPrintBuf[3][0]);
								
								//printf("%d-Status: CXN Error\n\r",m_DebugCn);
								
							}
										

							//instruction_out(0x01); // 디스플레이 지우기

							//instruction_out(0x06); // 엔트리 모두

							


								
							if(!nLineSelectFlg)
							{
								lcd_putstr(0,0,&mLCDPrintBuf[0][0]);
								
								
							}
							else
							{
								
								lcd_putstr(0,1,&mLCDPrintBuf[1][0]);
								
							}
							
							
										
							if(mXbeeSSIDFlagCnt >= 3 && mXbeeSSIDFlagCnt < 6 )
							{
								mXbeeSSIDFlagCnt++;
								lcd_putstr(0,2,&mLCDPrintBuf[2][0]);
								
								printf("%d-SSID Screen Print\n\r",m_DebugCn);
							}
							

							if(m_DebugCn < 10)
							{
								
								lcd_putstr(0,0,&mLCDPrintBuf[0][0]);
								lcd_putstr(0,1,&mLCDPrintBuf[1][0]);
								lcd_putstr(0,2,&mLCDPrintBuf[2][0]);
								lcd_putstr(0,3,&mLCDPrintBuf[3][0]);
							}


					}
				}
   }
 
}


/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
int fputc(int ch, FILE *f)
{
	return(ITM_SendChar(ch));
}



/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/


void MAIN_TIM(void)
{
	m_Main_TIM_Cnt++;
	
	if(!(m_Main_TIM_Cnt%500)){nTime_Flage = 1; }
	
	
	if(!(m_Main_TIM_Cnt%5000))
	{ 
//		HAL_GPIO_WritePin(GPIOI,GPIO_PIN_0,GPIO_PIN_RESET);
//		SPI_FLASH_ReadID(); 
//		HAL_GPIO_WritePin(GPIOI,GPIO_PIN_0,GPIO_PIN_RESET);
		
	}
	

	
	if(USART_1Ch.nRxTimeOut)
	{
		// 1번 채널이 아직 연결 중이면 기다린다.
	}
	else
	{
		if(mWifi_TRX_Flag.nDRIVTimeCnt){mWifi_TRX_Flag.nDRIVTimeCnt--; }
		if(mWifi_TRX_Flag.nStatusTimeCnt){mWifi_TRX_Flag.nStatusTimeCnt--; }
	}
	
	
}
/*****************************************************************************

  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 16 (내부RC)
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None

******************************************************************************/
static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* Enable HSE Oscillator and activate PLL with HSE as source */

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;  // 내부 PLL 설정
    RCC_OscInitStruct.HSEState = RCC_HSE_ON; // 내부 PLL 설정
	RCC_OscInitStruct.HSIState = RCC_HSI_OFF;


    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON; 
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25; // 내장형 16MB로 구성.(변경 불가)
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;

    HAL_RCC_OscConfig(&RCC_OscInitStruct);


    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | 
	                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
    
    //HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000); // 1ms 시스템 코어 타이머

    //HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);


    

}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
 static void EXTILine0_Config(void)
{

    GPIO_InitTypeDef   GPIO_InitStructure;

    __GPIOI_CLK_ENABLE();


    // RUN LED
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Pin = GPIO_PIN_11;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStructure); 

    /* Enable and set EXTI Line0 Interrupt to the lowest priority */
    //HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
    //HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}


/*****************************************************************************
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
******************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  if(GPIO_Pin == KEY_BUTTON_PIN)
  {
    /* Toggle LED3 */
  //  BSP_LED_Toggle(LED3);
    /* Toggle LED4 */
  //  BSP_LED_Toggle(LED4);    
    /* Toggle LED5 */
  //  BSP_LED_Toggle(LED5);   
    /* Toggle LED6 */
  //  BSP_LED_Toggle(LED6);
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}


#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
