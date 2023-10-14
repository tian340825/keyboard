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
