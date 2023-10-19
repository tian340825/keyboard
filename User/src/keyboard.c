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

uint8_t send_buf[65] = {0}; 


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
     memset(send_buf,0,sizeof(send_buf));
     send_buf[0] = 0x06;
     NormalKeyCode_t code = NUM_1;
     if (status == KEY_PRESSED ) 
     {
        /*等待按键释放 */
        for(code = NUM_1 ; code <= NUM_0 ;code++)
        {
            send_buf[code] = code;
        }
        for(code = A_CODE ; code <= Z_CODE ;code++)
        {
            send_buf[code] = code;
        }
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, send_buf, sizeof(send_buf));

     }
     else if (status == KEY_RELEASE)
     {
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, send_buf, sizeof(send_buf));
     }
}