#include "Keypad.h"
#include "Flash.h"
#include "main.h"
#include <string.h>



//extern uint32_t nTime_Flage;
//extern uint32_t nTime_Flage_500us;

uint16_t nKeypad_Flage_IN = 0;
uint16_t nKeypad_ScanCnt = 0;
uint16_t nKeypad_Prodata = 0;
uint16_t nKeypad_ReProdata = 0;

uint16_t nKeypad_PushButton = 0;
uint16_t nKeypad_DataBuf[12] = {23,14,30,46, 13,29,45,   11,27,43,  7,39}; //0,1,2,3,4,5,6,7,8,9,*,#
uint8_t nKeypad_InputDataBuf[5];

uint16_t nLineSelectFlg = 0;

uint32_t InputDataRouteNum = 0x0000;
uint64_t InputDataOperatorNum =0x00000;

uint8_t nKeypad_InputDataRouteBuf[3];
uint8_t nKeypad_InputDataOperatorBuf[5];

uint8_t nWifi_InputDataRouteBuf[3]; // 통신으로 수신한 데이타.
uint8_t nWifi_InputDataOperatorBuf[5]; // 통신으로 수신한 데이타.

uint8_t nKeypadNum_ChangCnt = 0; // keypad 값이 변경 되었는지 확인 한다.
uint8_t nKeypadOper_ChangCnt = 0; 
uint8_t nKeypadNum_ChangFlage = 0; // 변경 되었다면, Flage 정보를  활설화 한다.


uint8_t nLED_Light_Step = 0; // LED 밝기를 조절 하는 기능을 담당.

int nKeyKeep = 0;
int nKeyKeepCnt = 0;
int nKeyKeepCnt2 = 0;

/*****************************************************************************
* @brief -  PB - GPIO_PIN_15    KeyPad 0 
*           PC - GPIO_PIN_0     KeyPad 1
*           PC - GPIO_PIN_6     KeyPad 2
*           PC - GPIO_PIN_7     KeyPad 3
*           PC - GPIO_PIN_8     KeyPad 4
*           PC - GPIO_PIN_9     KeyPad 5
*           PC - GPIO_PIN_12    KeyPad 6
*           PC - GPIO_PIN_13    KeyPad 7
* @param -
* @retval-
******************************************************************************/
void Keypad_GPIO_Init(void)
{

    GPIO_InitTypeDef   GPIO_InitStructure;

    /* Enable GPIOx clock */
    __GPIOF_CLK_ENABLE();
    __GPIOG_CLK_ENABLE();

    /* Configure PA0 pin as input floating */

    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    
    HAL_GPIO_Init(GPIOF, &GPIO_InitStructure); 


    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    
    HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);


    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;  
    GPIO_InitStructure.Pin =  GPIO_PIN_3 | GPIO_PIN_4 ;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    
    HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);

		
	// 버퍼 클리어
	memset(nKeypad_InputDataBuf,0x00,sizeof(nKeypad_InputDataBuf));
	memset(nKeypad_InputDataRouteBuf,0x30,sizeof(nKeypad_InputDataRouteBuf));
	memset(nKeypad_InputDataOperatorBuf,0x30,sizeof(nKeypad_InputDataOperatorBuf));
		

}


/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/


void Keypad_ScanDo(void)
{
    int i;
    int sDaata = 0;
  
    nKeypad_ScanCnt++;
    
    
    sDaata = nKeypad_ScanCnt%3;
    
    
    if(sDaata)
    {
        if((sDaata) == 1)
        {

            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_RESET);            // 3,6,9
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15, GPIO_PIN_SET);  
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_SET);

            nKeypad_Prodata =  0x20; 
         }
         else if((sDaata) == 2)
         {
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14,GPIO_PIN_SET);            
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15,GPIO_PIN_RESET);   // 2,5,8
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3,  GPIO_PIN_SET);

            nKeypad_Prodata =  0x10; 
         
         }
        
    }
    else
    {
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14,GPIO_PIN_SET);            
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15,GPIO_PIN_SET);  
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3,  GPIO_PIN_RESET); // 1,4,7
        
        nKeypad_Prodata =  0x0; 
        
    }


}


/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
int Cnt_147 = 0;
int Cnt_258 = 0;
int Cnt_369 = 0;
void KeyPad_ScanInput(void)
{
    int i;

    nKeypad_Flage_IN =  HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10);
    nKeypad_Flage_IN |= HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_11) << 1;
    nKeypad_Flage_IN |= HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_12) << 2;
    nKeypad_Flage_IN |= HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_13) << 3;  
    

    if(nKeypad_Prodata == 0x20)
    {

       if(nKeypad_Flage_IN != 0x0F)
        {   
            
            Cnt_147 = 0;
            Cnt_258 = 0;
            Cnt_369++;
            
            KeyPad_RetunData(nKeypad_Flage_IN|0x20,Cnt_369);
            
            nKeyKeepCnt2 = 100;
        }
     
   
    }
    else if(nKeypad_Prodata == 0x10)
    {
 
       if(nKeypad_Flage_IN != 0x0F)
        {   
            Cnt_147 = 0;
            Cnt_258++;
            Cnt_369 = 0;       

            KeyPad_RetunData(nKeypad_Flage_IN|0x10,Cnt_369);     

             nKeyKeepCnt2 = 100;
            
        }
      
        
   
    } else if(nKeypad_Prodata == 0)
    {


       if(nKeypad_Flage_IN != 0x0F)
        {   
            Cnt_147++;
            Cnt_258 = 0;
            Cnt_369 = 0;   
            
            KeyPad_RetunData(nKeypad_Flage_IN,Cnt_369);   

            nKeyKeepCnt2 = 100;     
            
        }
      
   
    }


     if(nKeyKeepCnt2) // 같은 KeyPad를 일정시간 후 누르면 동작 하도록 딜레이 타임처리
     {
        nKeyKeepCnt2--;
     }
     else if(!(nKeyKeepCnt2))
     {
        nKeyKeep = 0;
        nKeypad_ReProdata = 0;
     }


}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/

int KeyPad_RetunData(int Input,int Cnt)
{
    int i=0;

    
    if( nKeyKeep !=  Input)
    {
        nKeyKeep = Input;
        nKeyKeepCnt = 0;
    }
     
    
    if(nKeyKeep == Input)
    {
        nKeyKeepCnt++;
        
        if(nKeyKeepCnt > 10 && nKeypad_ReProdata != Input) // 체터링 방지를 위해 같은 값을 10번 비교하여  처리.
        {
        
             for(i=0;i<12;i++)
            {
                if(Input == nKeypad_DataBuf[i])
                {
                


                    nKeypad_ReProdata = Input;

                    nKeypad_PushButton = i;
//                    printf(" nKeypad_PushButton : %d  \n\r",nKeypad_PushButton);

									
									
					if(nKeypad_PushButton == 11) //#키를 누르면 라인을 변경 한다.
					{

						
//						if(nKeypadNum_ChangCnt)
//						{
//							nKeypadNum_ChangCnt = 0;
//							
//							nKeypadNum_ChangFlage = 0x1;
//							
//							memcpy(&mFlashMemoySaveBuf[1],nKeypad_InputDataRouteBuf,3);
//							memcpy(&mFlashMemoySaveBuf[4],nKeypad_InputDataOperatorBuf,5);
//							
//							mFlashSaveCnt = 10000;
//							
//							mWifi_TRX_Flag.nDRIVTimeCnt = 15000;
//							mWifi_TRX_Flag.nStatusTimeCnt = 60000;
//							
//							
//							

//						}
//						else if(nKeypadOper_ChangCnt)
//						{
//							nKeypadOper_ChangCnt = 0;
//							
//							nKeypadNum_ChangFlage |= 0x02;
//							
//							
//							memcpy(&mFlashMemoySaveBuf[1],nKeypad_InputDataRouteBuf,3);
//							memcpy(&mFlashMemoySaveBuf[4],nKeypad_InputDataOperatorBuf,5);
//							
//							mFlashSaveCnt = 10000;
//							
//							mWifi_TRX_Flag.nDRIVTimeCnt = 15000;
//							mWifi_TRX_Flag.nStatusTimeCnt = 60000;
//	
//							
//						}

						nLineSelectFlg = ~nLineSelectFlg;
						
					}
					else if(nKeypad_PushButton == 10) // * 키를 누르면 동작 기능.
					{
						
						nLED_Light_Step++;
						
						nLED_Light_Step = (nLED_Light_Step %2);
						
						mFlashSaveCnt = 10000;
						
						
					}										
					else
					{

						if(!nLineSelectFlg) // 1번째 줄
						{
							nKeypadNum_ChangCnt++;
							
							nKeypadNum_ChangFlage = 0x1;
							
							mWifi_TRX_Flag.nDRIVTimeCnt = 15000;
							mWifi_TRX_Flag.nStatusTimeCnt = 60000;
							
							mFlashSaveCnt = 10000;
							
							
							InputDataRouteNum  = InputDataRouteNum<<8;
							InputDataRouteNum |= nKeypad_PushButton;
							
							nKeypad_InputDataRouteBuf[0] = (InputDataRouteNum >> 16)+0x30;
							nKeypad_InputDataRouteBuf[1] = (InputDataRouteNum >> 8) + 0x30;
							nKeypad_InputDataRouteBuf[2] = (InputDataRouteNum)+0x30;
							
							memcpy(&nKeypad_InputDataBuf[0],&nKeypad_InputDataRouteBuf[0],3);
							
							memcpy(&mFlashMemoySaveBuf[1],nKeypad_InputDataRouteBuf,3);
							memcpy(&mFlashMemoySaveBuf[4],nKeypad_InputDataOperatorBuf,5);
							
						}
						else
						{
							nKeypadOper_ChangCnt++;
							
							nKeypadNum_ChangFlage |= 0x02;
							
							mWifi_TRX_Flag.nDRIVTimeCnt = 15000;
							mWifi_TRX_Flag.nStatusTimeCnt = 60000;
							
							mFlashSaveCnt = 10000;
							
							
							InputDataOperatorNum  = InputDataOperatorNum<<8;
							InputDataOperatorNum |= nKeypad_PushButton;
							
							nKeypad_InputDataOperatorBuf[0] = (InputDataOperatorNum >> 32)+0x30;
							nKeypad_InputDataOperatorBuf[1] = (InputDataOperatorNum >> 24)+0x30;
							nKeypad_InputDataOperatorBuf[2] = (InputDataOperatorNum >> 16)+0x30;
							nKeypad_InputDataOperatorBuf[3] = (InputDataOperatorNum >>8)+0x30;
							nKeypad_InputDataOperatorBuf[4] = (InputDataOperatorNum)+0x30;
							
							memcpy(&mFlashMemoySaveBuf[1],nKeypad_InputDataRouteBuf,3);
							memcpy(&mFlashMemoySaveBuf[4],nKeypad_InputDataOperatorBuf,5);
							
							
						}
					}

                    break;

                }
            }  
            

        }
 
    
    }
   
    
    return i;

}









