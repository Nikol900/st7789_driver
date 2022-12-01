#ifndef	_LCD_HANDLER__H
#define _LCD_HANDLER__H

#include "st7789v.h"
#include "bitmap.h"
#include "stdbool.h"

//цвета дисплея в 8бит формате
typedef enum DISLAY_COLORS
{
 COLOR_BLACK		=0x00,
 COLOR_WHITE		=0xFF,
 COLOR_RED			=192,//0xE0,
 COLOR_GREEN		=16,//48,//104,//0x0C,
 COLOR_BRIGHT_GREEN = 48,
// COLOR_BLUE			=0x03,
 // 0x2d зеелный похож на цвет корпуса приьора

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
 * comment: подготовка дисплея к работе
*/
void LCD_init();

/* name: LCD_deinit
 * arg:
 * ret:
 * comment: сброс и отключение дисплея
*/
void LCD_deinit();

/* name: LCD_drawFillOver
 * arg:	x1,y1,x2,y2 - координаты заливки
 * 		x1,y1 - координаты левого верхнего угла
 * 		x2,y2 - координаты правого нижнего угла
 * 		color - цвет заливки
 * ret:
 * comment: заливка области дисплея сплошным цветом
*/
void LCD_drawFillOver16(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_drawFillOver(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,DisplayColors_t color);

/* name: LCD_fillPrepareColor
 * arg:	color - цвет заливки
 * ret:
 * comment: подготовка к заливке дисплея(заполнение буфера данных нужным цветом)
*/
void LCD_fillPrepareColor(DisplayColors_t color);

/* name: LCD_drawFillWithPreparedColor
 * arg:	x1,y1,x2,y2 - координаты заливки
 *		x1,y1 - координаты левого верхнего угла
 * 		x2,y2 - координаты правого нижнего угла
 * ret:
 * comment: заливка дисплея заранее подготовленным цветом, который находится в буфере(LCD_fillPrepare)
*/
void LCD_drawFillWithPreparedColor(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);


/* name: LCD_drawImgBitmap
 * arg: x,y - начальные координаты для заливки изображения
 * 		*Image - указатель на структуру tImage изображения
 * ret:
 * comment: заливка экрана изображением, находящимя в стуктуре tImage
*/
void LCD_drawImgBitmap(uint16_t x,uint16_t y,const tImage *Image);


/* name: LCD_drawImgMono
 * arg: x,y - начальные координаты для заливки изображения
 * 		color_front - цвет 1
 * 		color_back - цвет 2
 * 		*Image - указатель на структуру tImage изображения
 * ret:
 * comment: заливка экрана монохромным изображением и использованием указанных цветов, находящимя в стуктуре tImage
*/
void LCD_drawImgMono16(uint16_t x,uint16_t y,uint16_t color_front,uint16_t color_back, const tImage *Image);
void LCD_drawImgMono(uint16_t x,uint16_t y,DisplayColors_t color_front,DisplayColors_t color_back, const tImage *Image);


/* name: LCD_drawPixel
 * arg: x,y - начальные координаты для пикселя
 * 		color - цвет пикселя
  * ret:
 * comment: рисовка одного пикселя соответствующим цветом
*/
void LCD_drawPixel(uint16_t x,uint16_t y,DisplayColors_t color);


/* name: LCD_drawLine
 * arg: x1,y1,x2,y2 - координаты линии
 *		x1,y1 - координаты начала линии
 * 		x2,y2 - координаты конца линии
 * 		color - цвет линии
  * ret:
 * comment: рисовка прямой линии по заданным координатам
*/
void LCD_drawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,DisplayColors_t color);


/* name: LCD_drawRect
 * arg: x,y -начальные координаты
 * 		width,height - размеры рисуемого прямоугольника
 * 		color - цвет линий прямоугольника
  * ret:
 * comment: рисовка незакрашенного прямоугольника по заданным размерам
*/
void LCD_drawRect(uint16_t x,uint16_t y,uint16_t width,uint16_t height,DisplayColors_t color);


/* name: LCD_drawRectFilled
 * arg: x,y -начальные координаты
 * 		width,height - размеры рисуемого прямоугольника
 * 		color_front - цвет заливки прямоугольника
 * 		color_back - цвет линий прямоугольника
  * ret:
 * comment: рисовка закрашенного прямоугольника по заданным размерам
*/
void LCD_drawRectFilled(uint16_t x,uint16_t y,uint16_t width,uint16_t height,DisplayColors_t color_front,DisplayColors_t color_back);

/* name: LCD_text
 * arg:	*str - указатель на сроку текста
 *		x,y - начальные координаты
 * 		color_front - цвет символа
 * 		color_back - цвет фона
 * 		*font - указатель на шрифт отрисовки
  * ret:
 * comment: вывод текста по заданным координатам
*/
void LCD_text16(const char *str, uint16_t x, uint16_t y, uint16_t color_front,uint16_t color_back, const tFont *font);
void LCD_text(const char *str, uint16_t x, uint16_t y, DisplayColors_t color_front,DisplayColors_t color_back, const tFont *font);

/* name: LCD_setLightningIntencity
 * arg:	percent - значение яркости в процентах
  * ret:
 * comment: установка текущего значения яркости дисплея
*/

void LCD_setLightningIntencity(uint8_t percent);

/* name: LCD_getLightningIntencity
 * arg:
 * ret:
 * comment: получение текущего значения яркости дисплея
*/
uint8_t LCD_getLightningIntencity();

/* name: LCD_drawingIsBussy
 * arg:
 * ret: состояние рисовалки. True - что-то рисуется, шина занята. False- все свободно
 * comment: чтобы избежать вызова рисования одновременно(из-за прерываний), данной функцией
 * производится проверка на возможность отрисовки
*/
bool LCD_drawingIsBussy();

#endif
