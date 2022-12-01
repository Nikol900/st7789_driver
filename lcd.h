#ifndef	_LCD_HANDLER__H
#define _LCD_HANDLER__H

#include "st7789v.h"
#include "bitmap.h"
#include "stdbool.h"

//����� ������� � 8��� �������
typedef enum DISLAY_COLORS
{
 COLOR_BLACK		=0x00,
 COLOR_WHITE		=0xFF,
 COLOR_RED			=192,//0xE0,
 COLOR_GREEN		=16,//48,//104,//0x0C,
 COLOR_BRIGHT_GREEN = 48,
// COLOR_BLUE			=0x03,
 // 0x2d ������� ����� �� ���� ������� �������

 COLOR_WAVE         =18,//0x09,//0x29,//0x25,
 COLOR_TEXT         =COLOR_WAVE,//0x2e,
// COLOR_CYAN			=0x1F,
// COLOR_YELLOW		=0xFC,
// COLOR_ORANGE		=0xEC,
 COLOR_LIGHT_GRAY 	=172,//163,//245,//172,//100,//183,//247,//109,//0xB6,//0xDB,
 COLOR_GRAY			=82,//91,//0x92,
 COLOR_DARK_GRAY	=0x4d,//0x4e,//COLOR_WAVE,//0x92,//0x6D,
 COLOR_YELLOW       =240//248//240//232
}DisplayColors_t;


/* name: LCD_init
 * arg:
 * ret:
 * comment: ���������� ������� � ������
*/
void LCD_init();

/* name: LCD_deinit
 * arg:
 * ret:
 * comment: ����� � ���������� �������
*/
void LCD_deinit();

/* name: LCD_drawFillOver
 * arg:	x1,y1,x2,y2 - ���������� �������
 * 		x1,y1 - ���������� ������ �������� ����
 * 		x2,y2 - ���������� ������� ������� ����
 * 		color - ���� �������
 * ret:
 * comment: ������� ������� ������� �������� ������
*/
void LCD_drawFillOver16(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_drawFillOver(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,DisplayColors_t color);

/* name: LCD_fillPrepareColor
 * arg:	color - ���� �������
 * ret:
 * comment: ���������� � ������� �������(���������� ������ ������ ������ ������)
*/
void LCD_fillPrepareColor(DisplayColors_t color);

/* name: LCD_drawFillWithPreparedColor
 * arg:	x1,y1,x2,y2 - ���������� �������
 *		x1,y1 - ���������� ������ �������� ����
 * 		x2,y2 - ���������� ������� ������� ����
 * ret:
 * comment: ������� ������� ������� �������������� ������, ������� ��������� � ������(LCD_fillPrepare)
*/
void LCD_drawFillWithPreparedColor(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);


/* name: LCD_drawImgBitmap
 * arg: x,y - ��������� ���������� ��� ������� �����������
 * 		*Image - ��������� �� ��������� tImage �����������
 * ret:
 * comment: ������� ������ ������������, ���������� � �������� tImage
*/
void LCD_drawImgBitmap(uint16_t x,uint16_t y,const tImage *Image);


/* name: LCD_drawImgMono
 * arg: x,y - ��������� ���������� ��� ������� �����������
 * 		color_front - ���� 1
 * 		color_back - ���� 2
 * 		*Image - ��������� �� ��������� tImage �����������
 * ret:
 * comment: ������� ������ ����������� ������������ � �������������� ��������� ������, ���������� � �������� tImage
*/
void LCD_drawImgMono16(uint16_t x,uint16_t y,uint16_t color_front,uint16_t color_back, const tImage *Image);
void LCD_drawImgMono(uint16_t x,uint16_t y,DisplayColors_t color_front,DisplayColors_t color_back, const tImage *Image);


/* name: LCD_drawPixel
 * arg: x,y - ��������� ���������� ��� �������
 * 		color - ���� �������
  * ret:
 * comment: ������� ������ ������� ��������������� ������
*/
void LCD_drawPixel(uint16_t x,uint16_t y,DisplayColors_t color);


/* name: LCD_drawLine
 * arg: x1,y1,x2,y2 - ���������� �����
 *		x1,y1 - ���������� ������ �����
 * 		x2,y2 - ���������� ����� �����
 * 		color - ���� �����
  * ret:
 * comment: ������� ������ ����� �� �������� �����������
*/
void LCD_drawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,DisplayColors_t color);


/* name: LCD_drawRect
 * arg: x,y -��������� ����������
 * 		width,height - ������� ��������� ��������������
 * 		color - ���� ����� ��������������
  * ret:
 * comment: ������� �������������� �������������� �� �������� ��������
*/
void LCD_drawRect(uint16_t x,uint16_t y,uint16_t width,uint16_t height,DisplayColors_t color);


/* name: LCD_drawRectFilled
 * arg: x,y -��������� ����������
 * 		width,height - ������� ��������� ��������������
 * 		color_front - ���� ������� ��������������
 * 		color_back - ���� ����� ��������������
  * ret:
 * comment: ������� ������������ �������������� �� �������� ��������
*/
void LCD_drawRectFilled(uint16_t x,uint16_t y,uint16_t width,uint16_t height,DisplayColors_t color_front,DisplayColors_t color_back);

/* name: LCD_text
 * arg:	*str - ��������� �� ����� ������
 *		x,y - ��������� ����������
 * 		color_front - ���� �������
 * 		color_back - ���� ����
 * 		*font - ��������� �� ����� ���������
  * ret:
 * comment: ����� ������ �� �������� �����������
*/
void LCD_text16(const char *str, uint16_t x, uint16_t y, uint16_t color_front,uint16_t color_back, const tFont *font);
void LCD_text(const char *str, uint16_t x, uint16_t y, DisplayColors_t color_front,DisplayColors_t color_back, const tFont *font);

/* name: LCD_setLightningIntencity
 * arg:	percent - �������� ������� � ���������
  * ret:
 * comment: ��������� �������� �������� ������� �������
*/

void LCD_setLightningIntencity(uint8_t percent);

/* name: LCD_getLightningIntencity
 * arg:
 * ret:
 * comment: ��������� �������� �������� ������� �������
*/
uint8_t LCD_getLightningIntencity();

/* name: LCD_drawingIsBussy
 * arg:
 * ret: ��������� ���������. True - ���-�� ��������, ���� ������. False- ��� ��������
 * comment: ����� �������� ������ ��������� ������������(��-�� ����������), ������ ��������
 * ������������ �������� �� ����������� ���������
*/
bool LCD_drawingIsBussy();

#endif
