#include "Flash.h"
#include "USRAT.h"
#include "Keypad.h"


uint32_t FirstSector = 0, NbOfSectors = 0; 
uint32_t FlashAddressPosion = 0;
uint32_t SectorError = 0;

__IO uint8_t data8 = 0;

uint32_t mFLASH_TIM_Cnt = 0;

static FLASH_EraseInitTypeDef EraseInitStruct;



uint8_t mFlashMemoyBuf[15];


uint8_t mFlashMemoySaveBuf[10]="@@@@@@@@@@"; // 기록 시작 코드를 변경 # -> @ 18_0125
uint16_t mFlashSaveCnt = 0;
uint8_t mFlashFlag = 0; //메모리 읽기를 하였는지 확인 하는 부분.


/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void Flash_init(void)
{
	
	HAL_FLASH_Unlock();
	
	//HAL_FLASH_Lock();

	/* Get the 1st sector to erase */
	FirstSector = GetSector(FLASH_USER_START_ADDR);
	/* Get the number of sector to erase from 1st sector*/
	NbOfSectors = GetSector(FLASH_USER_END_ADDR) - FirstSector + 1;

	/* Fill EraseInit structure*/
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.Sector = FirstSector;
	EraseInitStruct.NbSectors = NbOfSectors;
	

	Flash_Read(&mFlashMemoyBuf[0]);
	
	
	
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void Flash_Main(void)
{
	if(mFlashSaveCnt == 1)
	{
		mFlashSaveCnt = 0;
		
		mFlashMemoySaveBuf[0] = '@'; //기록 시작을 표시하는 부분. 18_0125
		mFlashMemoySaveBuf[9] = nLED_Light_Step; //모든 기록에 화면 밝기를 기본으로 추가 한다. 18_0125
		
		Flash_Write(mFlashMemoySaveBuf,10);
		
	}
	
}



/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void Flash_TIM(void)
{
	mFLASH_TIM_Cnt++;
	
	if(mFlashSaveCnt) {mFlashSaveCnt--;}
	
	
}

/*****************************************************************************
* @brief -Flash_Write
* @param -None
* @retval-The sector of a given address
******************************************************************************/
void Flash_Write(uint8_t *pData,uint8_t Len)
{
	int i;

	__HAL_FLASH_DATA_CACHE_DISABLE();
	__HAL_FLASH_INSTRUCTION_CACHE_DISABLE();

	__HAL_FLASH_DATA_CACHE_RESET();
	__HAL_FLASH_INSTRUCTION_CACHE_RESET();

	__HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
	__HAL_FLASH_DATA_CACHE_ENABLE();
	
	
	//printf("%d - Flash Write-ST : %X  \n\r",mFLASH_TIM_Cnt,FlashAddressPosion);
	
	for(i = 0; i < Len ;i++)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, FlashAddressPosion, (uint64_t )pData[i]) == HAL_OK)
		{
			FlashAddressPosion = FlashAddressPosion + 1; //어드레스를 증가한다.
			
	
		}
		else
		{
			  Flash_Error_Handler();
		}
	}
	
	MyPrintf(&pData[0],10,"Flash Write ADD : %X ",FlashAddressPosion);
	
	//printf("%d - Flash Write-END : %X  \n\r",mFLASH_TIM_Cnt,FlashAddressPosion);
	
	// 쓰기 동작후 메모리 
	if((FlashAddressPosion+100) >= FLASH_USER_END_ADDR)
	{
		Flash_Errase();
	}
		
}


/*****************************************************************************
* @brief -Flash_Errase
* @param -None
* @retval-The sector of a given address
******************************************************************************/
void Flash_Errase(void)
{
	 if(HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK)
	  { 
		/* 
		  Error occurred while sector erase. 
		  User can add here some code to deal with this error. 
		  SectorError will contain the faulty sector and then to know the code error on this sector,
		  user can call function 'HAL_FLASH_GetError()'
		*/
		/*
		  FLASH_ErrorTypeDef errorcode = HAL_FLASH_GetError();
		*/
		Flash_Error_Handler();
	  }

}

/*****************************************************************************
* @brief -Flash_Read
* @param -None
* @retval-The sector of a given address
******************************************************************************/
void Flash_Read(uint8_t *pData)
{
	int i;
	FlashAddressPosion = FLASH_USER_START_ADDR;
	
	 data8 = *(__IO uint32_t*)FlashAddressPosion;
	
	pData[0] = data8;
	
	if(data8 == 0xFF){Flash_Errase(); }
	
	else
	{
		
		
		while(pData[0] == '@') //18_0125
		{
			for(i=0;i < 10;i++)
			{
				mFlashFlag = 1;
				
				data8 = *(__IO uint32_t*)FlashAddressPosion;
				
				if(data8 == 0xFF)
				{ 
					pData[0] = 0xFF;
					break;  
				}
				
				pData[i] =(uint8_t) data8;
				
				FlashAddressPosion = FlashAddressPosion + 1;
				
				
			}
			
			
			
			
		}
		
		//MyPrintf(&pData[0],10);
		
		
		//MyPrintf_USART1("%d - Flash Read2 : %X - Address : %X - mFlashflag  \n\r",mFLASH_TIM_Cnt,FlashAddressPosion,mFlashFlag);

		
		FlashAddressPosion = FlashAddressPosion + 9;
	
		data8 = *(__IO uint32_t*)FlashAddressPosion;
		
		pData[0] = data8;
		
		while(pData[0] == '@') //18_0125
		{
			for(i=0;i < 10;i++)
			{
				mFlashFlag = 1;
				
				data8 = *(__IO uint32_t*)FlashAddressPosion;
				
				if(data8 == 0xFF)
				{ 
					pData[0] = 0xFF;
					break;  
				}
				
				pData[i] =(uint8_t) data8;
				
				FlashAddressPosion = FlashAddressPosion + 1;
				
				
			}
			
			
			
		}
		
		
		
		//MyPrintf_USART1("%d - Flash Read2 : %X - Address : %X - mFlashflag  \n\r",mFLASH_TIM_Cnt,FlashAddressPosion,mFlashFlag);

		
		
		if(!mFlashFlag) // 읽기 조건이 맞지 않으면 메모리 삭제 한다. 18_0125
		{
			Flash_Errase();
		}
			
		
	}

	
}
/*****************************************************************************
* @brief -Gets the sector of a given address
* @param -None
* @retval-The sector of a given address
******************************************************************************/
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_SECTOR_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_SECTOR_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_SECTOR_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_SECTOR_10;  
  }
  else /* (Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11) */
  {
    sector = FLASH_SECTOR_11;
  }

  return sector;
}


/*****************************************************************************
* @brief - Gets sector Size
* @param - None
* @retval- The size of a given sector
******************************************************************************/
static uint32_t GetSectorSize(uint32_t Sector)
{
  uint32_t sectorsize = 0x00;

  if((Sector == FLASH_SECTOR_0) || (Sector == FLASH_SECTOR_1) || (Sector == FLASH_SECTOR_2) || (Sector == FLASH_SECTOR_3))
  {
    sectorsize = 16 * 1024;
  }
  else if(Sector == FLASH_SECTOR_4)
  {
    sectorsize = 64 * 1024;
  }
  else
  {
    sectorsize = 128 * 1024;
  }  
  return sectorsize;
}


static void Flash_Error_Handler(void)
{
  /* Turn LED5 on */
  while(1)
  {
  }
}


