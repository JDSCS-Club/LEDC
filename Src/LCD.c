#include "LCD.h"




/*****************************************************************************
* @brief -  PB - GPIO_PIN_5     LCD-RS
*           PB - GPIO_PIN_6     LCD-RW
*           PB - GPIO_PIN_7     LCD-E
*           PE - GPIO_PIN_0     LCD-D0
*           PE - GPIO_PIN_1     LCD-D1 
*           PE - GPIO_PIN_2     LCD-D2 
*           PE - GPIO_PIN_3     LCD-D3 
*           PE - GPIO_PIN_4     LCD-D4 
*           PE - GPIO_PIN_5     LCD-D5 
*           PE - GPIO_PIN_6     LCD-D6
*           PE - GPIO_PIN_11    LCD-D7
* @param -
* @retval-
******************************************************************************/
void TextLCD_GPIO_Init(void)
{

    GPIO_InitTypeDef   GPIO_InitStructure;


    /* Enable GPIOx clock */
//    __GPIOB_CLK_ENABLE();
    __GPIOE_CLK_ENABLE();


//    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStructure.Pull = GPIO_PULLUP;
//    GPIO_InitStructure.Pin = 
//    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    HAL_GPIO_Init(GPIOE, &GPIO_InitStructure); 


    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2|GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5|GPIO_PIN_6 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 ;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStructure); 

}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void lcd_init(void)
{

    /*****************************************/
//    	instruction_out(0x08); // 디스플레이 끄기
//    	HAL_Delay(2);
//    	instruction_out(0x38); // 8비트, 글꼴
//    	HAL_Delay(2);
//        instruction_out(0x38); // 8비트, 글꼴
//    	HAL_Delay(2);
//        
//    	instruction_out(0x06); // 엔트리 모드가 증가 및 변경되지 않음.
//        HAL_Delay(2);
//    	instruction_out(0x17); // 문자 모드를 설정하고 전원을 켭
//    	instruction_out(0x01); // 디스플레이 지우기
//    	//instruction_out(0x0C); // 디스플레이 켜기
//        instruction_out(0x0F); // 디스플레이 켜기

    /********************************************/
	instruction_out(0x08); // 디스플레이 끄기
	
	
    //HAL_Delay(2);
    instruction_out(0x38); // 8비트, 글꼴 Function Set
    //HAL_Delay(2);
    instruction_out(0x38); // 8비트, 글꼴 Function Set
    //HAL_Delay(2);
    //instruction_out(0x13); // 문자 모드를 설정하고 디스플레이 전원을 OFF
	
	instruction_out(0x06); // 엔트리 모두
	
    //HAL_Delay(2);
    instruction_out(0x17); // 문자 모드를 설정하고 디스플레이 전원을 켭
    //HAL_Delay(2);
	instruction_out(0x01); // 디스플레이 지우기
    instruction_out(0x0F); // 디스플레이 켜기
  
    //HAL_Delay(2);
//    instruction_out(0x02); //Retun home
    //HAL_Delay(2);
//    instruction_out(0x06); // 엔트리 모두
    //HAL_Delay(2);
	
	//instruction_out(0x01); // 디스플레이 지우기
	//instruction_out(0x06); // 엔트리 모두
	

}



/*****************************************************************************
* @brief -  PB - GPIO_PIN_5     LCD-RS
*           PB - GPIO_PIN_6     LCD-RW
*           PB - GPIO_PIN_7     LCD-EN
*           PE - GPIO_PIN_0     LCD-D0
*           PE - GPIO_PIN_1     LCD-D1 
*           PE - GPIO_PIN_2     LCD-D2 
*           PE - GPIO_PIN_3     LCD-D3 
*           PE - GPIO_PIN_4     LCD-D4 
*           PE - GPIO_PIN_5     LCD-D5 
*           PE - GPIO_PIN_6     LCD-D6
*           PE - GPIO_PIN_11    LCD-D7
*
* @param -
* @retval-
******************************************************************************/
void instruction_out(unsigned char b)
{
	uint32_t i = 0;
	
	 //LCD 응답 시간 지연 및 초기화 하기 위해 추가 반드시 필요.
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET); // D0
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET); // D1
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET); // D2
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // D3
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET); // D4
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET); // D5
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET); // D6
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET); // D7 

    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET); //RS Low
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET); //RS Low
	
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET); //RW Low
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET); //RW Low
    
    
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);//EN High
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);//EN High
    
    
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, ((b & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D0
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, ((b & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D1
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, ((b & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D2
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, ((b & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D3
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, ((b & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D4
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, ((b & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D5
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, ((b & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D6
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, ((b & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D7
    
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET); //RS Low
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET); //RS Low
	
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET); //RW Low
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET); //RW Low

    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET); //EN Low  
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET); //EN Low 

    //LCD 응답 시간 지연 및 초기화 하기 위해 추가 반드시 필요.
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET); // D0
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET); // D1
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET); // D2
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // D3
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET); // D4
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET); // D5
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET); // D6
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET); // D7    
    
    //HAL_Delay(1);
	
	for(i = 0;i<50;i++){};

}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/


void display_out(unsigned char b)
{
	uint32_t i = 0;
    //LCD 응답 시간 지연 및 초기화 하기 위해 추가 반드시 필요.
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET); // D0
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET); // D1
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET); // D2
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // D3
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET); // D4
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET); // D5
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET); // D6
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET); // D7   
	
     // 값 설정.
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET); //RS High
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET); //RS High
	
	
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET); //RW Low
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET); //RW Low


    
    
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET); //EN High
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET); //EN High
    

    
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, ((b & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D0
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, ((b & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D1
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, ((b & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D2
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, ((b & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D3
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, ((b & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D4
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, ((b & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D5
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, ((b & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D6
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,((b & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET)); // D7
    

        
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET); //RS High
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET); //RS High
	
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET); //RW Low
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET); //RW Low

    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET); //EN Low 
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET); //EN Low 
    
	 //LCD 응답 시간 지연 및 초기화 하기 위해 추가 반드시 필요.
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET); // D0
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET); // D1
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET); // D2
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // D3
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET); // D4
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET); // D5
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET); // D6
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET); // D7    
    
    //HAL_Delay(1);
	for(i = 0;i<50;i++){};
	
    

}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void lcd_busuFlag(unsigned char b)
{

	GPIOB->ODR = GPIOE->ODR | 0x40; //PB6 - RW를 High
	GPIOB->ODR = GPIOE->ODR & ~0x80; //PB7 - EN를 Low
	
	GPIOB->ODR = GPIOE->ODR | 0x04; //PB7 - EN를 High

  	//상위 4비트


	GPIOB->ODR = GPIOE->ODR & ~0x80; //PB7 - EN를 Low
  

	GPIOB->ODR = GPIOE->ODR | 0x40; //PB6 - RW를 High



}

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void lcd_gotoxy( char x,  char y)
{

    switch(y)
    {    
        case 0 : instruction_out(0x80+x); break;
        case 1 : instruction_out(0xC0+x); break;
        case 2 : instruction_out(0x94+x); break;
        case 3 : instruction_out(0xD4+x); break;
    }
}
/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void lcd_putstr( char x,  char y,  char *str)
{
    unsigned int i=0;
    
    lcd_gotoxy(x,y);
	
    do
    {
        display_out(str[i]&0xFF);
    }
    while(str[++i]!='\0');
	
}



















