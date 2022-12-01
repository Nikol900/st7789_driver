/*
 * bitmap.h
 *
 *  Created on: 7 èþë. 2021 ã.
 *      Author: Nikol
 */

#ifndef SRC_MODULES_LCD_BITMAP_H_
#define SRC_MODULES_LCD_BITMAP_H_

#include "main.h"

//typedef struct
//{
//    const uint16_t *data;
//    uint16_t width;
//    uint16_t height;
//   // uint8_t  dataSize;
//} tImageCol;

typedef struct
{
    const uint8_t *data;
    uint16_t width;
    uint16_t height;
    uint8_t  dataSize;
} tImage;

typedef struct
{
   // long int code;
    const tImage *image;
} tChar;

typedef struct
{
	uint8_t height;
    const tChar *chars;
} tFont;



#endif /* SRC_MODULES_LCD_BITMAP_H_ */
