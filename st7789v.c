#include "st7789v.h"
#include "stm32l1xx_ll_utils.h"//delay here
//==========================================================================================
void St7789_init()
{
	LL_mDelay(160);
	St7789_wrCmd(St7789V_SLEEP_OUT);
	LL_mDelay(50);
	St7789_wrCmd(St7789V_SET_GAMMA);
	St7789_wrData(0x01);
	St7789_wrCmd(St7789V_MEMORY_ACCESS_CONTROL);
	St7789_wrData(0x00);
	St7789_wrCmd(St7789V_SET_PIXEL_FORMAT);
	St7789_wrData(0x55); // 16bit format
	St7789_wrCmd(St7789V_FRAME_RATE_CONTROL2);
	St7789_wrData(0x05);
	St7789_wrCmd(St7789V_DISPLAY_ON);  // display on
}

void St7789_deinit()
{
	St7789_wrCmd(St7789V_DISPLAY_OFF);  // display off
}
//==========================================================================================

void St7789_clear()
{
	uint16_t col = 0x0000;//цвет черный
	St7789_setArea(0, LCD_WIDTH + LCD_WIDTH_OFFSET - 1,	LCD_HEIGHT_OFFSET, LCD_HEIGHT + LCD_HEIGHT_OFFSET - 1);

	uint8_t col1 = col >> 8;
	uint8_t col2 = col;

	for (uint32_t i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) //240 * 320 = 76800
	{
		LCD_D0_PORT->BSRR = BSRR_PREPARE_DATA | col1; // set 8 bits
		LCD_D0_PORT->BSRR = BSRR_WR_SET; //set WR
		LCD_D0_PORT->BSRR = BSRR_PREPARE_DATA | col2 ; // set 8 bits
		LCD_D0_PORT->BSRR = BSRR_WR_SET; //set WR
	}
}

