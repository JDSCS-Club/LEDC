#include "USRAT.h"
#include <string.h>
#include <stdarg.h>
#include "Keypad.h"
#include "Flash.h"
#include "main.h"
#include <string.h>


UART_HandleTypeDef UartHandle1; 

UART_HandleTypeDef UartHandle4;

UART_HandleTypeDef UartHandle3;

__IO ITStatus UartReady = RESET;


USART_INIT_SHAPE USART_1Ch;
USART_INIT_SHAPE USART_3Ch;
USART_INIT_SHAPE USART_4Ch;

uint16_t crc16tab[256]= {
	0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};



uint8_t mUSARTRXFlag_1Ch = 0;
uint8_t mUSARTRXFlag_3Ch = 0;
uint8_t mUSARTRXFlag_4Ch = 0;

uint8_t mUSART_RXBuf_1ch[USART_BUF_MIN];
uint8_t mUSART_GetRXBuf_1ch[USART_BUF_Get];
uint8_t mUSART_TXBuf_1ch[USART_BUF_MIN];
uint8_t mUSART_RXBufBackUp_1ch[USART_BUF_MIN];

uint8_t mUSART_RXBuf_2ch[USART_BUF_MIN];
uint8_t mUSART_GetRXBuf_2ch[USART_BUF_Get];
uint8_t mUSART_TXBuf_2ch[USART_BUF_MIN];
uint8_t mUSART_RXBufBackUp_2ch[USART_BUF_MIN];

uint8_t mUSART_RXBuf_3ch[USART_BUF_MIN];
uint8_t mUSART_GetRXBuf_3ch[USART_BUF_Get];
uint8_t mUSART_TXBuf_3ch[USART_BUF_MIN];
uint8_t mUSART_RXBufBackUp_3ch[USART_BUF_MIN];

uint8_t mUSART_RXBuf_4ch[USART_BUF_MIN];
uint8_t mUSART_GetRXBuf_4ch[USART_BUF_Get];
uint8_t mUSART_TXBuf_4ch[USART_BUF_MIN];
uint8_t mUSART_RXBufBackUp_4ch[USART_BUF_MIN];


uint8_t mUSART_TIM_Flag = 0;
uint8_t mUSART_TIM_60sFlag = 0;




uint8_t mSSID_TIM_1sFlag = 0;


uint32_t mUSART_TIM_Cnt = 0;


uint8_t mXbeeSSID[3][2][10] = {"+++","OK","ATID\r","OK","ATCN\r","OK"};
uint8_t mXbeeSSIDFlagCnt = 0;
uint8_t mSSID[10];

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
uint16_t dUSART_Test = 0;
void USRAT_init(void)
{
  /*##-1- Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART1 configured as follow:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
      
 /*############################## USART1 ####################################*/      
  UartHandle1.Instance          = USART1;
  
  UartHandle1.Init.BaudRate     = 9600;
  UartHandle1.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle1.Init.StopBits     = UART_STOPBITS_1;
  UartHandle1.Init.Parity       = UART_PARITY_NONE;
  UartHandle1.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle1.Init.Mode         = UART_MODE_TX_RX;
  UartHandle1.Init.OverSampling = UART_OVERSAMPLING_16;
  

  HAL_UART_Init(&UartHandle1);
  
  HAL_UART_Receive_IT(&UartHandle1, (uint8_t *)mUSART_RXBuf_1ch, 1); // 인터럽트 발생.
  

 /*############################## USART3 ####################################*/
  UartHandle3.Instance          = USART3;
  
  UartHandle3.Init.BaudRate     = 9600;
  UartHandle3.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle3.Init.StopBits     = UART_STOPBITS_1;
  UartHandle3.Init.Parity       = UART_PARITY_NONE;
  UartHandle3.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle3.Init.Mode         = UART_MODE_TX_RX;
  UartHandle3.Init.OverSampling = UART_OVERSAMPLING_16;
  
    
  HAL_UART_Init(&UartHandle3);
  
  HAL_UART_Receive_IT(&UartHandle3, (uint8_t *)mUSART_RXBuf_3ch, 1);
  
  

 /*############################## UART4 ####################################*/  
  UartHandle4.Instance          = UART4;
  
  UartHandle4.Init.BaudRate     = 9600;
  UartHandle4.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle4.Init.StopBits     = UART_STOPBITS_1;
  UartHandle4.Init.Parity       = UART_PARITY_NONE;
  UartHandle4.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle4.Init.Mode         = UART_MODE_TX_RX;
  UartHandle4.Init.OverSampling = UART_OVERSAMPLING_16;
  
    
  HAL_UART_Init(&UartHandle4);
  
  HAL_UART_Receive_IT(&UartHandle4, (uint8_t *)mUSART_RXBuf_4ch, 1);
  

 /*############################## USART1 ####################################*/   
  USART_1Ch.nRxOK = 0;
  USART_1Ch.nRxOK_Cnt = 0;
  USART_1Ch.nRxLen = 40; // 초기 길이를 10으로 지정.
  USART_1Ch.nRxPos = 0;
  USART_1Ch.nRxTimeOut = 5;
  USART_1Ch.nTxLen = 10;
  USART_1Ch.nTxPos = 0;
  USART_1Ch.nTxOK = TRUE;
  USART_1Ch.nTxOK_Cnt = 0;
  USART_1Ch.nTxTimeOut = 200;
  USART_1Ch.nRxDlyTm = 0;
  USART_1Ch.nRxBuffer = mUSART_RXBuf_1ch;
  USART_1Ch.nGetRxBuf = mUSART_GetRXBuf_1ch;
  USART_1Ch.nTxBuffer = mUSART_TXBuf_1ch;
  USART_1Ch.nRxBuf_BackUp = mUSART_RXBufBackUp_1ch;
  
  memset(USART_1Ch.nRxBuffer,0,sizeof(mUSART_RXBuf_1ch));
  memset(USART_1Ch.nTxBuffer,0,sizeof(mUSART_TXBuf_1ch));
  memset(USART_1Ch.nRxBuf_BackUp,0,sizeof(mUSART_RXBufBackUp_1ch));

 /*############################## USART3 ####################################*/   
  USART_3Ch.nRxOK = 0;
  USART_3Ch.nRxOK_Cnt = 0;
  USART_3Ch.nRxLen = 20; // 초기 길이를 10으로 지정.
  USART_3Ch.nRxPos = 0;
  USART_3Ch.nTxLen = 10;
  USART_3Ch.nTxPos = 0;
  USART_3Ch.nTxOK = TRUE;
  USART_3Ch.nTxOK_Cnt = 0;
  USART_3Ch.nRxDlyTm = 0;
  USART_3Ch.nRxBuffer = mUSART_RXBuf_3ch;
  USART_3Ch.nGetRxBuf = mUSART_GetRXBuf_3ch;
  USART_3Ch.nTxBuffer = mUSART_TXBuf_3ch;
  USART_3Ch.nRxBuf_BackUp = mUSART_RXBufBackUp_3ch;
  
  memset(USART_3Ch.nRxBuffer,0,sizeof(mUSART_RXBuf_3ch));
  memset(USART_3Ch.nTxBuffer,0,sizeof(mUSART_TXBuf_3ch));
  memset(USART_3Ch.nRxBuf_BackUp,0,sizeof(mUSART_RXBufBackUp_3ch));
  
 /*############################## USART4 ####################################*/   
  USART_4Ch.nRxOK = 0;
  USART_4Ch.nRxOK_Cnt = 0;
  USART_4Ch.nRxLen = 10; // 초기 길이를 10으로 지정.
  USART_4Ch.nRxPos = 0;
  USART_4Ch.nTxLen = 10;
  USART_4Ch.nTxPos = 0;
  USART_4Ch.nTxOK = TRUE;
  USART_4Ch.nTxOK_Cnt = 0;
  USART_4Ch.nRxDlyTm = 0;
  USART_4Ch.nRxBuffer = mUSART_RXBuf_4ch;
  USART_4Ch.nGetRxBuf = mUSART_GetRXBuf_4ch;
  USART_4Ch.nTxBuffer = mUSART_TXBuf_4ch;
  USART_4Ch.nRxBuf_BackUp = mUSART_RXBufBackUp_4ch;
  
  memset(USART_4Ch.nRxBuffer,0,sizeof(mUSART_RXBuf_4ch));
  memset(USART_4Ch.nTxBuffer,0,sizeof(mUSART_TXBuf_4ch));
  memset(USART_4Ch.nRxBuf_BackUp,0,sizeof(mUSART_RXBufBackUp_4ch));
  

}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
uint16_t crc16_ccitt_Woojin(uint8_t *buf, int len)
{
	int counter;
	uint16_t crc = 0xFFFF;
	for( counter = 0; counter < len; counter++)
		crc = (crc<<8) ^ crc16tab[((crc>>8) ^ buf[counter])];
        
    buf[len] = WORD_L(crc);
    buf[len+1] = WORD_H(crc);
    
    buf[len+2] = 0x03;

	return crc;
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void USRAT_GPIO_Init(void)
{



}
/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/

void USART1_IRQHandler(void)
{
      HAL_UART_IRQHandler(& UartHandle1);
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/

void USART3_IRQHandler(void)
{
      HAL_UART_IRQHandler(& UartHandle3);
}
/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/

void UART4_IRQHandler(void)
{
      HAL_UART_IRQHandler(& UartHandle4);
}
/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/

void USARTRX_MainPro(void)
{
    uint8_t sRXBuf[5];
	uint8_t sKeypadFalg = 0;

    if(mUSARTRXFlag_1Ch)
    {
        mUSARTRXFlag_1Ch = 0;
        
		HAL_UART_Receive_IT(&UartHandle1, (uint8_t *)USART_1Ch.nGetRxBuf, 1);
			
        USART_1CH_PRO(USART_1Ch.nGetRxBuf);
		
		//printf("1ch --> 3ch BayPass \n\r");
		
    }
    else if(mUSARTRXFlag_4Ch)
    {
        mUSARTRXFlag_4Ch = 0;
		HAL_UART_Receive_IT(&UartHandle4, (uint8_t *)USART_4Ch.nGetRxBuf, 1);
        USART_4CH_PRO(USART_4Ch.nGetRxBuf);
        
    }
    else if(mUSARTRXFlag_3Ch)
    {
        mUSARTRXFlag_3Ch = 0;
		HAL_UART_Receive_IT(&UartHandle3, (uint8_t *)USART_3Ch.nGetRxBuf, 1);
			
		if(USART_1Ch.nTxTimeOut) //1ch 이 아직 타임 아웃이 아니면, XCTU와 통신  중이다.
		{
				USART_3CH_PRO_XCTU(USART_3Ch.nGetRxBuf);
		}
		else // 1ch과 통신 아웃이 되면, 프로토콜 함수 비교
		{
				USART_3CH_PRO(USART_3Ch.nGetRxBuf);
		}
        
    }
		
		/**************************버퍼 타이머 설정 변경 ***********************************/
		if(mUSART_TIM_Flag) // 1ms 마다 실행 통신 상태를 확인 한다.
		{

			mUSART_TIM_Flag = 0;
		   
			if(USART_1Ch.nRxTimeOut) /*######1ch######## */
			{
				USART_1Ch.nRxTimeOut--;
				if(USART_1Ch.nRxTimeOut ==1) //수신 타이머가 1이면서
				{	
					if(USART_1Ch.nRxPos) // 수신 데이타에 값이 있으면
					{
						HAL_UART_Transmit_IT(&UartHandle3, (uint8_t*)&USART_1Ch.nRxBuffer[0],USART_1Ch.nRxPos);
						
						USART_1Ch.nTxTimeOut = 200;
						
					}
				}
			}
			
			if(USART_3Ch.nRxTimeOut) /*######3ch######## */
			{
				USART_3Ch.nRxTimeOut--;
			
				if(USART_3Ch.nRxTimeOut ==1) //수신 타이머가 1이면서
				{	
					if(USART_3Ch.nRxPos) // 수신 데이타에 값이 있으면
					{
						
						
						if(mXbeeSSIDFlagCnt < 3)
						{
						
							if(!strncmp((char *)&USART_3Ch.nRxBuffer[0],(char *)"OK",2) && (mXbeeSSIDFlagCnt == 0))
							{
								mXbeeSSIDFlagCnt++;
								
							}
							else if(!strncmp((char *)&USART_3Ch.nRxBuffer[0],(char *)"LRV",3) && (mXbeeSSIDFlagCnt == 1))
							{
								mXbeeSSIDFlagCnt++;
								memcpy(mSSID,USART_3Ch.nRxBuffer,USART_3Ch.nRxPos);
							}
							if(!strncmp((char *)&USART_3Ch.nRxBuffer[0],(char *)"OK",2) && (mXbeeSSIDFlagCnt == 2))
							{
								mXbeeSSIDFlagCnt++;
							}
							
						}
						
						if(USART_1Ch.nTxTimeOut)
						{
							printf("wifi-RX OK \n\r");
							HAL_UART_Transmit_IT(&UartHandle1, (uint8_t*)&USART_3Ch.nRxBuffer[0],USART_3Ch.nRxPos);
						}
						
						

					}
				}
			}
			
			if(USART_4Ch.nRxTimeOut) /*######4ch######## */
			{
					USART_4Ch.nRxTimeOut--;
			}
			
			
			if(USART_1Ch.nTxTimeOut){USART_1Ch.nTxTimeOut--;}
			
			if(USART_3Ch.nTxTimeOut) // OCC 0x5x 코드에 내가 0xAx 코드로 응답하는 부분.
			{
				USART_3Ch.nTxTimeOut--;
				
				if(USART_3Ch.nTxTimeOut == 1)
				{
					USART_3ch_ROU_OPER_SEND(0,0x10,(USART_3Ch.nRxCommand + 0xA0),nWifi_InputDataRouteBuf,nWifi_InputDataOperatorBuf);
					
					mWifi_TRX_Flag.nOCC.nWifi_TX_Cnt++;
					
					
				}
				
			}
			if(USART_4Ch.nTxTimeOut){USART_4Ch.nTxTimeOut--;}
						
		}
		
		
		
		if(mWifi_TRX_Flag.nDRIVTimeCnt == 1 || mWifi_TRX_Flag.nStatusTimeCnt == 1) // Key pad 입력시 15초 만에 전송 기능 동작 , 정상적인 경우 60초 마다 라우터 통신 기능 동작.
		{
			
			mWifi_TRX_Flag.nDRIVTimeCnt = 0;
			mWifi_TRX_Flag.nStatusTimeCnt = 60000;
			
			nKeypadNum_ChangCnt = 0; //OCC 전송을 완료 했다면, ChangeCnt는 0으로 한다.
			
		//if(mUSART_TIM_60sFlag) // 60초 마다 전송 하는 기능 test.
		//{
			mUSART_TIM_60sFlag = 0;
			if(nKeypadNum_ChangFlage)
			{
				sKeypadFalg = (nKeypadNum_ChangFlage == 0x03) ? 0x51 : ((nKeypadNum_ChangFlage == 0x01) ? 0x52 : 0x53)  ;
				
				mWifi_TRX_Flag.nDRIV.nWifi_TX_Cnt++;
			}
			else 
			{
				sKeypadFalg = 0x01;  
				
				mWifi_TRX_Flag.nStatus.nWifi_TX_Cnt++;
				
			}
	
			
			USART_3ch_ROU_OPER_SEND(0,0x10, sKeypadFalg ,&nKeypad_InputDataRouteBuf[0],&nKeypad_InputDataOperatorBuf[0]);
			
			//nKeypadNum_ChangFlage = 0;
			
		//}
		}
		
		
		if(mSSID_TIM_1sFlag && (mXbeeSSIDFlagCnt<3))
		{
			mSSID_TIM_1sFlag = 0;
			
			XbeeSSIDREAD();
		}
		
		
		
		if(USART_3Ch.nRxOK)
		{
			USART_3Ch.nRxOK = 0;
			
			USART_3CH_RXPRO(USART_3Ch.nRxBuf_BackUp);
				
		}

}


/*****************************************************************************
  * @brief  Tx Transfer completed callback
  * @param  UartHandle: UART handle. 
  * @note   This example shows a simple way to report end of IT Tx transfer, and 
  *         you can add your own implementation. 
  * @retval None
  ******************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Set transmission flag: transfer complete */
	//UartReady = SET;



}

/*****************************************************************************
  * @brief  Rx Transfer completed callback
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report end of IT Rx transfer, and 
  *         you can add your own implementation.
  * @retval None
  ******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Set transmission flag: transfer complete */
	//UartReady = SET;


	if(huart->Instance == USART1)
	{

		mUSARTRXFlag_1Ch = 1;
		
		

	}
	else  if(huart->Instance == UART4)
	{
		mUSARTRXFlag_4Ch = 1;
		

	}
	else  if(huart->Instance == USART3)
	{
		mUSARTRXFlag_3Ch = 1;

		
	}
	
}

/*****************************************************************************
  * @brief  UART error callbacks
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  ******************************************************************************/
 void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  /* Turn LED3 on: Transfer error in reception/transmission process */

}

/*****************************************************************************
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 0  : pBuffer1 identical to pBuffer2
  *         >0 : pBuffer1 differs from pBuffer2
  ******************************************************************************/
uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
	while (BufferLength--)
	{
		if ((*pBuffer1) != *pBuffer2)
		{
		  return BufferLength;
		}
		pBuffer1++;
		pBuffer2++;
	}

	return 0;
}
/*****************************************************************************
* @brief - USART_1CH_PRO
* @param - XCTU 와 연결 컨넥션 하는 기능으로 사용.
* @retval-
******************************************************************************/

void USART_1CH_PRO(uint8_t *pData)
{

    if(!USART_1Ch.nRxTimeOut) { USART_1Ch.nRxPos = 0;}
        
    USART_1Ch.nRxTimeOut = 5;
    
    USART_1Ch.nRxBuffer[USART_1Ch.nRxPos++] = pData[0];
		

    switch(USART_1Ch.nRxPos)
    {
    case 0x01 :
				
				
        break;
    case 0x02 :
    
        break;
    
    default :
        if(USART_1Ch.nRxPos >= USART_1Ch.nRxLen )
        {
            USART_1Ch.nRxPos = 0;
            
            memcpy(USART_1Ch.nRxBuf_BackUp , USART_1Ch.nRxBuffer,USART_1Ch.nRxLen);
            
        }
        break;
     }
		 
     
}
/*****************************************************************************
* @brief - USART_1CH_PRO
* @param -
* @retval-
******************************************************************************/
void USART_3CH_PRO_XCTU(uint8_t *pData)
{
		
    if(!USART_3Ch.nRxTimeOut) { USART_3Ch.nRxPos = 0;}
        
    USART_3Ch.nRxTimeOut = 5;
    
    USART_3Ch.nRxBuffer[USART_3Ch.nRxPos++] = pData[0];
		
		
    switch(USART_3Ch.nRxPos)
    {
    case 0x01 :
      
        break;
    case 0x02 :
    
        break;

    default :
			

        if(USART_3Ch.nRxPos >= USART_3Ch.nRxLen)
        {
            USART_3Ch.nRxPos = 0;
            
            memcpy(USART_3Ch.nRxBuf_BackUp , USART_3Ch.nRxBuffer,USART_3Ch.nRxLen);
           
            
        }
        break;
     }
		 
     
}

/*****************************************************************************
* @brief - USART_1CH_PRO
* @param -
* @retval-
******************************************************************************/

void USART_3CH_PRO(uint8_t *pData)
{
	uint8_t i;
	uint8_t sRxBuf[30];
	char dDebugText[30];

	//int sTXBufCnt = 0;

	uint8_t sRXBuf_Cnt = 0;
	uint8_t sRXBuf_Cnt_1 = 0;
	uint16_t sCRCDATA = 0;
	uint16_t sCRCDATA_Check = 0;

	pUSART_PROTOCOL_HEAD pRXHead;


	memset(sRxBuf,0x00,30);
	
    if(!USART_3Ch.nRxTimeOut) { USART_3Ch.nRxPos = 0;}
        
    USART_3Ch.nRxTimeOut = 5;
    
    USART_3Ch.nRxBuffer[USART_3Ch.nRxPos++] = pData[0];
    
		
    switch(USART_3Ch.nRxPos)
    {
    case 0x01 :
        if(USART_3Ch.nRxBuffer[0] != 0x10) {  USART_3Ch.nRxPos = 0;}
        break;
    case 0x02 :
		if(USART_3Ch.nRxBuffer[1] != STX) {  USART_3Ch.nRxPos = 0;}
        break;
				
	case 0x03 :
		USART_3Ch.nRxLen  = (USART_3Ch.nRxBuffer[2] +6);
		
		break;
	
	default :
					
			if(USART_3Ch.nRxBuffer[USART_3Ch.nRxPos-2]  == 0x10 && USART_3Ch.nRxBuffer[USART_3Ch.nRxPos-1]  == 0x03)
			{

				memcpy(&USART_3Ch.nRxBuf_BackUp[0] ,&USART_3Ch.nRxBuffer[0],USART_3Ch.nRxPos);

				sRXBuf_Cnt_1 = USART_STUFF_DIVIDE(USART_3Ch.nRxBuf_BackUp,sRxBuf,USART_3Ch.nRxPos);


				sCRCDATA = MAKE_WORD(sRxBuf[sRXBuf_Cnt_1-3],sRxBuf[sRXBuf_Cnt_1-2]); 

				crc16_ccitt_Woojin(&sRxBuf[1],sRXBuf_Cnt_1-4);
				sCRCDATA_Check = MAKE_WORD(sRxBuf[sRXBuf_Cnt_1-3],sRxBuf[sRXBuf_Cnt_1-2]);


				if(sCRCDATA == sCRCDATA_Check)
				{
					memcpy(&USART_3Ch.nRxBuf_BackUp[0],&sRxBuf[0],sRXBuf_Cnt_1);

					USART_3Ch.nRxOK = 1;
					USART_3Ch.nRxLen = sRXBuf_Cnt_1;
					
					USART_3Ch.nRxOK_Cnt = (USART_3Ch.nRxOK_Cnt > 100) ? 0 : (USART_3Ch.nRxOK_Cnt +1);
					
					

					MyPrintf(sRxBuf,sRXBuf_Cnt_1," %d-USART3 Wifi RX OK : ",mUSART_TIM_Cnt);
					//MyPrintf(sRxBuf,sRXBuf_Cnt_1);
							
				}
				else
				{
					MyPrintf_USART1("USART3 Wifi CRC NG, R-%4X, S - %4X \n\r",sCRCDATA,sCRCDATA_Check);
				}


				USART_3Ch.nRxPos = 0;


			}

				
		break;
		}
		 
     
}
/*****************************************************************************
* @brief - USART_1CH_PRO
* @param -
* @retval-
******************************************************************************/
void USART_4CH_PRO(uint8_t *pData)
{

    if(!USART_4Ch.nRxTimeOut) { USART_4Ch.nRxPos = 0;}
        
    USART_4Ch.nRxTimeOut = 10;
    
    USART_4Ch.nRxBuffer[USART_4Ch.nRxPos++] = pData[0];
    
    switch(USART_1Ch.nRxPos)
    {
    case 0x01 :
        //if(USART_4Ch.nRxBuffer[0] != STX) {  USART_4Ch.nRxPos = 0;}
        break;
    case 0x02 :
    
        break;
    
    default :
        if(USART_4Ch.nRxPos >= USART_4Ch.nRxLen)
        {
            USART_4Ch.nRxPos = 0;
            
            memcpy(USART_4Ch.nRxBuf_BackUp , USART_4Ch.nRxBuffer,USART_4Ch.nRxLen);
            
            printf("%s \n\r",&USART_4Ch.nRxBuffer[0]);
            
        }
        break;
     }
     
}
/*****************************************************************************
* @brief - 1ms 타이머 함수
* @param -
* @retval-
******************************************************************************/
void USART_TIM(void)
{
	
		mUSART_TIM_Flag = 1;
	
		mUSART_TIM_Cnt++;
		//Keypad 누르면, 일정 시간동안 추가로 기다린다.
		if(!(mUSART_TIM_Cnt%(30000+ (nKeypadNum_ChangFlage*5000)))){ mUSART_TIM_60sFlag  = 1; }
		
		if(!(mUSART_TIM_Cnt%2000)) {mSSID_TIM_1sFlag = 1;}
		

}


/*****************************************************************************
* @brief - 1ms 타이머 함수
* @param -
* @retval-
******************************************************************************/
void USART_3ch_ROU_OPER_SEND(uint8_t sSequeNum,uint8_t sCommCod1,uint8_t sCommCod2,uint8_t *pRou,uint8_t *pOper)
{
		int sBuf_Cnt = 0;
		int i;
		uint8_t sTxBuf[30];
		int sTXBufCnt = 0;
	
		sCommCod2 = ((sCommCod2&0x0F) > 3)  ? (sCommCod2&0xF1) : sCommCod2; 
	
		//USART_3Ch.nTxBuffer[sBuf_Cnt++] = 0x10;
		USART_3Ch.nTxBuffer[sBuf_Cnt++] = 0x02;

		if((sCommCod2&0x0F) == 0x01)
		{ 
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = 0x0F;
		}
		else if((sCommCod2&0x0F) == 0x02)
		{
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = 0x0A;
		}
		else if((sCommCod2&0x0F) == 0x03)
		{
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = 0x0C;
		}
		
		USART_3Ch.nTxBuffer[sBuf_Cnt++] = 0x00;
	
		if(!sSequeNum) //시퀀스 넘버가 0 이면 우진 TX DATA 를 송부 하는 것으로, 우진에 시권스 넘버를 적용한다.
		{
			USART_3Ch.nTxOK_Cnt = (USART_3Ch.nTxOK_Cnt > 127) ? 0: (USART_3Ch.nTxOK_Cnt+1);
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = USART_3Ch.nTxOK_Cnt;
		}
		else // 응답하는 부분으로 0x80을 더하여 응답 한다.
		{
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = sSequeNum + 0x80;
		}
		

		USART_3Ch.nTxBuffer[sBuf_Cnt++] = sCommCod1;
		USART_3Ch.nTxBuffer[sBuf_Cnt++] = sCommCod2;

		
		if((sCommCod2&0x0F) == 0x01)
		{
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pRou[0] ;
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pRou[1] ;
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pRou[2] ;
			
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pOper[0] ;
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pOper[1] ;
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pOper[2] ;
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pOper[3] ;
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pOper[4] ;
			
		}
		else if((sCommCod2&0x0F) == 0x02)
		{
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pRou[0] ;
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pRou[1] ;
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pRou[2] ;
			
		}
		else if((sCommCod2&0x0F) == 0x03)
		{
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pOper[0] ;
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pOper[1] ;
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pOper[2] ;
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pOper[3] ;
			USART_3Ch.nTxBuffer[sBuf_Cnt++] = pOper[4] ;
			
		}
		
		crc16_ccitt_Woojin(&USART_3Ch.nTxBuffer[1],(sBuf_Cnt-1));
		
		sTXBufCnt = USART_STUFF_ADD(USART_3Ch.nTxBuffer,sTxBuf,sBuf_Cnt+3); // STUFF 프로토콜 추가 하는 함수.
		 
		 memcpy(USART_3Ch.nTxBuffer,sTxBuf,sTXBufCnt);
		 
		 HAL_UART_Transmit_IT(&UartHandle3, (uint8_t*)&USART_3Ch.nTxBuffer[0],sTXBufCnt);
		 
		if((sCommCod2&0x0F) == 0x01)     {MyPrintf(&USART_3Ch.nTxBuffer[0],sTXBufCnt,"%d-wifi ROU-OPER TX :",mUSART_TIM_Cnt);}
		else if((sCommCod2&0x0F) == 0x02){MyPrintf(&USART_3Ch.nTxBuffer[0],sTXBufCnt,"%d-wifi ROU TX :",mUSART_TIM_Cnt);}
		else if((sCommCod2&0x0F) == 0x03){MyPrintf(&USART_3Ch.nTxBuffer[0],sTXBufCnt,"%d-wifi OPER TX :",mUSART_TIM_Cnt);}
		//MyPrintf(&USART_3Ch.nTxBuffer[0],sTXBufCnt);
		
}


/*****************************************************************************
* @brief - 1ms 타이머 함수
* @param -
* @retval-
******************************************************************************/
uint8_t USART_STUFF_ADD(uint8_t *pInData,uint8_t *pOutData,uint8_t Len)
{
	int sInCnt = 0;
	int sOutCnt = 0;

	for(sInCnt =0; sInCnt < Len ;sInCnt++)
	{
		if(pInData[sInCnt] == 0x02 || pInData[sInCnt] == 0x03 || pInData[sInCnt] == 0x10)
		{
			if(pInData[sInCnt] == 0x02 && sInCnt <= 2)
			{				
				pOutData[sOutCnt++] = 0x10;
				pOutData[sOutCnt++] = pInData[sInCnt];
			}
			else if(pInData[sInCnt] == 0x03 && sInCnt >= (Len-2) )
			{
				pOutData[sOutCnt++] = 0x10;
				pOutData[sOutCnt++] = pInData[sInCnt];
			}
			else if(pInData[sInCnt] == 0x10)
			{
				pOutData[sOutCnt++] = 0x10;
				pOutData[sOutCnt++] = pInData[sInCnt];
			}
			else
			{
				pOutData[sOutCnt++] = pInData[sInCnt];
			}
			
		}
		else
		{
			pOutData[sOutCnt++] = pInData[sInCnt];		
		}
	}

	return sOutCnt;

}
	
/*****************************************************************************
* @brief - 1ms 타이머 함수
* @param -
* @retval-
******************************************************************************/
uint8_t USART_STUFF_DIVIDE(uint8_t *pInData,uint8_t *pOutData,uint8_t Len)
{
	int sInCnt = 0;
	int sOutCnt = 0;

	for(sInCnt =0; sInCnt < Len ;sInCnt++) // 0x10코드를 제거하고, 오리지날 데이타를 추출한다.
	{
		if(pInData[sInCnt] == 0x10)
		{
			sInCnt++;

			pOutData[sOutCnt++] = USART_3Ch.nRxBuf_BackUp[sInCnt];

		}
		else
		{
			pOutData[sOutCnt++] = USART_3Ch.nRxBuf_BackUp[sInCnt];
		}					
	}

	return sOutCnt;
}


/*****************************************************************************
* @brief - USART_3CH_RXPRO 통신 수신 데이타를 처리하는 함수.
* @param -
* @retval-
******************************************************************************/
void USART_3CH_RXPRO(uint8_t *pData)
{
		//uint8_t sBuf_ROU[10];
		//uint8_t sBuf_OPER[10];
	
		pUSART_PROTOCOL_HEAD pHead = (USART_PROTOCOL_HEAD *) pData;
	
		pUSART_ROUTEID_PTC pRouteID;
		pUSART_OPERATOR_PTC pOperatorID;
		pUSART_ROU_OPER_PTC pRou_OperID;
	
		memset(nWifi_InputDataRouteBuf,0x00,sizeof(nWifi_InputDataRouteBuf));
		memset(nWifi_InputDataOperatorBuf,0x00,sizeof(nWifi_InputDataOperatorBuf));
	
		//프로토콜 길이를 확인 하는 부분으로 고통으로 사용한다.
		if((pHead->CommCod2&0x0F) == 0x01)     
		{ 
			pRou_OperID = (USART_ROU_OPER_PTC *) pData;
			
			memcpy(&nWifi_InputDataRouteBuf[0],&pRou_OperID->nRouteIDBuf[0],3);
			memcpy(&nWifi_InputDataOperatorBuf[0],&pRou_OperID->nOperatorIDBuf[0],5);
			
			
			USART_3Ch.nRxCommand = 0x01;
			
			
		}
		else if((pHead->CommCod2&0x0F) == 0x02)
		{ 
			pRouteID    = (USART_ROUTEID_PTC *) pData;
			
			memcpy(nWifi_InputDataRouteBuf,&pRouteID->nRouteIDBuf[0],3);
			
			USART_3Ch.nRxCommand = 0x02;
			
		}
		else if((pHead->CommCod2&0x0F) == 0x03)
		{ 
			pOperatorID = (USART_OPERATOR_PTC *) pData;
			
			memcpy(nWifi_InputDataOperatorBuf,&pOperatorID->nOperatorIDBuf[0],5);
			
			USART_3Ch.nRxCommand = 0x03;
		}
	
	
		
		if(pHead->CommCod1 == 0x10) // ACK, RNS 장치 ID가 0x10 이므로  occ에서 ACK전송 한것이다.
		{
			//ACK를 확인 .
			nKeypadNum_ChangFlage = 0; // ACK가 수신 되면, 0으로 클리어 한다.	
			
			mWifi_TRX_Flag.nStatus.nWifi_RX_Cnt++;
			
			
		}
		else if(pHead->CommCod1 == 0x80) // occ에서 송부 한 데이타. 내가 ACK  를 전송 해야한다.
		{
			if(((pHead->CommCod2)&0xF0) == 0x10)
			{
				USART_3ch_ROU_OPER_SEND(0,0x10,pHead->CommCod2,&nKeypad_InputDataRouteBuf[0],&nKeypad_InputDataOperatorBuf[0]);
			}
			else if(((pHead->CommCod2)&0xF0) == 0x50)
			{
				
				USART_3ch_ROU_OPER_SEND((pHead->SequeNum),pHead->CommCod1,pHead->CommCod2,&nWifi_InputDataRouteBuf[0],&nWifi_InputDataOperatorBuf[0]);
				
				if((pHead->CommCod2&0x0F) == 1)
				{
					memcpy(nKeypad_InputDataRouteBuf,nWifi_InputDataRouteBuf,3);
					memcpy(nKeypad_InputDataOperatorBuf,nWifi_InputDataOperatorBuf,5);
					memcpy(&nKeypad_InputDataBuf[0],&nKeypad_InputDataRouteBuf[0],3);
					
					// 18_0119 -> 버그 수정(wifi 수신 데이타는 갱신 하는 부분이 없음)
					InputDataRouteNum = ConvAsc2Hex(nKeypad_InputDataBuf[0]);
					InputDataRouteNum = (InputDataRouteNum << 8)|ConvAsc2Hex(nKeypad_InputDataBuf[1]);
					InputDataRouteNum = (InputDataRouteNum << 8)|ConvAsc2Hex(nKeypad_InputDataBuf[2]);
					
				}
				else if((pHead->CommCod2&0x0F) == 2)
				{
					memcpy(nKeypad_InputDataRouteBuf,nWifi_InputDataRouteBuf,3);
					memcpy(&nKeypad_InputDataBuf[0],&nKeypad_InputDataRouteBuf[0],3);
								
					// 18_0119 -> 버그 수정(wifi 수신 데이타는 갱신 하는 부분이 없음)
					InputDataRouteNum = ConvAsc2Hex(nKeypad_InputDataBuf[0]);
					InputDataRouteNum = (InputDataRouteNum << 8)|ConvAsc2Hex(nKeypad_InputDataBuf[1]);
					InputDataRouteNum = (InputDataRouteNum << 8)|ConvAsc2Hex(nKeypad_InputDataBuf[2]);
					
				}
				else if((pHead->CommCod2&0x0F) == 3)
				{
					memcpy(nKeypad_InputDataOperatorBuf,nWifi_InputDataOperatorBuf,5);
				}
				
				
				//메모리 저장하는 부분.
				memcpy(&mFlashMemoySaveBuf[1],nKeypad_InputDataRouteBuf,3);
				memcpy(&mFlashMemoySaveBuf[4],nKeypad_InputDataOperatorBuf,5);			
				mFlashSaveCnt = 10000;
				
				mWifi_TRX_Flag.nOCC.nWifi_RX_Cnt++;
				
				
				
				USART_3Ch.nTxTimeOut = 500; // 500ms 있다가 한번더 전송 한다.
			}
			else if(((pHead->CommCod2)&0xF0) == 0xA0)
			{
				if(pHead->SequeNum < 0x80) // 설정 완료 응답을 수신하면,
				{
					//ACK를 전송 한다.
					USART_3ch_ROU_OPER_SEND((pHead->SequeNum),pHead->CommCod1,pHead->CommCod2,&nWifi_InputDataRouteBuf[0],&nWifi_InputDataOperatorBuf[0]);
					
					
					mWifi_TRX_Flag.nDRIV.nWifi_RX_Cnt++;
						
				}
				
				
			}
			
			
		}
}

/*****************************************************************************
* @brief - MyPrintf
* @param -
* @retval-
******************************************************************************/

void XbeeSSIDREAD(void)
{
	USART_1Ch.nTxTimeOut = 500;
	
	if(mXbeeSSIDFlagCnt == 0)
	{
		HAL_UART_Transmit_IT(&UartHandle3, (uint8_t*)&mXbeeSSID[0][0][0],3);
	}
	else if(mXbeeSSIDFlagCnt == 1)
	{
		HAL_UART_Transmit_IT(&UartHandle3, (uint8_t*)&mXbeeSSID[1][0][0],5);
	}
	else if(mXbeeSSIDFlagCnt == 2)
	{
		HAL_UART_Transmit_IT(&UartHandle3, (uint8_t*)&mXbeeSSID[2][0][0],5);
	}

}



/*****************************************************************************
* @brief - MyPrintf
* @param -
* @retval-
******************************************************************************/

void MyPrintf(uint8_t *pData,int len,char * format, ...)
{
	int i;
	int sLne;

	uint8_t sBuf[512];
	uint8_t sBuf_2[10];
	
	va_list args;
	static char szBuf2[2048];
	
	va_start(args, format);
	vsprintf(szBuf2, format, args);
	
	sLne = strlen(szBuf2);
	
	memcpy(&sBuf[0],(uint8_t*)szBuf2,sLne);
	
	
	for(i = 0; i < len; i++)
	{
		//printf("%02X-",pData[i]);
		
		sprintf((char*)&sBuf_2[0],"%02X-", pData[i]);
		memcpy(&sBuf[sLne+(i*3)],&sBuf_2[0],3);
		
	}

	
	//printf("\n\r");
	
	sprintf((char*)&sBuf_2[0],"\n\r");
	memcpy(&sBuf[sLne + (i*3)],&sBuf_2[0],4);
	
	HAL_UART_Transmit_IT(&UartHandle1, (uint8_t *)&sBuf[0],sLne + (i*3)+2);
	
	va_end(args);
	
	
	
}


//*********************************************************************************************************
// MyPrintf_USART1
//*********************************************************************************************************


void MyPrintf_USART1(char * format, ... )
{
	va_list args;
	static char szBuf[2048];
	
	va_start(args, format);
	vsprintf(szBuf, format, args);
	

	HAL_UART_Transmit_IT(&UartHandle1, (uint8_t*)szBuf,strlen(szBuf));


	va_end(args);
}

//*****************************************************************************************
//	BCD_BIN
//*****************************************************************************************
uint16_t BCD_BIN(uint16_t nInput)
{
	uint16_t sNum = 0;

	sNum += ((nInput>>12)&0xf) * 1000;
	sNum += ((nInput>>8)&0xf) * 100;
	sNum += ((nInput>>4)&0xf) * 10;
	sNum += ((nInput)&0xf) * 1;
	return sNum;
}

//*****************************************************************************************
//	ASC? HEX? ???.
//*****************************************************************************************
uint8_t ConvAsc2Hex(char chDat)
{
	int nBuf = 0;	
	if(chDat >= '0' && chDat <= '9') nBuf = chDat-'0';		
	else
	if(chDat >= 'a' && chDat <= 'f') nBuf = ((chDat-'a') + 10);		
	else
	if(chDat >= 'A' && chDat <= 'F') nBuf = ((chDat-'A') + 10);
	
	return nBuf;
}

//*****************************************************************************************
//	???? ASC? HEX? ???.
//*****************************************************************************************
int FunConvAscHex(char *InchData,uint8_t *OuthexData,int Len)
{
	int i;
	int sCnt = 0;
	for(i=0;i<Len; )
	{
		OuthexData[sCnt] = (ConvAsc2Hex(InchData[i++])<<4)&0xF0;
		OuthexData[sCnt] |= ConvAsc2Hex(InchData[i++])&0x0F;

		sCnt++;
	}
	return sCnt;
}

//*****************************************************************************************
//	?? ASC???
//*****************************************************************************************
uint8_t IsNumAsc(char nCh)
{
	if(nCh >= '0' && nCh <= '9') return TRUE;
	return FALSE;
}

//*****************************************************************************************
//	ASC? DEC? ???.
//*****************************************************************************************
uint8_t ConvAsc2Dec(char nCh)
{
	int nBuf = 0;	
	if(nCh >= '0' && nCh <= '9') nBuf = nCh-'0'; else return 0;
	return nBuf;
}

//*****************************************************************************************
//	HEX? ASC? ???.
//*****************************************************************************************
char ConvHex2Asc(uint8_t btCh)
{
	char chBuf = '0';
	if(btCh >= 0 && btCh <= 9) chBuf = btCh+'0';
	else if(btCh >= 10 && btCh <= 15) chBuf = (btCh-10)+'A';
	return chBuf;
}
//*****************************************************************************************
//	DEC? HEX? ???.
//*****************************************************************************************
int ConvDec2Hex(char nCh)
{
	return ((((nCh / 0x10) & 0x0F) << 4) | ((nCh % 0x10) & 0x0F));
}

int FunConvHexAsc(uint8_t *InhexData,char *OUTAscData,int Len)
{
	int i;
	int sCnt = 0;
	for(i=0;i<Len;i++)
	{
		OUTAscData[sCnt++] = ConvHex2Asc(BYTE_H(InhexData[i]));
		OUTAscData[sCnt++] = ConvHex2Asc(BYTE_L(InhexData[i]));
	}
	return sCnt;
}





