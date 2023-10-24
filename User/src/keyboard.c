 /**
 * @File Name: keyboard.c
 * @brief  
 * @Author : L email:tianlicoder@foxmail.com
 * @Version : 1.0
 * @Creat Date : 2023-10-05
 * 
 * @copyright Copyright (c) 2023 author
 * 
 */
#include "keyboard.h"

#define GET_BIT(value,bit) ((value)&(1<<(bit)))    //读取指定位
#define CPL_BIT(value,bit) ((value)^=(1<<(bit)))   //取反指定位
#define SET0_BIT(value,bit) ((value)&=~(1<<(bit))) //把某个位置0
#define SET1_BIT(value,bit) ((value)|= (1<<(bit))) //把某个位置1

/**
 * @brief rawData
 *   
 * [{a:6},"Esc","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12",{a:5},"PrtSc\nNmLk","Pause\nScrLk","Delete\nInsert"],
 * [{a:4},"~\n`","!\n1","@\n2","#\n3","$\n4","%\n5","^\n6","&\n7","*\n8","(\n9",")\n0","_\n-","+\n=",{a:6,w:2},"Backspace","Home"],
 * [{a:4,w:1.5},"Tab","Q","W","E","R","T","Y","U","I","O","P","{\n[","}\n]",{w:1.5},"|\n\\",{a:6},"Page Up"],
 * [{a:4,w:1.75},"Caps Lock","A","S","D","F","G","H","J","K","L",":\n;","\"\n'",{a:6,w:2.25},"Enter","Page Down"],
 * [{w:2.25},"Shift",{a:4},"Z","X","C","V","B","N","M","<\n,",">\n.","?\n/",{a:6,w:1.75},"Shift",{a:7},"↑",{a:6},"End"],
 * [{w:1.25},"Ctrl",{w:1.25},"Win",{w:1.25},"Alt",{a:7,w:6.25},"",{a:6},"Alt","Fn","Ctrl",{a:7},"←","↓","→"]
 */
const int DEF_KEY_RAW_DATA[CHIP_74HC65_TOTAL][CHIP_74HC65_PIN_TOTAL] = 
{
    {   ESC,            F1,             F2,             F3,             F4,             F5,             F6,                 F7          },
    {   F8,             F9,             F10,            F11,            F12,            PRINT,          SCROLL_LOCK,        DELETE      },
    {   HOME,           BACKSPACE,      EQUAL,          MINUS,          NUM_0,          NUM_9,          NUM_8 ,             NUM_7       },
    {   NUM_6,          NUM_5,          NUM_4,          NUM_3,          NUM_2,          NUM_1,          GRAVE_ACCENT,       TAB         },
    {   CODE_Q,         CODE_W,         CODE_E,         CODE_R,         CODE_T,         CODE_Y,         CODE_U,             CODE_I      },
    {   CODE_O,         CODE_P,         LEFT_U_BRACE,   RIGHT_U_BRACE,  BACKSLASH,      PAGE_UP,        PAGE_DOWN,          ENTER       },
    {   QUOTE,          SEMI_COLON,     CODE_L,         CODE_K,         CODE_J,         CODE_H,         CODE_G,             CODE_F      },
    {   CODE_D,         CODE_S,         CODE_A,         CAP_LOCK,       LEFT_SHIFT,     CODE_Z,         CODE_X,             CODE_C      },
    {   CODE_V,         CODE_B,         CODE_N,         CODE_M,         COMMA,          PERIOD,         SLASH,              RIGHT_SHIFT },
    {   RIGHT_ARROW,    DOWN_ARROW,     LEFT_ARROW,     RIGHT_CTRL,     RIGHT_GUI,      RIGHT_ALT,      SPACE,              LEFT_ALT    },
    {   LEFT_GUI,       LEFT_CTRL,      RESERVED,       RESERVED,       RESERVED,       RESERVED,       RESERVED,           RESERVED    }
};

int scan(keyBoard_t *k,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void test(keyBoard_t *k);
int8_t updataReportData (keyBoard_t *k,uint8_t padNum,uint8_t* padValue);

/**
 * @brief  
 * @param  GPIOx: 
 * @param  GPIO_Pin: 
 * @return KeyStatus: 
 */
int scan(keyBoard_t *k,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
   // HAL_SPI_Receive(&hspi1, key_data, 3, 0x2f);
    return KEY_RELEASE;
}

// void Key_Test(keyBoard_t *k,KeyStatus status)
// {
//    memset(&k->reportData,0,sizeof(keyReportDada));
//    NormalKeyCode_t code = NUM_1;
//    if (status == KEY_PRESSED )
//    {
//       for(code = CODE_A ; code <= PAD_NUM_0; code++)
//       {
//          if(code == PRINT)
//             continue;
//          k->reportData.normalKeyCode[code / 8] |= 1 << (code % 8);
//       }
//       USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&k->reportData, sizeof(keyReportDada));
//    }
//    else
//    {
//       USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&k->reportData, sizeof(keyReportDada));
//    }
// }

/**
 * @brief  
 * @param  status: 
 */
void test(keyBoard_t *k)
{
   uint8_t reportData[CHIP_74HC65_TOTAL] = {0};
   
   memset(reportData,0xff,sizeof(reportData));
   k->updataReportData(k,CHIP_74HC65_TOTAL,reportData);
   k->printReportData(k);
   USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&k->reportData, k->reportDataLen);
   // Key_Test(k,0);

	HAL_Delay(500);


   // Key_Test(k,1);
   memset(reportData,0x00,sizeof(reportData));
   k->updataReportData(k,CHIP_74HC65_TOTAL,reportData);
   k->printReportData(k);
   USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&k->reportData, k->reportDataLen);
}

/**
 * @brief  
 * @param  padNum: 
 * @param  padValue: 
 * @return int8_t: 
 */
int8_t updataReportData (keyBoard_t *k,uint8_t padNum,uint8_t* padValue)
{
   uint8_t *value = padValue;
   memset(&k->reportData,0,sizeof(keyReportDada));
   printf("\r\n%d,%s>>",padNum,padValue);HAL_Delay(100);
    for(int num = 0; num < padNum && num < CHIP_74HC65_TOTAL &&  value != NULL;num++,value++)
    {
        for(int pin = 0;pin < CHIP_74HC65_PIN_TOTAL; pin++)
        {
            if((k->keyRawData[pin][pin]  >= RESERVED) && (VOLUME_DOWN >= k->keyRawData[num][pin]))//NormalKeyCode_t
            {
               printf("%4d",k->keyRawData[num][pin] );
               k->reportData.normalKeyCode[k->keyRawData[num][pin] / 8] |= (GET_BIT(*value,pin) << (k->keyRawData[num][pin] % 8));
            }
            else if((k->keyRawData[num][pin]  >= LEFT_CTRL) && (RIGHT_GUI >= k->keyRawData[num][pin]))//SpecialKeyCode_t
            {
               k->reportData.specialKeyCode |=  (GET_BIT(*value,pin) << ((k->keyRawData[num][pin]  + 8 ) % 8));
            }
        }
    }
   printf("<<\r\n");

    return 0;
}

/**
 * @brief  
 * @param  k: 
 */
void printReportData(keyBoard_t *k)
{
   printf("ReportData:[%02X][%02X]",k->reportData.specialKeyCode,k->reportData.reserved);
   int i = 0;
   for(i = 0; i < 17; i++)
   {
      printf("[%02X]",k->reportData.normalKeyCode[i]);
   }
   printf("\r\n");
}
/**
 * @brief  
 * @param  k: 
 */
void printKeyRawData(keyBoard_t *k)
{
   for(int num = 0;num < CHIP_74HC65_TOTAL;num++)
   {
      for(int pin = 0;pin < CHIP_74HC65_PIN_TOTAL; pin++)
      {
         printf("[%04d]",k->keyRawData[num][pin]);
      }
   }
   printf("\r\n");
}
/**
 * @brief  
 * @param  k: 
 * @return int: 
 */
void keyInit(keyBoard_t *k)
{
    //memset(k,0,sizeof(keyBoard_t));
    k->reportDataLen = sizeof(keyReportDada);
    memcpy(&k->keyRawData,DEF_KEY_RAW_DATA,sizeof(DEF_KEY_RAW_DATA));
    k->test = test;
    k->scan = scan;
    k->updataReportData = updataReportData;
    k->printReportData = printReportData;
    k->printKeyRawData = printKeyRawData;
}
