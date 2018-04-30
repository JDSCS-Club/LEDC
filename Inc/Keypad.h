#include "stm32f4xx_hal.h"

#define KEY_BUTTON_PIN                GPIO_PIN_0



extern uint8_t nKeypad_InputDataBuf[5];

extern uint16_t nLineSelectFlg;

extern uint8_t nKeypad_InputDataRouteBuf[3];
extern uint8_t nKeypad_InputDataOperatorBuf[5];


extern uint8_t nWifi_InputDataRouteBuf[3];
extern uint8_t nWifi_InputDataOperatorBuf[5];

extern uint8_t nKeypadNum_ChangFlage;
extern uint8_t nKeypadNum_ChangCnt;

extern uint32_t InputDataRouteNum;

extern uint8_t nLED_Light_Step;


void Keypad_GPIO_Init(void);
void Keypad_ScanDo(void);
void KeyPad_ScanInput(void);
int KeyPad_RetunData(int Input,int Cnt);
