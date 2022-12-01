/*
 * ������� ������� ������ � ��������
 * �������������(��� ��� ���������) ,  �������������
 * �������� ������ � ������.
 *
 * */
#ifndef __St7789V_H
#define __St7789V_H

#include "stdint.h"
#include "stm32l1xx_ll_gpio.h"


//������� ������� �������
#define LCD_WIDTH_OFFSET        0
#define LCD_HEIGHT_OFFSET       0
#define LCD_WIDTH               240
#define LCD_HEIGHT              320


//GPIO
#define LCD_BL_EN_PORT      GPIOC
#define LCD_BL_EN_PIN       LL_GPIO_PIN_9
#define LCD_RST_PORT        GPIOC
#define LCD_RST_PIN         LL_GPIO_PIN_14
//#define LCD_CS_PORT         GPIOC
//#define LCD_CS_PIN          LL_GPIO_PIN_13
#define LCD_DC_PORT         GPIOC
#define LCD_DC_PIN          LL_GPIO_PIN_10
#define LCD_WR_PORT         GPIOC
#define LCD_WR_PIN          LL_GPIO_PIN_11
#define LCD_RD_PORT         GPIOC
#define LCD_RD_PIN          LL_GPIO_PIN_15

#define LCD_D0_PORT         GPIOC
#define LCD_D0_PIN          GPIO_Pin_0
#define LCD_D1_PORT         GPIOC
#define LCD_D1_PIN          GPIO_Pin_1
#define LCD_D2_PORT         GPIOC
#define LCD_D2_PIN          GPIO_Pin_2
#define LCD_D3_PORT         GPIOC
#define LCD_D3_PIN          GPIO_Pin_3
#define LCD_D4_PORT         GPIOC
#define LCD_D4_PIN          GPIO_Pin_4
#define LCD_D5_PORT         GPIOC
#define LCD_D5_PIN          GPIO_Pin_5
#define LCD_D6_PORT         GPIOC
#define LCD_D6_PIN          GPIO_Pin_6
#define LCD_D7_PORT         GPIOC
#define LCD_D7_PIN          GPIO_Pin_7


//�������������� ������� ��� 8��� ����
#define BSRR_WR_RESET 		(LCD_WR_PIN<<16)// WR_PIN << 16 for reset
#define BSRR_WR_SET 		(LCD_WR_PIN)	// WR_PIN
#define BSRR_DATA_RESET 	(0xff0000) 		// � reset ����� LCD_D0_PIN - LCD_D7_PIN


#define BSRR_PREPARE_DATA 	(BSRR_WR_RESET | BSRR_DATA_RESET) //������� �������� ��� ������� 8�16 ���

/* St7789V_CMD Display register adresses */
typedef enum {
    St7789V_NULLCMD                     = 0x00,
    St7789V_SW_RESET                    = 0x01,
    St7789V_SLEEP_OUT                   = 0x11,
    St7789V_PARTIAL_MODE_ON             = 0x12,
    St7789V_PARTIAL_MODE_OFF            = 0x13,
    St7789V_SET_GAMMA                   = 0x26,
    St7789V_DISPLAY_OFF                 = 0x28,
    St7789V_DISPLAY_ON                  = 0x29,
    St7789V_COLUMN_ADDRESS              = 0x2A,
    St7789V_PAGE_ADDRESS                = 0x2B,
    St7789V_GRAM                        = 0x2C,
    St7789V_PARTIAL_MODE_ADDRESSES      = 0x30,
    St7789V_MEMORY_ACCESS_CONTROL       = 0x36,
    St7789V_SET_PIXEL_FORMAT            = 0x3A,
    St7789V_WRITE_BRIGHTNESS            = 0x51,
    St7789V_WRITE_CTRL                  = 0x53,
    St7789V_RGB_INTERFACE               = 0xB0,
    St7789V_FRAME_CONTROL               = 0xB1,
    St7789V_PARTIAL_MODE_CONTROL        = 0xB5,
    St7789V_FUNCTION_CONTROL            = 0xB6,
    St7789V_ENTRY_MODE_SET              = 0xB7,
    St7789V_POWER_CONTROL_1             = 0xC0,
    St7789V_POWER_CONTROL_2             = 0xC1,
    St7789V_VCOM_CONTROL_1              = 0xC5,
    St7789V_FRAME_RATE_CONTROL2         = 0xC6,
    St7789V_VCOM_CONTROL_2              = 0xC7,
    St7789V_POWER_CONTROL_A             = 0xCB,
    St7789V_POWER_CONTROL_B             = 0xCF,
    St7789V_POS_GAMMA_CORRECTION        = 0xE0,
    St7789V_NEG_GAMMA_CORRECTION        = 0xE1,
    St7789V_TIMING_CONTROL_A            = 0xE8,
    St7789V_TIMING_CONTROL_B            = 0xE9,
    St7789V_TIMING_CONTROL_C            = 0xEA,
    St7789V_POWER_ON_SEQUENCE           = 0xED,
    St7789V_GAMMA3_EN                   = 0xF2,
    St7789V_INTERFACE_CONTROL           = 0xF6,
    St7789V_PUMP_RATIO_CONTROL          = 0xF7
} St7789V_CMD;



/* name: St7789_init
 * arg:
 * ret:
 * comment: ������������ �������� �������
*/
void St7789_init();

/* name: St7789_deinit
 * arg:
 * ret:
 * comment: �������������� �������� �������
*/
void St7789_deinit();


/* name: St7789_clear
 * arg:
 * ret:
 * comment: ������� ������(������� ������� ������ ������)
 * ������� ���������� ���� ��������� ���
*/
void St7789_clear();


/* name: St7789_wrCmd
 * arg: cmd -������������� �������(1 ����)
 * ret:
 * comment: �������� ������� � �������
*/
static inline void St7789_wrCmd(uint8_t cmd)
{
    //LCD_D_PORT->ODR = cmd;
    //LCD_DC_LOW;
    //LCD_WR_LOW;
    //LCD_WR_HIGH;
	LCD_D0_PORT->BSRR = BSRR_DATA_RESET | cmd;
	LCD_DC_PORT->BRR = LCD_DC_PIN;
	LCD_WR_PORT->BRR = LCD_WR_PIN;
	LCD_WR_PORT->BSRR = LCD_WR_PIN;
}

/* name: St7789_wrData
 * arg: data -������������� ������(1����)
 * ret:
 * comment: �������� ������ � �������
*/
static inline void St7789_wrData(uint8_t data)
{
	LCD_D0_PORT->BSRR = BSRR_DATA_RESET | data;
    LCD_DC_PORT->BSRR = LCD_DC_PIN;
    LCD_WR_PORT->BRR = LCD_WR_PIN;
    LCD_WR_PORT->BSRR = LCD_WR_PIN;
}

/* name: St7789_setArea
 * arg: x1, y1 - ��������� ����������
 * 		x2, y2 - �������� ����������
 * ret:
 * comment: ��������� ������� ��� ������� ������
*/
//==========================================================================================
static inline void St7789_setArea(uint16_t x1,  uint16_t x2,  uint16_t y1,  uint16_t y2)
{

	St7789_wrCmd(St7789V_COLUMN_ADDRESS);    // CASETP

    St7789_wrData((x1>>8)&0xFF);
    St7789_wrData(x1&0xFF);
    St7789_wrData((x2>>8)&0xFF);
    St7789_wrData(x2&0xFF);

    St7789_wrCmd(St7789V_PAGE_ADDRESS);    // RASETP
    St7789_wrData((y1>>8)&0xFF);
    St7789_wrData(0xFF&y1);
    St7789_wrData((y2>>8)&0xFF);
    St7789_wrData(0xFF&y2);

    St7789_wrCmd(St7789V_GRAM); //RAMWR

}

/* name: St7789_startData
 * arg:
 * ret:
 * comment: ���������� ������� � ������ ������
*/

static inline void St7789_startData()
{
	LCD_DC_PORT->BSRR = LCD_DC_PIN;//Data start now
}





/*
 * �.�. ���������� ��� ����������� ����������� 8��� ��������,  � ������� ���� ������ 16���
 * �� ����� ����������� �� 8 � 16 ���.
 * ������� ���� ���� ����������� �������� 16��� �����
 * ������ ������� - 8��� ����
 * �������� ������� - �������� 16��� ���� + ������� ���������� ��������
 *
 * */


// 3R3G2B
//// 1�� ���� � 16��� �����
//static const uint32_t table1_8_to_16[256] = {
//BSRR_PREPARE_DATA|0x0000 , BSRR_PREPARE_DATA|0x0000 , BSRR_PREPARE_DATA|0x0000 , BSRR_PREPARE_DATA|0x0000 , BSRR_PREPARE_DATA|0x0001 , BSRR_PREPARE_DATA|0x0001 , BSRR_PREPARE_DATA|0x0001 , BSRR_PREPARE_DATA|0x0001 ,
//BSRR_PREPARE_DATA|0x0002 , BSRR_PREPARE_DATA|0x0002 , BSRR_PREPARE_DATA|0x0002 , BSRR_PREPARE_DATA|0x0002 , BSRR_PREPARE_DATA|0x0003 , BSRR_PREPARE_DATA|0x0003 , BSRR_PREPARE_DATA|0x0003 , BSRR_PREPARE_DATA|0x0003 ,
//BSRR_PREPARE_DATA|0x0004 , BSRR_PREPARE_DATA|0x0004 , BSRR_PREPARE_DATA|0x0004 , BSRR_PREPARE_DATA|0x0004 , BSRR_PREPARE_DATA|0x0005 , BSRR_PREPARE_DATA|0x0005 , BSRR_PREPARE_DATA|0x0005 , BSRR_PREPARE_DATA|0x0005 ,
//BSRR_PREPARE_DATA|0x0006 , BSRR_PREPARE_DATA|0x0006 , BSRR_PREPARE_DATA|0x0006 , BSRR_PREPARE_DATA|0x0006 , BSRR_PREPARE_DATA|0x0007 , BSRR_PREPARE_DATA|0x0007 , BSRR_PREPARE_DATA|0x0007 , BSRR_PREPARE_DATA|0x0007 ,
//BSRR_PREPARE_DATA|0x0020 , BSRR_PREPARE_DATA|0x0020 , BSRR_PREPARE_DATA|0x0020 , BSRR_PREPARE_DATA|0x0020 , BSRR_PREPARE_DATA|0x0021 , BSRR_PREPARE_DATA|0x0021 , BSRR_PREPARE_DATA|0x0021 , BSRR_PREPARE_DATA|0x0021 ,
//BSRR_PREPARE_DATA|0x0022 , BSRR_PREPARE_DATA|0x0022 , BSRR_PREPARE_DATA|0x0022 , BSRR_PREPARE_DATA|0x0022 , BSRR_PREPARE_DATA|0x0023 , BSRR_PREPARE_DATA|0x0023 , BSRR_PREPARE_DATA|0x0023 , BSRR_PREPARE_DATA|0x0023 ,
//BSRR_PREPARE_DATA|0x0024 , BSRR_PREPARE_DATA|0x0024 , BSRR_PREPARE_DATA|0x0024 , BSRR_PREPARE_DATA|0x0024 , BSRR_PREPARE_DATA|0x0025 , BSRR_PREPARE_DATA|0x0025 , BSRR_PREPARE_DATA|0x0025 , BSRR_PREPARE_DATA|0x0025 ,
//BSRR_PREPARE_DATA|0x0026 , BSRR_PREPARE_DATA|0x0026 , BSRR_PREPARE_DATA|0x0026 , BSRR_PREPARE_DATA|0x0026 , BSRR_PREPARE_DATA|0x0027 , BSRR_PREPARE_DATA|0x0027 , BSRR_PREPARE_DATA|0x0027 , BSRR_PREPARE_DATA|0x0027 ,
//BSRR_PREPARE_DATA|0x0040 , BSRR_PREPARE_DATA|0x0040 , BSRR_PREPARE_DATA|0x0040 , BSRR_PREPARE_DATA|0x0040 , BSRR_PREPARE_DATA|0x0041 , BSRR_PREPARE_DATA|0x0041 , BSRR_PREPARE_DATA|0x0041 , BSRR_PREPARE_DATA|0x0041 ,
//BSRR_PREPARE_DATA|0x0042 , BSRR_PREPARE_DATA|0x0042 , BSRR_PREPARE_DATA|0x0042 , BSRR_PREPARE_DATA|0x0042 , BSRR_PREPARE_DATA|0x0043 , BSRR_PREPARE_DATA|0x0043 , BSRR_PREPARE_DATA|0x0043 , BSRR_PREPARE_DATA|0x0043 ,
//BSRR_PREPARE_DATA|0x0044 , BSRR_PREPARE_DATA|0x0044 , BSRR_PREPARE_DATA|0x0044 , BSRR_PREPARE_DATA|0x0044 , BSRR_PREPARE_DATA|0x0045 , BSRR_PREPARE_DATA|0x0045 , BSRR_PREPARE_DATA|0x0045 , BSRR_PREPARE_DATA|0x0045 ,
//BSRR_PREPARE_DATA|0x0046 , BSRR_PREPARE_DATA|0x0046 , BSRR_PREPARE_DATA|0x0046 , BSRR_PREPARE_DATA|0x0046 , BSRR_PREPARE_DATA|0x0047 , BSRR_PREPARE_DATA|0x0047 , BSRR_PREPARE_DATA|0x0047 , BSRR_PREPARE_DATA|0x0047 ,
//BSRR_PREPARE_DATA|0x0060 , BSRR_PREPARE_DATA|0x0060 , BSRR_PREPARE_DATA|0x0060 , BSRR_PREPARE_DATA|0x0060 , BSRR_PREPARE_DATA|0x0061 , BSRR_PREPARE_DATA|0x0061 , BSRR_PREPARE_DATA|0x0061 , BSRR_PREPARE_DATA|0x0061 ,
//BSRR_PREPARE_DATA|0x0062 , BSRR_PREPARE_DATA|0x0062 , BSRR_PREPARE_DATA|0x0062 , BSRR_PREPARE_DATA|0x0062 , BSRR_PREPARE_DATA|0x0063 , BSRR_PREPARE_DATA|0x0063 , BSRR_PREPARE_DATA|0x0063 , BSRR_PREPARE_DATA|0x0063 ,
//BSRR_PREPARE_DATA|0x0064 , BSRR_PREPARE_DATA|0x0064 , BSRR_PREPARE_DATA|0x0064 , BSRR_PREPARE_DATA|0x0064 , BSRR_PREPARE_DATA|0x0065 , BSRR_PREPARE_DATA|0x0065 , BSRR_PREPARE_DATA|0x0065 , BSRR_PREPARE_DATA|0x0065 ,
//BSRR_PREPARE_DATA|0x0066 , BSRR_PREPARE_DATA|0x0066 , BSRR_PREPARE_DATA|0x0066 , BSRR_PREPARE_DATA|0x0066 , BSRR_PREPARE_DATA|0x0067 , BSRR_PREPARE_DATA|0x0067 , BSRR_PREPARE_DATA|0x0067 , BSRR_PREPARE_DATA|0x0067 ,
//BSRR_PREPARE_DATA|0x0080 , BSRR_PREPARE_DATA|0x0080 , BSRR_PREPARE_DATA|0x0080 , BSRR_PREPARE_DATA|0x0080 , BSRR_PREPARE_DATA|0x0081 , BSRR_PREPARE_DATA|0x0081 , BSRR_PREPARE_DATA|0x0081 , BSRR_PREPARE_DATA|0x0081 ,
//BSRR_PREPARE_DATA|0x0082 , BSRR_PREPARE_DATA|0x0082 , BSRR_PREPARE_DATA|0x0082 , BSRR_PREPARE_DATA|0x0082 , BSRR_PREPARE_DATA|0x0083 , BSRR_PREPARE_DATA|0x0083 , BSRR_PREPARE_DATA|0x0083 , BSRR_PREPARE_DATA|0x0083 ,
//BSRR_PREPARE_DATA|0x0084 , BSRR_PREPARE_DATA|0x0084 , BSRR_PREPARE_DATA|0x0084 , BSRR_PREPARE_DATA|0x0084 , BSRR_PREPARE_DATA|0x0085 , BSRR_PREPARE_DATA|0x0085 , BSRR_PREPARE_DATA|0x0085 , BSRR_PREPARE_DATA|0x0085 ,
//BSRR_PREPARE_DATA|0x0086 , BSRR_PREPARE_DATA|0x0086 , BSRR_PREPARE_DATA|0x0086 , BSRR_PREPARE_DATA|0x0086 , BSRR_PREPARE_DATA|0x0087 , BSRR_PREPARE_DATA|0x0087 , BSRR_PREPARE_DATA|0x0087 , BSRR_PREPARE_DATA|0x0087 ,
//BSRR_PREPARE_DATA|0x00a0 , BSRR_PREPARE_DATA|0x00a0 , BSRR_PREPARE_DATA|0x00a0 , BSRR_PREPARE_DATA|0x00a0 , BSRR_PREPARE_DATA|0x00a1 , BSRR_PREPARE_DATA|0x00a1 , BSRR_PREPARE_DATA|0x00a1 , BSRR_PREPARE_DATA|0x00a1 ,
//BSRR_PREPARE_DATA|0x00a2 , BSRR_PREPARE_DATA|0x00a2 , BSRR_PREPARE_DATA|0x00a2 , BSRR_PREPARE_DATA|0x00a2 , BSRR_PREPARE_DATA|0x00a3 , BSRR_PREPARE_DATA|0x00a3 , BSRR_PREPARE_DATA|0x00a3 , BSRR_PREPARE_DATA|0x00a3 ,
//BSRR_PREPARE_DATA|0x00a4 , BSRR_PREPARE_DATA|0x00a4 , BSRR_PREPARE_DATA|0x00a4 , BSRR_PREPARE_DATA|0x00a4 , BSRR_PREPARE_DATA|0x00a5 , BSRR_PREPARE_DATA|0x00a5 , BSRR_PREPARE_DATA|0x00a5 , BSRR_PREPARE_DATA|0x00a5 ,
//BSRR_PREPARE_DATA|0x00a6 , BSRR_PREPARE_DATA|0x00a6 , BSRR_PREPARE_DATA|0x00a6 , BSRR_PREPARE_DATA|0x00a6 , BSRR_PREPARE_DATA|0x00a7 , BSRR_PREPARE_DATA|0x00a7 , BSRR_PREPARE_DATA|0x00a7 , BSRR_PREPARE_DATA|0x00a7 ,
//BSRR_PREPARE_DATA|0x00c0 , BSRR_PREPARE_DATA|0x00c0 , BSRR_PREPARE_DATA|0x00c0 , BSRR_PREPARE_DATA|0x00c0 , BSRR_PREPARE_DATA|0x00c1 , BSRR_PREPARE_DATA|0x00c1 , BSRR_PREPARE_DATA|0x00c1 , BSRR_PREPARE_DATA|0x00c1 ,
//BSRR_PREPARE_DATA|0x00c2 , BSRR_PREPARE_DATA|0x00c2 , BSRR_PREPARE_DATA|0x00c2 , BSRR_PREPARE_DATA|0x00c2 , BSRR_PREPARE_DATA|0x00c3 , BSRR_PREPARE_DATA|0x00c3 , BSRR_PREPARE_DATA|0x00c3 , BSRR_PREPARE_DATA|0x00c3 ,
//BSRR_PREPARE_DATA|0x00c4 , BSRR_PREPARE_DATA|0x00c4 , BSRR_PREPARE_DATA|0x00c4 , BSRR_PREPARE_DATA|0x00c4 , BSRR_PREPARE_DATA|0x00c5 , BSRR_PREPARE_DATA|0x00c5 , BSRR_PREPARE_DATA|0x00c5 , BSRR_PREPARE_DATA|0x00c5 ,
//BSRR_PREPARE_DATA|0x00c6 , BSRR_PREPARE_DATA|0x00c6 , BSRR_PREPARE_DATA|0x00c6 , BSRR_PREPARE_DATA|0x00c6 , BSRR_PREPARE_DATA|0x00c7 , BSRR_PREPARE_DATA|0x00c7 , BSRR_PREPARE_DATA|0x00c7 , BSRR_PREPARE_DATA|0x00c7 ,
//BSRR_PREPARE_DATA|0x00e0 , BSRR_PREPARE_DATA|0x00e0 , BSRR_PREPARE_DATA|0x00e0 , BSRR_PREPARE_DATA|0x00e0 , BSRR_PREPARE_DATA|0x00e1 , BSRR_PREPARE_DATA|0x00e1 , BSRR_PREPARE_DATA|0x00e1 , BSRR_PREPARE_DATA|0x00e1 ,
//BSRR_PREPARE_DATA|0x00e2 , BSRR_PREPARE_DATA|0x00e2 , BSRR_PREPARE_DATA|0x00e2 , BSRR_PREPARE_DATA|0x00e2 , BSRR_PREPARE_DATA|0x00e3 , BSRR_PREPARE_DATA|0x00e3 , BSRR_PREPARE_DATA|0x00e3 , BSRR_PREPARE_DATA|0x00e3 ,
//BSRR_PREPARE_DATA|0x00e4 , BSRR_PREPARE_DATA|0x00e4 , BSRR_PREPARE_DATA|0x00e4 , BSRR_PREPARE_DATA|0x00e4 , BSRR_PREPARE_DATA|0x00e5 , BSRR_PREPARE_DATA|0x00e5 , BSRR_PREPARE_DATA|0x00e5 , BSRR_PREPARE_DATA|0x00e5 ,
//BSRR_PREPARE_DATA|0x00e6 , BSRR_PREPARE_DATA|0x00e6 , BSRR_PREPARE_DATA|0x00e6 , BSRR_PREPARE_DATA|0x00e6 , BSRR_PREPARE_DATA|0x00e7 , BSRR_PREPARE_DATA|0x00e7 , BSRR_PREPARE_DATA|0x00e7 , BSRR_PREPARE_DATA|0x00e7 ,
//};
//
//// 2�� ���� � 16��� �����
//static const uint32_t table2_8_to_16[256] = {
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 , BSRR_PREPARE_DATA | 0x0000 , BSRR_PREPARE_DATA | 0x0008 , BSRR_PREPARE_DATA | 0x0010 , BSRR_PREPARE_DATA | 0x0018 ,
//};


//1R3G4B
static const uint32_t table1_8_to_16[256] = {
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4d,BSRR_PREPARE_DATA | 0xDE,BSRR_PREPARE_DATA | 0xEF,BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x0,
BSRR_PREPARE_DATA | 0x1,BSRR_PREPARE_DATA | 0x1,BSRR_PREPARE_DATA | 0x1,BSRR_PREPARE_DATA | 0x1,BSRR_PREPARE_DATA | 0x1,BSRR_PREPARE_DATA | 0x1,BSRR_PREPARE_DATA | 0x1,BSRR_PREPARE_DATA | 0x1,
BSRR_PREPARE_DATA | 0x2,BSRR_PREPARE_DATA | 0x2,BSRR_PREPARE_DATA | 0x2,BSRR_PREPARE_DATA | 0x2,BSRR_PREPARE_DATA | 0x2,BSRR_PREPARE_DATA | 0x2,BSRR_PREPARE_DATA | 0x2,BSRR_PREPARE_DATA | 0x2,
BSRR_PREPARE_DATA | 0x3,BSRR_PREPARE_DATA | 0x3,BSRR_PREPARE_DATA | 0x3,BSRR_PREPARE_DATA | 0x3,BSRR_PREPARE_DATA | 0x3,BSRR_PREPARE_DATA | 0x3,BSRR_PREPARE_DATA | 0x3,BSRR_PREPARE_DATA | 0x3,
BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x4,
BSRR_PREPARE_DATA | 0x5,BSRR_PREPARE_DATA | 0x5,BSRR_PREPARE_DATA | 0x5,BSRR_PREPARE_DATA | 0x5,BSRR_PREPARE_DATA | 0x5,BSRR_PREPARE_DATA | 0x5,BSRR_PREPARE_DATA | 0x5,BSRR_PREPARE_DATA | 0x5,
BSRR_PREPARE_DATA | 0x6,BSRR_PREPARE_DATA | 0x6,BSRR_PREPARE_DATA | 0x6,BSRR_PREPARE_DATA | 0x6,BSRR_PREPARE_DATA | 0x6,BSRR_PREPARE_DATA | 0x6,BSRR_PREPARE_DATA | 0x6,BSRR_PREPARE_DATA | 0x6,
BSRR_PREPARE_DATA | 0x7,BSRR_PREPARE_DATA | 0x7,BSRR_PREPARE_DATA | 0x7,BSRR_PREPARE_DATA | 0x7,BSRR_PREPARE_DATA | 0x7,BSRR_PREPARE_DATA | 0x7,BSRR_PREPARE_DATA | 0x7,BSRR_PREPARE_DATA | 0x7,
BSRR_PREPARE_DATA | 0x40,BSRR_PREPARE_DATA | 0x40,BSRR_PREPARE_DATA | 0x40,BSRR_PREPARE_DATA | 0x40,BSRR_PREPARE_DATA | 0x40,BSRR_PREPARE_DATA | 0x40,BSRR_PREPARE_DATA | 0x40,BSRR_PREPARE_DATA | 0x40,
BSRR_PREPARE_DATA | 0x41,BSRR_PREPARE_DATA | 0x41,BSRR_PREPARE_DATA | 0x41,BSRR_PREPARE_DATA | 0x41,BSRR_PREPARE_DATA | 0x41,BSRR_PREPARE_DATA | 0x41,BSRR_PREPARE_DATA | 0x41,BSRR_PREPARE_DATA | 0x41,
BSRR_PREPARE_DATA | 0x42,BSRR_PREPARE_DATA | 0x42,BSRR_PREPARE_DATA | 0x42,BSRR_PREPARE_DATA | 0x42,BSRR_PREPARE_DATA | 0x42,BSRR_PREPARE_DATA | 0x42,BSRR_PREPARE_DATA | 0x42,BSRR_PREPARE_DATA | 0x42,
BSRR_PREPARE_DATA | 0x43,BSRR_PREPARE_DATA | 0x43,BSRR_PREPARE_DATA | 0x43,BSRR_PREPARE_DATA | 0x43,BSRR_PREPARE_DATA | 0x43,BSRR_PREPARE_DATA | 0x43,BSRR_PREPARE_DATA | 0x43,BSRR_PREPARE_DATA | 0x43,
BSRR_PREPARE_DATA | 0x44,BSRR_PREPARE_DATA | 0x44,BSRR_PREPARE_DATA | 0x44,BSRR_PREPARE_DATA | 0x44,BSRR_PREPARE_DATA | 0x44,BSRR_PREPARE_DATA | 0x44,BSRR_PREPARE_DATA | 0x44,BSRR_PREPARE_DATA | 0x44,
BSRR_PREPARE_DATA | 0x45,BSRR_PREPARE_DATA | 0x45,BSRR_PREPARE_DATA | 0x45,BSRR_PREPARE_DATA | 0x45,BSRR_PREPARE_DATA | 0x45,BSRR_PREPARE_DATA | 0x45,BSRR_PREPARE_DATA | 0x45,BSRR_PREPARE_DATA | 0x45,
BSRR_PREPARE_DATA | 0x46,BSRR_PREPARE_DATA | 0x46,BSRR_PREPARE_DATA | 0x46,BSRR_PREPARE_DATA | 0x46,BSRR_PREPARE_DATA | 0x46,BSRR_PREPARE_DATA | 0x46,BSRR_PREPARE_DATA | 0x46,BSRR_PREPARE_DATA | 0x46,
BSRR_PREPARE_DATA | 0x47,BSRR_PREPARE_DATA | 0x47,BSRR_PREPARE_DATA | 0x47,BSRR_PREPARE_DATA | 0x47,BSRR_PREPARE_DATA | 0x47,BSRR_PREPARE_DATA | 0x47,BSRR_PREPARE_DATA | 0x47,BSRR_PREPARE_DATA | 0x47,
BSRR_PREPARE_DATA | 0x80,BSRR_PREPARE_DATA | 0x80,BSRR_PREPARE_DATA | 0x80,BSRR_PREPARE_DATA | 0x80,BSRR_PREPARE_DATA | 0x80,BSRR_PREPARE_DATA | 0x80,BSRR_PREPARE_DATA | 0x80,BSRR_PREPARE_DATA | 0x80,
BSRR_PREPARE_DATA | 0x81,BSRR_PREPARE_DATA | 0x81,BSRR_PREPARE_DATA | 0x81,BSRR_PREPARE_DATA | 0x81,BSRR_PREPARE_DATA | 0x81,BSRR_PREPARE_DATA | 0x81,BSRR_PREPARE_DATA | 0x81,BSRR_PREPARE_DATA | 0x81,
BSRR_PREPARE_DATA | 0x82,BSRR_PREPARE_DATA | 0x82,BSRR_PREPARE_DATA | 0x82,BSRR_PREPARE_DATA | 0x82,BSRR_PREPARE_DATA | 0x82,BSRR_PREPARE_DATA | 0x82,BSRR_PREPARE_DATA | 0x82,BSRR_PREPARE_DATA | 0x82,
BSRR_PREPARE_DATA | 0x83,BSRR_PREPARE_DATA | 0x83,BSRR_PREPARE_DATA | 0x83,BSRR_PREPARE_DATA | 0x83,BSRR_PREPARE_DATA | 0x83,BSRR_PREPARE_DATA | 0x83,BSRR_PREPARE_DATA | 0x83,BSRR_PREPARE_DATA | 0x83,
BSRR_PREPARE_DATA | 0x84,BSRR_PREPARE_DATA | 0x84,BSRR_PREPARE_DATA | 0x84,BSRR_PREPARE_DATA | 0x84,BSRR_PREPARE_DATA | 0x84,BSRR_PREPARE_DATA | 0x84,BSRR_PREPARE_DATA | 0x84,BSRR_PREPARE_DATA | 0x84,
BSRR_PREPARE_DATA | 0x85,BSRR_PREPARE_DATA | 0x85,BSRR_PREPARE_DATA | 0x85,BSRR_PREPARE_DATA | 0x85,BSRR_PREPARE_DATA | 0x85,BSRR_PREPARE_DATA | 0x85,BSRR_PREPARE_DATA | 0x85,BSRR_PREPARE_DATA | 0x85,
BSRR_PREPARE_DATA | 0x86,BSRR_PREPARE_DATA | 0x86,BSRR_PREPARE_DATA | 0x86,BSRR_PREPARE_DATA | 0x86,BSRR_PREPARE_DATA | 0x86,BSRR_PREPARE_DATA | 0x86,BSRR_PREPARE_DATA | 0x86,BSRR_PREPARE_DATA | 0x86,
BSRR_PREPARE_DATA | 0x87,BSRR_PREPARE_DATA | 0x87,BSRR_PREPARE_DATA | 0x87,BSRR_PREPARE_DATA | 0x87,BSRR_PREPARE_DATA | 0x87,BSRR_PREPARE_DATA | 0x87,BSRR_PREPARE_DATA | 0x87,BSRR_PREPARE_DATA | 0x87,
BSRR_PREPARE_DATA | 0xc0,BSRR_PREPARE_DATA | 0xc0,BSRR_PREPARE_DATA | 0xc0,BSRR_PREPARE_DATA | 0xc0,BSRR_PREPARE_DATA | 0xc0,BSRR_PREPARE_DATA | 0xc0,BSRR_PREPARE_DATA | 0xc0,BSRR_PREPARE_DATA | 0xc0,
BSRR_PREPARE_DATA | 0xc1,BSRR_PREPARE_DATA | 0xc1,BSRR_PREPARE_DATA | 0xc1,BSRR_PREPARE_DATA | 0xc1,BSRR_PREPARE_DATA | 0xc1,BSRR_PREPARE_DATA | 0xc1,BSRR_PREPARE_DATA | 0xc1,BSRR_PREPARE_DATA | 0xc1,
BSRR_PREPARE_DATA | 0xc2,BSRR_PREPARE_DATA | 0xc2,BSRR_PREPARE_DATA | 0xc2,BSRR_PREPARE_DATA | 0xc2,BSRR_PREPARE_DATA | 0xc2,BSRR_PREPARE_DATA | 0xc2,BSRR_PREPARE_DATA | 0xc2,BSRR_PREPARE_DATA | 0xc2,
BSRR_PREPARE_DATA | 0xc3,BSRR_PREPARE_DATA | 0xc3,BSRR_PREPARE_DATA | 0xc3,BSRR_PREPARE_DATA | 0xc3,BSRR_PREPARE_DATA | 0xc3,BSRR_PREPARE_DATA | 0xc3,BSRR_PREPARE_DATA | 0xc3,BSRR_PREPARE_DATA | 0xc3,
BSRR_PREPARE_DATA | 0xc4,BSRR_PREPARE_DATA | 0xc4,BSRR_PREPARE_DATA | 0xc4,BSRR_PREPARE_DATA | 0xc4,BSRR_PREPARE_DATA | 0xc4,BSRR_PREPARE_DATA | 0xc4,BSRR_PREPARE_DATA | 0xc4,BSRR_PREPARE_DATA | 0xc4,
BSRR_PREPARE_DATA | 0xc5,BSRR_PREPARE_DATA | 0xc5,BSRR_PREPARE_DATA | 0xc5,BSRR_PREPARE_DATA | 0xc5,BSRR_PREPARE_DATA | 0xc5,BSRR_PREPARE_DATA | 0xc5,BSRR_PREPARE_DATA | 0xc5,BSRR_PREPARE_DATA | 0xc5,
BSRR_PREPARE_DATA | 0xc6,BSRR_PREPARE_DATA | 0xc6,BSRR_PREPARE_DATA | 0xc6,BSRR_PREPARE_DATA | 0xc6,BSRR_PREPARE_DATA | 0xc6,BSRR_PREPARE_DATA | 0xc6,BSRR_PREPARE_DATA | 0xc6,BSRR_PREPARE_DATA | 0xc6,
BSRR_PREPARE_DATA | 0xc7,BSRR_PREPARE_DATA | 0xc7,BSRR_PREPARE_DATA | 0xc7,BSRR_PREPARE_DATA | 0xc7,BSRR_PREPARE_DATA | 0xc7,BSRR_PREPARE_DATA | 0xc7,BSRR_PREPARE_DATA | 0xc7,BSRR_PREPARE_DATA | 0xff,};


static const uint32_t table2_8_to_16[256] = {
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x31,BSRR_PREPARE_DATA | 0xFA,BSRR_PREPARE_DATA | 0x9C,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0x1c,
BSRR_PREPARE_DATA | 0x0,BSRR_PREPARE_DATA | 0x4,BSRR_PREPARE_DATA | 0x8,BSRR_PREPARE_DATA | 0xc,BSRR_PREPARE_DATA | 0x10,BSRR_PREPARE_DATA | 0x14,BSRR_PREPARE_DATA | 0x18,BSRR_PREPARE_DATA | 0xff,};
#endif // __St7789V_H
