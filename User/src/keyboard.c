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
#include "usb_device.h"
keyReportDada keyData = 0;

KeyStatus Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
     /*检测是否有按键按下 */
     if (HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_PRESSED ) {
        /*等待按键释放 */
        HAL_Delay(10);
        if (HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_PRESSED )
        return  KEY_PRESSED; 
     }
     return KEY_RELEASE;
}

void Key_Test(KeyStatus status)
{
   memset(&keyData,0,sizeof(keyReportDada));
   NormalKeyCode_t code = NUM_1;
   if (status == KEY_PRESSED ) 
   {
         for(code = A_CODE ; code <= PAD_NUM_0; code++)
         {
			   if(code == PRINT)
               continue;
            keyData.NormalKey[code / 8] |= 1 << (code % 8);
         }
         USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&keyData, sizeof(keyReportDada));
   }
   else
   {
      USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&keyData, sizeof(keyReportDada));
   }
}