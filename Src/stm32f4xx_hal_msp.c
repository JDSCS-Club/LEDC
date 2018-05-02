/**
  ******************************************************************************
  * @file    TIM/TIM_TimeBase/Src/stm32f4xx_hal_msp.c
  * @author  MCD Application Team
  * @version V1.2.7
  * @date    17-February-2017
  * @brief   HAL MSP module.    
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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
  *
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @defgroup HAL_MSP
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief TIM MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* TIMx Peripheral clock enable */

	if(htim->Instance == TIM3)
	{

//		__HAL_RCC_TIM3_CLK_ENABLE();

//		HAL_NVIC_ClearPendingIRQ(TIM3_IRQn);

//		/*##-2- Configure the NVIC for TIMx ########################################*/
//		/* Set Interrupt Group Priority */ 
//		HAL_NVIC_SetPriority(TIM3_IRQn, 4, 0);

//		/* Enable the TIMx global Interrupt */
//		HAL_NVIC_EnableIRQ(TIM3_IRQn);

//		HAL_TIM_Base_Start_IT(htim);

	}
	else  if(htim->Instance == TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();
		HAL_NVIC_ClearPendingIRQ(TIM4_IRQn);

		/*##-2- Configure the NVIC for TIMx ########################################*/
		/* Set Interrupt Group Priority */ 
		HAL_NVIC_SetPriority(TIM4_IRQn, 4, 0);

		/* Enable the TIMx global Interrupt */
		HAL_NVIC_EnableIRQ(TIM4_IRQn);

		HAL_TIM_Base_Start_IT(htim);

	}
	else  if(htim->Instance == TIM5)
	{
		__HAL_RCC_TIM5_CLK_ENABLE();
		HAL_NVIC_ClearPendingIRQ(TIM5_IRQn);

		/*##-2- Configure the NVIC for TIMx ########################################*/
		/* Set Interrupt Group Priority */ 
		HAL_NVIC_SetPriority(TIM5_IRQn, 4, 0);

		/* Enable the TIMx global Interrupt */
		HAL_NVIC_EnableIRQ(TIM5_IRQn);

		HAL_TIM_Base_Start_IT(htim);

	}
  
  
}



void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* TIMx Peripheral clock enable */

	if(htim->Instance == TIM3)
	{

//		__HAL_RCC_TIM3_CLK_DISABLE();

//		//    HAL_NVIC_ClearPendingIRQ(TIM3_IRQn);
//		//    
//		//      /*##-2- Configure the NVIC for TIMx ########################################*/
//		//      /* Set Interrupt Group Priority */ 
//		//      HAL_NVIC_SetPriority(TIM3_IRQn, 4, 0);

//		/* Enable the TIMx global Interrupt */
//		HAL_NVIC_DisableIRQ(TIM3_IRQn);

//		HAL_TIM_Base_Stop_IT(htim);

	}
	else  if(htim->Instance == TIM4)
	{

		__HAL_RCC_TIM4_CLK_DISABLE();

		//    HAL_NVIC_ClearPendingIRQ(TIM4_IRQn);

		//      /*##-2- Configure the NVIC for TIMx ########################################*/
		//      /* Set Interrupt Group Priority */ 
		//      HAL_NVIC_SetPriority(TIM4_IRQn, 4, 0);
		//      
		//      /* Enable the TIMx global Interrupt */
		HAL_NVIC_DisableIRQ(TIM4_IRQn);

		HAL_TIM_Base_Stop_IT(htim);

	}
	else  if(htim->Instance == TIM5)
	{

		__HAL_RCC_TIM5_CLK_DISABLE();

		//    HAL_NVIC_ClearPendingIRQ(TIM4_IRQn);

		//      /*##-2- Configure the NVIC for TIMx ########################################*/
		//      /* Set Interrupt Group Priority */ 
		//      HAL_NVIC_SetPriority(TIM4_IRQn, 4, 0);
		//      
		//      /* Enable the TIMx global Interrupt */
		HAL_NVIC_DisableIRQ(TIM5_IRQn);

		HAL_TIM_Base_Stop_IT(htim);

	}
  
  
}

/**
  * @brief UART MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param huart: UART handle pointer
  * @retval None
  */
  

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  if(huart->Instance == USART1)
  {

        /*##-1- Enable peripherals and GPIO Clocks #################################*/
        /* Enable GPIO TX/RX clock */
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /* Enable USART1 clock */
        __HAL_RCC_USART1_CLK_ENABLE(); 

        /*##-2- Configure peripheral GPIO ##########################################*/  
        /* UART TX /GPIO pin configuration  */
        GPIO_InitStruct.Pin       = GPIO_PIN_9|GPIO_PIN_10 ;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;

        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* UART RX GPIO pin configuration  */
        //GPIO_InitStruct.Pin = GPIO_PIN_10;

        //HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


        HAL_NVIC_SetPriority(USART1_IRQn, 14, 1);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
    else if(huart->Instance == UART4)
    {
          /*##-1- Enable peripherals and GPIO Clocks #################################*/
        /* Enable GPIO TX/RX clock */
        __HAL_RCC_GPIOC_CLK_ENABLE();

        /* Enable USART1 clock */
        __HAL_RCC_UART4_CLK_ENABLE(); 

        /*##-2- Configure peripheral GPIO ##########################################*/  
        /* UART TX GPIO pin configuration  */
        GPIO_InitStruct.Pin       = GPIO_PIN_10|GPIO_PIN_11;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART4;

        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        /* UART RX GPIO pin configuration  */
        //GPIO_InitStruct.Pin = GPIO_PIN_11;
        //GPIO_InitStruct.Alternate = GPIO_AF7_USART3;

        //HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


        HAL_NVIC_SetPriority(UART4_IRQn, 15, 1);
        HAL_NVIC_EnableIRQ(UART4_IRQn);
    }
     else if(huart->Instance == USART3)
    {
          /*##-1- Enable peripherals and GPIO Clocks #################################*/
        /* Enable GPIO TX/RX clock */
        __HAL_RCC_GPIOD_CLK_ENABLE();

        /* Enable USART1 clock */
        __HAL_RCC_USART3_CLK_ENABLE(); 

        /*##-2- Configure peripheral GPIO ##########################################*/  
        /* UART TX GPIO pin configuration  */
        GPIO_InitStruct.Pin       = GPIO_PIN_8|GPIO_PIN_9;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART3;

        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        /* UART RX GPIO pin configuration  */
        //GPIO_InitStruct.Pin = GPIO_PIN_11;
        //GPIO_InitStruct.Alternate = GPIO_AF7_USART3;

        //HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);


        HAL_NVIC_SetPriority(USART3_IRQn, 15, 1);
        HAL_NVIC_EnableIRQ(USART3_IRQn);
    }
  
}

/**
  * @brief UART MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{

    if(huart->Instance == USART1)
    {
        __HAL_RCC_USART1_CLK_DISABLE();
        /*##-1- Reset peripherals ##################################################*/
        __HAL_RCC_USART1_FORCE_RESET();
        __HAL_RCC_USART1_RELEASE_RESET();

        /*##-2- Disable peripherals and GPIO Clocks #################################*/
        /* Configure UART Tx as alternate function  */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);
        /* Configure UART Rx as alternate function  */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);

        HAL_NVIC_DisableIRQ(USART1_IRQn);
    }
    else if(huart->Instance == UART4)
    {
        __HAL_RCC_UART4_CLK_DISABLE();
         /*##-1- Reset peripherals ##################################################*/
        __HAL_RCC_UART4_FORCE_RESET();
        __HAL_RCC_UART4_RELEASE_RESET();

        /*##-2- Disable peripherals and GPIO Clocks #################################*/
        /* Configure UART Tx as alternate function  */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10);
        /* Configure UART Rx as alternate function  */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_11);

        HAL_NVIC_DisableIRQ(UART4_IRQn);       
        
    }
    else if(huart->Instance == USART3)
    {
        __HAL_RCC_USART3_CLK_DISABLE();
        /*##-1- Reset peripherals ##################################################*/
        __HAL_RCC_USART3_FORCE_RESET();
        __HAL_RCC_USART3_RELEASE_RESET();

        /*##-2- Disable peripherals and GPIO Clocks #################################*/
        /* Configure UART Tx as alternate function  */
        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_9);
        /* Configure UART Rx as alternate function  */
        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_10);

        HAL_NVIC_DisableIRQ(USART3_IRQn);
    }
  
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  if(hspi->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_SPI2_CLK_ENABLE();
  
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA7     ------> SPI1_MOSI
    PB4     ------> SPI1_MISO 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 ;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);


  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
	
	
}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{

  if(hspi->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI2_CLK_DISABLE();
  
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA7     ------> SPI1_MOSI
    PB4     ------> SPI1_MISO 
    */
    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);


  }
  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */

}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef   GPIO_InitStruct;
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* TIMx Peripheral clock enable */
	
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_TIM8_CLK_ENABLE();

  /* Enable all GPIO Channels Clock requested */
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();
  __GPIOC_CLK_ENABLE();


  /* Configure PB.06 (pin 23 in P2 connector) (TIM4_Channel1), PB.07 (pin 24 in P2 connector) (TIM4_Channel2), PB.08 (pin 19 in P2 connector) (TIM4_Channel3),
     PB.09 (pin 20 in P2 connector) (TIM4_Channel4) in output, push-pull, alternate function mode
  */
  /* Common configuration for all channels */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	
	
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  
/*#################################*/  
  GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  
  
  
  
  
  
  
  
  

//  GPIO_InitStruct.Alternate = TIMx_GPIO_AF_CHANNEL4;
//  GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL4;
//  HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL4, &GPIO_InitStruct);
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
