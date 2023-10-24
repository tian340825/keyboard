/**
 * @File Name: keyboard.h
 * @brief  
 * @Author : L email:tianlicoder@foxmail.com
 * @Version : 1.0
 * @Creat Date : 2023-10-05
 * 
 * @copyright Copyright (c) 2023 author
 * 
 */
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <string.h>
#include "stdio.h"
#include "usb_device.h"
#include "usbd_customhid.h"
#include "main.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

#define CHIP_74HC65_TOTAL           11
#define CHIP_74HC65_PIN_TOTAL       8

typedef enum
{
    KEY_PRESSED = 0,
    KEY_RELEASE
}KeyStatus;

typedef enum SpecialKeyCode_t
{
    LEFT_CTRL = -8,LEFT_SHIFT ,LEFT_ALT,LEFT_GUI,RIGHT_CTRL,RIGHT_SHIFT,RIGHT_ALT,RIGHT_GUI
}SpecialKeyCode_t;

/**
 * @brief  HID report data
 */
typedef enum NormalKeyCode_t
{
    RESERVED = 0,ERROR_ROLL_OVER,POST_FAIL,ERROR_UNDEFINED,
    CODE_A,CODE_B,CODE_C,CODE_D,CODE_E,CODE_F,CODE_G,CODE_H,CODE_I,CODE_J,CODE_K,CODE_L,CODE_M,
    CODE_N,CODE_O,CODE_P,CODE_Q,CODE_R,CODE_S,CODE_T,CODE_U,CODE_V,CODE_W,CODE_X,CODE_Y,CODE_Z,
    NUM_1/*1!*/,NUM_2/*2@*/,NUM_3/*3#*/,NUM_4/*4$*/,NUM_5/*5%*/,
    NUM_6/*6^*/,NUM_7/*7&*/,NUM_8/*8**/,NUM_9/*9(*/,NUM_0/*0)*/,
    ENTER,ESC,BACKSPACE,TAB,SPACE,
    MINUS/*-_*/,EQUAL/*=+*/,LEFT_U_BRACE/*[{*/,RIGHT_U_BRACE/*]}*/,
    BACKSLASH/*\|*/,NONE_US/**/,SEMI_COLON/*;:*/,QUOTE/*'"*/,
    GRAVE_ACCENT/*`~*/,COMMA/*,<*/,PERIOD/*.>*/,SLASH/*/?*/,
    CAP_LOCK,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,
    PRINT,SCROLL_LOCK,PAUSE,INSERT,HOME,PAGE_UP,DELETE,END,PAGE_DOWN,
    RIGHT_ARROW,LEFT_ARROW,DOWN_ARROW,UP_ARROW,PAD_NUM_LOCK,
    PAD_SLASH,PAD_ASTERISK,PAD_MINUS,PAD_PLUS,PAD_ENTER,
    PAD_NUM_1,PAD_NUM_2,PAD_NUM_3,PAD_NUM_4,PAD_NUM_5,
    PAD_NUM_6,PAD_NUM_7,PAD_NUM_8,PAD_NUM_9,PAD_NUM_0,
    PAD_PERIOD , NONUS_BACKSLASH,APPLICATION,POWER,PAD_EQUAL,
    F13,F14,F15,F16,F17,F18,F19,F20,F21,F22,F23,F24, EXECUTE,
    HELP,MENU,SELECT,STOP,AGAIN,UNDO,CUT,COPY,PASTE,FIND,MUTE,VOLUME_UP,VOLUME_DOWN,
    FN = 1000
}NormalKeyCode_t;


/**
 * @brief  
 */
typedef struct keyReportDada
{
    uint8_t  specialKeyCode;
    uint8_t  reserved;
    uint8_t  normalKeyCode[17];
}keyReportDada;

typedef struct keyBoard_t
{
    keyReportDada reportData;
    int reportDataLen;
    uint8_t keyPad[CHIP_74HC65_TOTAL];
    uint8_t reportFlg;
    int  keyRawData[CHIP_74HC65_TOTAL][CHIP_74HC65_PIN_TOTAL];

    int8_t (*updataReportData) (struct keyBoard_t *,uint8_t ,uint8_t* );
    int (*scan) (struct keyBoard_t *,GPIO_TypeDef* ,uint16_t );
	void (*test) (struct keyBoard_t *);
    void (*printReportData) (struct keyBoard_t *);
    void (*printKeyRawData) (struct keyBoard_t *);
}keyBoard_t;

void keyInit(keyBoard_t *k);

#ifdef __cplusplus
}
#endif

#endif //__KEYBOARD_H__
