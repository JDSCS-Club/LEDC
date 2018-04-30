/**
  ******************************************************************************
  * @file SPI/M25P64_FLASH/spi_flash.c 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  This file provides a set of functions needed to manage the
  *         communication between SPI peripheral and SPI M25P64 FLASH.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "spi_flash.h"


/* Private typedef -----------------------------------------------------------*/
#define SPI_FLASH_PageSize    256

/* Private define ------------------------------------------------------------*/
#define WRITE      0x02  /* Write to Memory Page_Program */

#define WRSR       0x01  /* Write Status Register instruction */

#define WREN       0x06  /* Write enable instruction */
#define WRDI       0x04  /* Write disables instruction */



#define READ       0x03  /* Read from Memory Read */
#define HS_READ    0x0B  /* *HighSpeed_Read*/
#define RDSR       0x05  /* Read Status Register instruction  */

#define ULBPR	   0x98  /* Global Block Protection Unlock */


#define RDID       0x9F  /* Read identification */

#define SE         0x20  /* Sector Erase instruction */
#define BE         0xD8  /* Bulk Erase instruction */
#define CE         0xC7  /* Chip_Erase*/

#define WIP_Flag   0x80  /* Write In Progress (WIP) flag */


#define Dummy_Byte 0xFF


SPI_HandleTypeDef SpiMemoryHandle;

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void SPI_FLASH_Init(void)
{
//  SPI_InitTypeDef  SPI_InitStructure;
	

	
	GPIO_InitTypeDef   GPIO_InitStructure;

	__GPIOI_CLK_ENABLE();

	GPIO_InitStructure.Pin = GPIO_PIN_0 |  GPIO_PIN_5 | GPIO_PIN_4;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStructure); 


	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0,GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_5,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_4,GPIO_PIN_SET);



	SpiMemoryHandle.Instance = SPI2;
	SpiMemoryHandle.Init.Mode = SPI_MODE_MASTER;
	SpiMemoryHandle.Init.Direction = SPI_DIRECTION_2LINES;
	SpiMemoryHandle.Init.DataSize = SPI_DATASIZE_8BIT;
	SpiMemoryHandle.Init.CLKPolarity = SPI_POLARITY_LOW;
	SpiMemoryHandle.Init.CLKPhase = SPI_PHASE_1EDGE;
	SpiMemoryHandle.Init.NSS = SPI_NSS_SOFT;
	SpiMemoryHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	SpiMemoryHandle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	SpiMemoryHandle.Init.TIMode = SPI_TIMODE_DISABLE;
	SpiMemoryHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SpiMemoryHandle.Init.CRCPolynomial = 10;

	if (HAL_SPI_Init(&SpiMemoryHandle) != HAL_OK)
	{
		Error_Handler();
	}


	SPI_FLASH_GlobalBlockProtec();
	
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void SPI_FLASH_SectorErase(uint32_t SectorAddr)
{
	
	uint8_t tx_spi_buf[100];
	uint8_t rx_spi_buf[100];


	SPI_FLASH_WriteEnable();

	SPI_FLASH_CS_LOW();

	tx_spi_buf[0] = SE;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	tx_spi_buf[0] = (SectorAddr & 0xFFFFFF) >> 16;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);
	tx_spi_buf[0] = (SectorAddr & 0xFFFF) >> 8;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);
	tx_spi_buf[0] = SectorAddr & 0xFF;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);


	SPI_FLASH_CS_HIGH();

	SPI_FLASH_WaitForWriteEnd();
}


/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void SPI_Chip_Erase(void)
{
	uint8_t tx_spi_buf[100];
	uint8_t rx_spi_buf[100];

	/* Send write enable instruction */
	SPI_FLASH_WriteEnable();

	SPI_FLASH_CS_LOW();

	
	tx_spi_buf[0] = CE;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	SPI_FLASH_CS_HIGH();

	//SPI_FLASH_WriteDisable();

	SPI_FLASH_WaitForWriteEnd();
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void SPI_FLASH_BulkErase(void)
{
//  /* Send write enable instruction */
//  SPI_FLASH_WriteEnable();

//  /* Bulk Erase */
//  /* Select the FLASH: Chip Select low */
//  SPI_FLASH_CS_LOW();
//  /* Send Bulk Erase instruction  */
//  SPI_FLASH_SendByte(BE);
//  /* Deselect the FLASH: Chip Select high */
//  SPI_FLASH_CS_HIGH();

//  /* Wait the end of Flash writing */
//  SPI_FLASH_WaitForWriteEnd();
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint8_t Cnt = 0;
	uint8_t tx_spi_buf[100];
	uint8_t rx_spi_buf[100];

	SPI_FLASH_WriteEnable();

	SPI_FLASH_CS_LOW();


	tx_spi_buf[0] = WRITE;

	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	tx_spi_buf[0] = (WriteAddr & 0xFFFFFF) >> 16;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	tx_spi_buf[0] = (WriteAddr& 0xFFFF) >> 8;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	tx_spi_buf[0] = WriteAddr & 0xFF;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);
	
	

	while (NumByteToWrite--)
	{
		HAL_SPI_TransmitReceive(&SpiMemoryHandle,&pBuffer[Cnt],rx_spi_buf,1,1);

		Cnt++;
	}


	SPI_FLASH_CS_HIGH();

	SPI_FLASH_WaitForWriteEnd();
  
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = WriteAddr % SPI_FLASH_PageSize;
  count = SPI_FLASH_PageSize - Addr;
  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

  if (Addr == 0) /* WriteAddr is SPI_FLASH_PageSize aligned  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else /* WriteAddr is not SPI_FLASH_PageSize aligned  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
      {
        temp = NumOfSingle - count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      if (NumOfSingle != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	uint8_t i;
	uint8_t tx_spi_buf[100];
	uint8_t rx_spi_buf[100];

	SPI_FLASH_WriteEnable();

	SPI_FLASH_CS_LOW();

	tx_spi_buf[0] = HS_READ; // HighSpeed_Read_Cont COMM
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	tx_spi_buf[0] = (ReadAddr & 0xFFFFFF) >> 16;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	tx_spi_buf[0] = (ReadAddr& 0xFFFF) >> 8;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	tx_spi_buf[0] = ReadAddr & 0xFF;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);




	tx_spi_buf[0] = Dummy_Byte;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	for(i = 0;i < NumByteToRead;i++)
	{
		tx_spi_buf[0] = Dummy_Byte;
		HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);
		*pBuffer = rx_spi_buf[0];
		pBuffer++;
	}

	SPI_FLASH_CS_HIGH();
	  
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
uint32_t SPI_FLASH_ReadID(void)
{
	uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

	uint8_t tx_spi_buf[100];
	uint8_t rx_spi_buf[100];


	SPI_FLASH_CS_LOW();

	tx_spi_buf[0] = RDID;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	tx_spi_buf[0] = Dummy_Byte;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);
	Temp0 = rx_spi_buf[0];

	tx_spi_buf[0] = Dummy_Byte;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);
	Temp1 = rx_spi_buf[0];

	
	
	tx_spi_buf[0] = Dummy_Byte;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);
	Temp2 = rx_spi_buf[0];


	SPI_FLASH_CS_HIGH();


	Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

	return Temp;
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr)
{
//  /* Select the FLASH: Chip Select low */
//  SPI_FLASH_CS_LOW();

//  /* Send "Read from Memory " instruction */
//  SPI_FLASH_SendByte(READ);

//  /* Send the 24-bit address of the address to read from -----------------------*/
//  /* Send ReadAddr high nibble address byte */
//  SPI_FLASH_SendByte((ReadAddr & 0xFFFFFF) >> 16);
//  /* Send ReadAddr medium nibble address byte */
//  SPI_FLASH_SendByte((ReadAddr& 0xFFFF) >> 8);
//  /* Send ReadAddr low nibble address byte */
//  SPI_FLASH_SendByte(ReadAddr & 0xFF);
//	
//	SPI_FLASH_CS_HIGH();

}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
uint8_t SPI_FLASH_ReadByte(void)
{
//  return (SPI_FLASH_SendByte(Dummy_Byte));
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
//  /* Loop while DR register in not emplty */
//  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);


//  /* Send byte through the SPI1 peripheral */
//  SPI_I2S_SendData(SPI2, byte);
//	//HAL_SPI_Transmit_IT(&SpiMemoryHandle,&byte,1);

//  /* Wait to receive a byte */
//  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

//  /* Return the byte read from the SPI bus */
//  return SPI_I2S_ReceiveData(SPI2);
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
uint16_t SPI_FLASH_SendHalfWord(uint16_t HalfWord)
{
//  /* Loop while DR register in not emplty */
//  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

//  /* Send Half Word through the SPI1 peripheral */
//  SPI_I2S_SendData(SPI2, HalfWord);

//  /* Wait to receive a Half Word */
//  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

//  /* Return the Half Word read from the SPI bus */
//  return SPI_I2S_ReceiveData(SPI2);
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void SPI_FLASH_WriteEnable(void)
{
	uint8_t tx_spi_buf[100];
	uint8_t rx_spi_buf[100];

	SPI_FLASH_CS_LOW();

	tx_spi_buf[0] = WREN; // 0x06
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	SPI_FLASH_CS_HIGH();
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void SPI_FLASH_WriteDisable(void)
{
	
	uint8_t tx_spi_buf[100];
	uint8_t rx_spi_buf[100];
	/* Select the FLASH: Chip Select low */
	SPI_FLASH_CS_LOW();

	tx_spi_buf[0] = WRDI; // 
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	SPI_FLASH_CS_HIGH();
	
	
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void SPI_FLASH_WaitForWriteEnd(void)
{
	uint8_t FLASH_Status = 0;

	uint8_t tx_spi_buf[100];
	uint8_t rx_spi_buf[100];


	SPI_FLASH_CS_LOW();

	tx_spi_buf[0] = RDSR;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);


	do
	{
		tx_spi_buf[1] = Dummy_Byte;
		HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

		FLASH_Status = rx_spi_buf[0];

	}
	while ((FLASH_Status & WIP_Flag) == 0x80); /* Write in progress */

	SPI_FLASH_CS_HIGH();
	
}


/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void SPI_FLASH_GlobalBlockProtec(void)
{	
	
	uint8_t tx_spi_buf[100];
	uint8_t rx_spi_buf[100];

	SPI_FLASH_CS_LOW();

	tx_spi_buf[0] = ULBPR;
	HAL_SPI_TransmitReceive(&SpiMemoryHandle,tx_spi_buf,rx_spi_buf,1,1);

	SPI_FLASH_CS_HIGH();

}



/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
static void Error_Handler(void)
{
  /* Turn LED5 on */
  while(1)
  {
  }
}



/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
