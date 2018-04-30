#include "LED.h"
#include "Keypad.h"
#include "USRAT.h"


uint16_t LED_FONTDATA[100][16]= { 
//0
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x18,0x3C,0x3C,0x3C,0x3C,0x18,0x18,0x00,0x18,0x18,0x18,0x00,0x00,
0x00,0x00,0x77,0x77,0x77,0x66,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x06,0x37,0x3F,0x7E,0x76,0x37,0x3F,0x7E,0x76,0x30,0x00,0x00,0x00,0x00,
0x00,0x08,0x08,0x3E,0x7F,0x6B,0x69,0x7E,0x3F,0x4B,0x6B,0x7F,0x3E,0x08,0x08,0x00,
//5
0x00,0x00,0x00,0x71,0x73,0x77,0x0E,0x1C,0x38,0x77,0x67,0x47,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x38,0x7C,0x6C,0x7C,0x3B,0x7F,0x6E,0x66,0x7F,0x3B,0x00,0x00,0x00,
0x00,0x00,0x00,0x1C,0x1C,0x1C,0x38,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1C,0x38,0x70,0x70,0x70,0x70,0x70,0x70,0x38,0x1C,0x00,0x00,0x00,
0x00,0x00,0x00,0x38,0x1C,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x1C,0x38,0x00,0x00,0x00,
//10
0x00,0x00,0x00,0x00,0x18,0xDB,0xFF,0x7E,0x18,0x7E,0xFF,0xDB,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x7E,0x7E,0x18,0x18,0x18,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x38,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x38,0x38,0x00,0x00,0x00,
//15
0x00,0x00,0x00,0x01,0x03,0x07,0x0E,0x1C,0x38,0x70,0xE0,0xC0,0x80,0x00,0x00,0x00,
0x7E,0xFF,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xFF,0x7E, //0
0x18,0x38,0xF8,0xF8,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xFF,0xFF, //1
0x7E,0xFF,0xC3,0xC3,0x03,0x03,0x03,0x06,0x0C,0x18,0x30,0x60,0xC0,0xC0,0xFF,0xFF, //2
0x7E,0xFF,0xC3,0xC3,0x03,0x03,0x03,0x3E,0x3E,0x03,0x03,0x03,0xC3,0xC3,0xFF,0x7E, //3
//20
0x06,0x0E,0x1E,0x36,0x66,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xFF,0xFF,0x06,0x06,0x06, //4
0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xFE,0xFF,0x03,0x03,0x03,0xC3,0xC3,0xFF,0x7E, //5
0x7E,0xFF,0xC3,0xC3,0xC0,0xC0,0xC0,0xFE,0xFF,0xC3,0xC3,0xC3,0xC3,0xC3,0xFF,0x7E, //6
0xFF,0xFF,0xC3,0xC3,0x03,0x03,0x06,0x0C,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18, //7
0x7E,0xFF,0xC3,0xC3,0xC3,0xC3,0xC3,0x7E,0x7E,0xC3,0xC3,0xC3,0xC3,0xC3,0xFF,0x7E, //8
//25
0x7E,0xFF,0xC3,0xC3,0xC3,0xC3,0xC3,0xFF,0x7F,0x03,0x03,0x03,0xC3,0xC3,0xFF,0x7E, //9
0x00,0x00,0x00,0x00,0x38,0x38,0x38,0x00,0x00,0x38,0x38,0x38,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x38,0x38,0x38,0x00,0x00,0x38,0x38,0x38,0x70,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0E,0x1C,0x38,0x70,0xE0,0x70,0x38,0x1C,0x0E,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x7F,0x00,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,
//30
0x00,0x00,0x00,0x00,0x70,0x38,0x1C,0x0E,0x07,0x0E,0x1C,0x38,0x70,0x00,0x00,0x00,
0x00,0x00,0x00,0x3E,0x7F,0x63,0x63,0x07,0x0E,0x1C,0x00,0x1C,0x1C,0x00,0x00,0x00,
0x00,0x00,0x3E,0x7F,0x41,0x5D,0x5D,0x55,0x5F,0x5F,0x43,0x7F,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x08,0x1C,0x3E,0x77,0x63,0x63,0x7F,0x7F,0x63,0x63,0x00,0x00,0x00,
0x00,0x00,0x00,0x7E,0x7F,0x63,0x63,0x7E,0x7F,0x63,0x63,0x7F,0x7E,0x00,0x00,0x00,
//35
0x00,0x00,0x00,0x1E,0x3F,0x73,0x60,0x60,0x60,0x60,0x73,0x3F,0x1E,0x00,0x00,0x00,
0x00,0x00,0x00,0x7C,0x7E,0x67,0x63,0x63,0x63,0x63,0x67,0x7E,0x7C,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x7F,0x60,0x60,0x7E,0x7E,0x60,0x60,0x7F,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x7F,0x60,0x60,0x7E,0x7E,0x60,0x60,0x60,0x60,0x00,0x00,0x00,
0x00,0x00,0x00,0x1E,0x3F,0x73,0x60,0x60,0x67,0x67,0x73,0x3F,0x1E,0x00,0x00,0x00,
//40
0x00,0x00,0x00,0x63,0x63,0x63,0x63,0x7F,0x7F,0x63,0x63,0x63,0x63,0x00,0x00,0x00,
0x00,0x00,0x00,0x3C,0x3C,0x18,0x18,0x18,0x18,0x18,0x18,0x3C,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x06,0x66,0x66,0x7E,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x63,0x67,0x6E,0x7C,0x78,0x78,0x7C,0x6E,0x67,0x63,0x00,0x00,0x00,
0x00,0x00,0x00,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7F,0x7F,0x00,0x00,0x00,
//45
0x00,0x00,0x00,0x63,0x77,0x7F,0x7F,0x6B,0x63,0x63,0x63,0x63,0x63,0x00,0x00,0x00,
0x00,0x00,0x00,0x63,0x63,0x73,0x7B,0x7F,0x6F,0x67,0x63,0x63,0x63,0x00,0x00,0x00,
0x00,0x00,0x00,0x1C,0x3E,0x77,0x63,0x63,0x63,0x63,0x77,0x3E,0x1C,0x00,0x00,0x00,
0x00,0x00,0x00,0x7E,0x7F,0x63,0x63,0x7F,0x7E,0x60,0x60,0x60,0x60,0x00,0x00,0x00,
0x00,0x00,0x00,0x3E,0x7F,0x63,0x63,0x63,0x63,0x67,0x7F,0x3E,0x07,0x03,0x00,0x00,
//50
0x00,0x00,0x00,0x7E,0x7F,0x63,0x63,0x7F,0x7E,0x63,0x63,0x63,0x63,0x00,0x00,0x00,
0x00,0x00,0x00,0x3E,0x7F,0x63,0x60,0x7E,0x3F,0x03,0x63,0x7F,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x7E,0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x7F,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x63,0x63,0x63,0x63,0x63,0x63,0x77,0x3E,0x1C,0x08,0x00,0x00,0x00,
//55
0x00,0x00,0x00,0x63,0x63,0x63,0x6B,0x6B,0x6B,0x7F,0x7F,0x36,0x36,0x00,0x00,0x00,
0x00,0x00,0x00,0x41,0x63,0x77,0x3E,0x1C,0x1C,0x3E,0x77,0x63,0x41,0x00,0x00,0x00,
0x00,0x00,0x00,0x81,0xC3,0xE7,0x7E,0x3C,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x7F,0x07,0x0E,0x1C,0x38,0x70,0x60,0x7F,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x3C,0x3C,0x30,0x30,0x30,0x30,0x30,0x30,0x3C,0x3C,0x00,0x00,0x00,
//60
0x00,0x00,0x00,0x80,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x3C,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x3C,0x00,0x00,0x00,
0x00,0x08,0x1C,0x3E,0x77,0x63,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x78,0x3C,0x1E,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//65
0x00,0x00,0x00,0x00,0x00,0x3C,0x3E,0x06,0x3E,0x7E,0x66,0x7E,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x30,0x30,0x30,0x3E,0x3F,0x33,0x33,0x33,0x3F,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3E,0x7F,0x63,0x60,0x60,0x63,0x7F,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x06,0x06,0x06,0x3E,0x7E,0x66,0x66,0x66,0x7E,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3E,0x7F,0x63,0x7F,0x7F,0x60,0x7F,0x3F,0x00,0x00,0x00,
//70
0x00,0x00,0x00,0x1C,0x3E,0x36,0x30,0x7C,0x7C,0x30,0x30,0x30,0x30,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3E,0x7E,0x66,0x66,0x7E,0x3E,0x06,0x66,0x7E,0x3C,0x00,
0x00,0x00,0x00,0x30,0x30,0x30,0x30,0x3E,0x3F,0x33,0x33,0x33,0x33,0x00,0x00,0x00,
0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x06,0x06,0x00,0x00,0x06,0x06,0x06,0x06,0x66,0x66,0x7E,0x3C,0x00,
//75
0x00,0x00,0x00,0x30,0x30,0x30,0x33,0x37,0x3E,0x3C,0x3E,0x37,0x33,0x00,0x00,0x00,
0x00,0x00,0x00,0x38,0x38,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x76,0x7F,0x7F,0x6B,0x6B,0x6B,0x63,0x63,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3E,0x3F,0x33,0x33,0x33,0x33,0x33,0x33,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3E,0x7F,0x63,0x63,0x63,0x63,0x7F,0x3E,0x00,0x00,0x00,
//80
0x00,0x00,0x00,0x00,0x00,0x3E,0x3F,0x33,0x33,0x3F,0x3E,0x30,0x30,0x30,0x30,0x00,
0x00,0x00,0x00,0x00,0x00,0x3E,0x7E,0x66,0x66,0x7E,0x3E,0x06,0x06,0x06,0x06,0x00,
0x00,0x00,0x00,0x00,0x00,0x3E,0x3F,0x33,0x30,0x30,0x30,0x30,0x30,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3F,0x7F,0x60,0x7E,0x3F,0x03,0x7F,0x7E,0x00,0x00,0x00,
0x00,0x00,0x00,0x18,0x18,0x7E,0x7E,0x18,0x18,0x1B,0x1B,0x1F,0x0E,0x00,0x00,0x00,
//85
0x00,0x00,0x00,0x00,0x00,0x63,0x63,0x63,0x63,0x63,0x63,0x7F,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x63,0x63,0x63,0x63,0x77,0x3E,0x1C,0x08,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x63,0x63,0x6B,0x6B,0x6B,0x7F,0x7F,0x36,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x41,0x63,0x77,0x3E,0x1C,0x3E,0x77,0x63,0x41,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x63,0x63,0x73,0x3B,0x1F,0x0E,0x1C,0x38,0x70,0x00,0x00,
//90
0x00,0x00,0x00,0x00,0x00,0x7F,0x7F,0x0E,0x1C,0x38,0x70,0x7F,0x7F,0x00,0x00,0x00,
0x00,0x00,0x0E,0x18,0x18,0x18,0x18,0x70,0x18,0x18,0x18,0x18,0x0E,0x00,0x00,0x00,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
0x00,0x00,0x70,0x18,0x18,0x18,0x18,0x0E,0x18,0x18,0x18,0x18,0x70,0x00,0x00,0x00,
0x00,0x00,0x00,0x70,0xFB,0xDF,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//95
0x18,0x18,0x18,0x3C,0x24,0x66,0x42,0xC3,0x81,0xC3,0x42,0x66,0x24,0x3C,0x18,0x18};




uint32_t mLEDAddCntLine = 0;
uint32_t mLEDAddCnt = 0;

/*****************************************************************************
* @brief -
* @param -
* @retval-
******************************************************************************/
void LED_GPIO_Init(void)
{
	 GPIO_InitTypeDef   GPIO_InitStructure;

	    /* Enable GPIOx clock */
    __GPIOA_CLK_ENABLE();
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Pin = GPIO_PIN_6;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	
	
	__GPIOB_CLK_ENABLE();
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_5 ;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	__GPIOC_CLK_ENABLE();
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Pin =  GPIO_PIN_6|GPIO_PIN_7 | GPIO_PIN_8 ;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	__GPIOF_CLK_ENABLE();
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6|GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 ;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

}

/*****************************************************************************
* @brief -GPIO_PIN_9  =  R0  0x200
*         GPIO_PIN_10 =  G0  0x400
*         GPIO_PIN_11 =  B0  0x800

*         GPIO_PIN_12 =  R1  0x1000
*         GPIO_PIN_13 =  G1  0x2000
*         GPIO_PIN_14 =  B1  0x4000

*         GPIO_PIN_15 =  A0 0x8000
*         GPIO_PIN_4  =  A1 0x10
*         GPIO_PIN_5  =  A2 0x40

*         GPIO_PIN_6 =  CLK 0x20
*         GPIO_PIN_7 =  LAT 0x80
*         GPIO_PIN_8 =  OE  0x100 
       G     B    R
       1     0    1  - 노랑.
       1     1    1  - 화이트.
       
 
* @param -
* @retval-
******************************************************************************/

int aaaaa=0;
int bbbbb=0;

int mPrint1 = 0;
int mPrint2 = 0;
int mPrint3 = 0;
int mPrint4 = 0;
int mPrint5 = 0;
int mPrint6 = 0;

uint32_t InputDataRouteNumReNumBer = 0xFFFF;
uint32_t sLedDataBuf[16];

void LED_init(void)
{
		int sClkCnt = 0;
    int i;

    
    uint32_t A_Data = 0;
    uint32_t B_Data = 0;  
		uint32_t C_Data = 0;
    uint32_t D_Data = 0;  
	
    uint16_t sLine = 0;
    uint16_t ssLine = 0;
	
		uint16_t sLedColor = 0;
	
	
    

	// 18_0119 -> 버그 수정(wifi 수신 데이타는 갱신 하는 부분이 없음)
		if(InputDataRouteNum  != InputDataRouteNumReNumBer)
		{
			InputDataRouteNumReNumBer = InputDataRouteNum;
			
			//------------------------------------------폰트 데이타 구성 부분.
					for(i=0;i<16;i++)
					{
					
							A_Data = LED_FONTDATA[(ConvAsc2Hex(nKeypad_InputDataBuf[0])+16)][i];
							B_Data = LED_FONTDATA[(ConvAsc2Hex(nKeypad_InputDataBuf[1])+16)][i];
							
							C_Data = LED_FONTDATA[(ConvAsc2Hex(nKeypad_InputDataBuf[2])+16)][i];
							//D_Data |= LED_FONTDATA[(nKeypad_InputDataBuf[3]+16)][i];
							
							D_Data = A_Data << 24;
							D_Data |= B_Data << 12;
							D_Data |= C_Data;
						
							sLedDataBuf[i]  = D_Data;
							//sLedDataBuf[i]  |= B_Data;

					}
		}

	//------------------------------------------어드레스 설정 부분.
			mLEDAddCnt++;
			
			
			ssLine = ((mLEDAddCnt)%8);
			sLine = ((mLEDAddCnt+7)%8);
			
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, ((sLine & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET)); //A0
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, ((sLine & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET));  //A1
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, ((sLine & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET));  //A2      
			
	//------------------------------------------데이타 전송 부분
	
			HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_SET); // OE - High
			
			HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,GPIO_PIN_SET); // LAT - High
			HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,GPIO_PIN_RESET); // LAT - Low
			
			
			HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_RESET); // OE - Low
			
			sLedColor = (mLEDAddCnt/8)%(3 + nLED_Light_Step*4);
		
		if(!sLedColor)
		{
			mPrint1++;
			
			for(sClkCnt = 0;sClkCnt<32;sClkCnt++) // Blue 설정.
			{
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET); // CLK Low
		 
			   //노랑
			   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET));  // G0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // B0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET));      // G0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // B0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET));    // R0 High
				
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_SET); // CLK High
	 
				
			}
		}
		else if(sLedColor==1)
		{
			mPrint2++;

			for(sClkCnt = 0;sClkCnt<32;sClkCnt++)// RED 설정.
			{
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET); // CLK Low
		 
			   //노랑
			   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // G0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // B0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));      // G0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // B0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_SET); // CLK High
	 
			}
		}
		else if(sLedColor==2)
		{
			mPrint3++;
			for(sClkCnt = 0;sClkCnt<32;sClkCnt++) //RED 설정.
			{
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET); // CLK Low
		 
			   //노랑
			   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // G0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // B0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));      // G0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // B0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_SET); // CLK High
	 
			}
			
		}
		else if(sLedColor==3)
		{
			mPrint4++;
			for(sClkCnt = 0;sClkCnt<32;sClkCnt++) // 공백 
			{
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET); // CLK Low
		 
			   //노랑
			   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6, (((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // G0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // B0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));      // G0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // B0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_SET); // CLK High
	 
			}
			
		}
		else if(sLedColor==4)
		{
			mPrint5++;
			for(sClkCnt = 0;sClkCnt<32;sClkCnt++) // 공백
			{
			   

			    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET); // CLK Low
		 
			   //노랑
			   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6, (((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // G0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // B0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));      // G0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // B0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_SET); // CLK High
	 
			}
			
		}
		else if(sLedColor==5)
		{
			mPrint6++;
			for(sClkCnt = 0;sClkCnt<32;sClkCnt++) // 공백
			{
			   

			    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET); // CLK Low
		 
			   //노랑
			   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6, (((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // G0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // B0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));      // G0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // B0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_SET); // CLK High
	 
			}
			
		}
		else if(sLedColor==6)
		{
			for(sClkCnt = 0;sClkCnt<32;sClkCnt++) // 공백
			{
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET); // CLK Low
		 
			   //노랑
			   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6, (((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // G0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // B0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));      // G0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // B0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_SET); // CLK High
	 
			}
			
		}
		else if(sLedColor==7)
		{
			for(sClkCnt = 0;sClkCnt<32;sClkCnt++) // 공백
			{
			   

			     HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET); // CLK Low
		 
			   //노랑
			   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6, (((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // G0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));  // B0 High
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,(((sLedDataBuf[ssLine]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));      // G0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // B0 High
			   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,(((sLedDataBuf[ssLine+8]>>(31-sClkCnt)) & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_RESET));    // R0 High
			   

			   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_SET); // CLK High
	 
			}
			
		}

        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET); // CLK Low
        
  

}