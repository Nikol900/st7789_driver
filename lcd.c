#include "lcd.h"
#include "PWM.h"
// количество точек дисплея в буфере
#define DMA_BUFFER_POINTS 75

//размер буферов для ДМА
//размер одной точки буфера ДМА
#define OP_SIZE					4//OnePoint size(две посылки 8бит + две команды)
//размер буфера для отрисовки
#define DMA_BUFFER_SIZE 		(DMA_BUFFER_POINTS*OP_SIZE)


/* global vars */
uint32_t DmaBuffer1[DMA_BUFFER_SIZE];//буфер1 для  ДМА
uint32_t DmaBuffer2[DMA_BUFFER_SIZE];//буфер2 для  ДМА


/* prots */
//должны переехать отсюда, или нет...
void dmaInit();
void dmaLoadBuffers();
static inline void calcBufferSize(uint32_t *totalBufferSize, uint32_t *currentBufferSize,uint32_t MAX_SIZE);
static inline void dmaSetBufferSize(uint32_t currentBufferSize);
static inline void dmaSetBuffer(uint32_t *buffer);
static inline void calcBufferSize();
static inline void dmaProcessing();
static inline void dmaProcessingFull(uint32_t *buffer, uint32_t currentBufferSize);


// вспомогательные функции внутри модуля
static inline uint8_t drawCharacter(const char ch,uint16_t x, uint16_t y, DisplayColors_t color_front,DisplayColors_t color_back,const tFont* font);
static inline uint8_t drawCharacter16(const char ch,uint16_t x, uint16_t y, uint16_t color_front,uint16_t color_back,const tFont* font);
static inline uint32_t calcTotalBufferSize(uint16_t width,uint16_t height);
static inline void lcdSetArea(uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2);

bool DrawingIsBussy = false;

bool LCD_drawingIsBussy()
{
    return DrawingIsBussy;
}

/* code */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * ПРЯМОУГОЛЬНИКИ * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//16бит
void LCD_drawFillOver16(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
    DrawingIsBussy = true;
    uint32_t totalBufferSize = calcTotalBufferSize((y2-y1),(x2-x1));//общий размер на отправку
    uint32_t currentBufferSize = totalBufferSize > DMA_BUFFER_SIZE ? DMA_BUFFER_SIZE: totalBufferSize;//текущий пакет

    //подготовили буфер к отправке
    for (uint32_t i = 0; i < currentBufferSize; i += OP_SIZE)
    {
        DmaBuffer1[i] = BSRR_PREPARE_DATA |((color>>8)&0xFF);
        DmaBuffer1[i + 2] = BSRR_PREPARE_DATA | ((color)&0xFF);
    }
    //подготовил дисплей к отрисовке
    lcdSetArea(x1, x2, y1, y2);

    //запустил дма в работу
    while (totalBufferSize) //пока есть что отправлять
    {
        //отправка данных
        dmaProcessingFull(DmaBuffer1, currentBufferSize);
        //пересчитал размер буфера
        calcBufferSize(&totalBufferSize,&currentBufferSize,DMA_BUFFER_SIZE);
    }
    DrawingIsBussy = false;
}
//8бит
void LCD_drawFillOver(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,DisplayColors_t color)
{
    DrawingIsBussy = true;
	uint32_t totalBufferSize = calcTotalBufferSize((y2-y1),(x2-x1));//общий размер на отправку
	uint32_t currentBufferSize = totalBufferSize > DMA_BUFFER_SIZE ? DMA_BUFFER_SIZE: totalBufferSize;//текущий пакет

	//подготовили буфер к отправке
	for (uint32_t i = 0; i < currentBufferSize; i += OP_SIZE)
	{
		DmaBuffer1[i] =  table1_8_to_16[color];
		DmaBuffer1[i + 2] =  table2_8_to_16[color];
	}
	//подготовил дисплей к отрисовке
	lcdSetArea(x1, x2, y1, y2);

	//запустил дма в работу
	while (totalBufferSize) //пока есть что отправлять
	{
		//отправка данных
		dmaProcessingFull(DmaBuffer1, currentBufferSize);
		//пересчитал размер буфера
		calcBufferSize(&totalBufferSize,&currentBufferSize,DMA_BUFFER_SIZE);
	}
	DrawingIsBussy = false;
}
void LCD_fillPrepareColor(DisplayColors_t color)
{
    DrawingIsBussy = true;
	//подготовили буфер
	for (uint32_t i = 0; i < DMA_BUFFER_SIZE; i += OP_SIZE)
	{
		DmaBuffer1[i] =  table1_8_to_16[color];
		//DmaBuffer1[i + 1] = BSRR_WR_SET;
		DmaBuffer1[i + 2] =  table2_8_to_16[color];
		//DmaBuffer1[i + 3] = BSRR_WR_SET;
	}
	DrawingIsBussy = false;
}
void LCD_drawFillWithPreparedColor(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    DrawingIsBussy = true;
	uint32_t totalBufferSize = calcTotalBufferSize((y2 - y1),(x2 - x1));//общий размер на отправку
	uint32_t currentBufferSize = totalBufferSize > DMA_BUFFER_SIZE ?	DMA_BUFFER_SIZE : totalBufferSize;//текущий пакет

	//подготовил дисплей к отисовке
	lcdSetArea(x1, x2, y1, y2);

	//запустил дма в работу
	while (totalBufferSize) //пока есть что отправлять
	{
		//отправка данных
		dmaProcessingFull(DmaBuffer1, currentBufferSize);
		//пересчитал размер буфера
		calcBufferSize(&totalBufferSize,&currentBufferSize,DMA_BUFFER_SIZE);
	}
	DrawingIsBussy = false;
}
void LCD_drawRect(uint16_t x,uint16_t y,uint16_t width,uint16_t height,DisplayColors_t color)
{
    DrawingIsBussy = true;
	width--;
	height--;
	LCD_drawLine(x,y,x,y+height,color);//+

	LCD_drawLine(x,y,x+width,y,color);//horizontal
	LCD_drawLine(x,y+height,x+width,y+height,color);//horizontal

	LCD_drawLine(x+width,y,x+width,y+height,color);//+
	DrawingIsBussy = false;
}

void LCD_drawRectFilled(uint16_t x,uint16_t y,uint16_t width,uint16_t height,DisplayColors_t color_front,DisplayColors_t color_back)
{
    DrawingIsBussy = true;
	LCD_drawFillOver(x,y,x+width,y+height,color_back);
	LCD_drawRect(x,y,width,height,color_front);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * ПИКСЕЛЬ * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LCD_drawPixel(uint16_t x,uint16_t y,DisplayColors_t color)
{
    DrawingIsBussy = true;
	//подготовил дисплей к отрисовке
	lcdSetArea(x,x, y, y);

    LCD_D0_PORT->BSRR = table1_8_to_16[color];
    LCD_D0_PORT->BSRR = BSRR_WR_SET;//set WR
    LCD_D0_PORT->BSRR = table2_8_to_16[color];
    LCD_D0_PORT->BSRR = BSRR_WR_SET;//set WR
    DrawingIsBussy = false;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * ЛИНИИ * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static inline void drawLineDiagonal(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,DisplayColors_t color)
{
    DrawingIsBussy = true;
	float yTemp;
	float angle = (float)(y1 - y0)/(x1 - x0);
	if (x1 > x0)
	{
		for (uint16_t i = 0; i < (x1 - x0 + 1); i++)
		{
			yTemp = i * angle + y0;
			LCD_drawPixel(x0 + i, (uint16_t) yTemp, color);
			if (y1 > y0)
			{
				if (((uint16_t) yTemp) < y1)
					LCD_drawPixel(x0 + i, ((uint16_t) yTemp) + 1, color);
			}
			else
			{
				if (((uint16_t) yTemp) > y1)
					LCD_drawPixel(x0 + i, ((uint16_t) yTemp) - 1, color);
			}
		}
	}
	else
	{
		for (uint16_t i = 0; i < (x0 - x1 + 1); i++)
		{
			yTemp = i * angle + y1;
			LCD_drawPixel(x1 + i, (uint16_t) yTemp, color);
			if (y0 > y1)
			{
				if (((uint16_t) yTemp) < y0)
					LCD_drawPixel(x1 + i, ((uint16_t) yTemp) + 1, color);
			}
			else
			{
				if (((uint16_t) yTemp) > y0)
					LCD_drawPixel(x1 + i, ((uint16_t) yTemp) - 1, color);
			}
		}
	}
	DrawingIsBussy = false;
}

void LCD_drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, DisplayColors_t color)
{
    DrawingIsBussy = true;
	if (x1 == x2)	//вертикаль
	{
		LCD_drawFillOver(x1, y1, x1 + 1, y2 + 1, color);//линия представлена в виде заливки опеределлного участка
	}
	else if (y1 == y2)	//горизонталь
	{
		LCD_drawFillOver(x1, y1, x2 + 1, y1 + 1, color);//линия представлена в виде заливки опеределлного участка
	}
	else	//любая другая прямая
	{
		drawLineDiagonal(x1, y1, x2, y2, color);
	}
	DrawingIsBussy = false;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * КАРТИНКИ * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//получить значение точки в байте для монохромной картинки
static inline uint8_t imgMonoGetPix(uint8_t byte, uint8_t pos)
{
	return ((byte >> (7-pos))&0x01);//? 1:0;
}
void LCD_drawImgMono16(uint16_t x,uint16_t y,uint16_t color_front,uint16_t color_back, const tImage *Image)
{
    DrawingIsBussy = true;
    uint16_t x2 = x+Image->width;// > LCD_WIDTH ? LCD_WIDTH : Image->width;
    uint16_t y2 = y+Image->height;// > LCD_HEIGHT ? LCD_HEIGHT : Image->height;

    uint32_t totalBufferSize = calcTotalBufferSize((y2 - y), (x2 - x));//общий размер на отправку
    uint32_t currentBufferSize = totalBufferSize > DMA_BUFFER_SIZE ? DMA_BUFFER_SIZE: totalBufferSize;//текущий размер пакета

    uint32_t imageBufferIdx = 0;//индекс байта в буфере изображения


    ///подготовительные данные, чтобы не заниматься этим внутри циклов
    uint32_t table1_ColorBack = BSRR_PREPARE_DATA |((color_back>>8)&0xFF);//цвет фона первых 8бит
    uint32_t table2_ColorBack = BSRR_PREPARE_DATA | ((color_back)&0xFF);//цвет фона последних 8бит
    uint32_t table1_ColorFront = BSRR_PREPARE_DATA |((color_front>>8)&0xFF);
    uint32_t table2_ColorFront = BSRR_PREPARE_DATA | ((color_front)&0xFF);

    uint8_t imgByte = Image->data[imageBufferIdx];//получил первый байт картинки из массива

    uint16_t bitPos = 0;//позиция бита в байте

    uint8_t dmaBufferNumb = 0;   //начинать с этого буфера
    uint32_t *dmaBufferPointer;//указатель на массив ДМА

    //подготовил первый пакет
    for (uint32_t i = 0; i < currentBufferSize; i += OP_SIZE)
    {
        if(imgMonoGetPix(imgByte,bitPos))
        {
            DmaBuffer1[i] =     table1_ColorFront;
            DmaBuffer1[i + 2] = table2_ColorFront;
        }
        else
        {
            DmaBuffer1[i] =     table1_ColorBack;
            DmaBuffer1[i + 2] = table2_ColorBack;
        }
        //DmaBuffer2 не заполнять, заполнится во время работы

        {//пересчет позиций в буфере
            bitPos++;
            if (bitPos == 8)
            {
                imageBufferIdx++;
                imgByte = Image->data[imageBufferIdx];
                bitPos = 0;
            }
        }
    }

    //подготовил дисплей к отрисовке
    lcdSetArea(x, x2, y, y2);//Выставили область

    while (totalBufferSize) //пока есть что отправлять
    {
        calcBufferSize(&totalBufferSize,&currentBufferSize,DMA_BUFFER_SIZE);//пересчитал размер буфера
        dmaSetBufferSize(currentBufferSize);//установил новый размер на отправку по дма

        if (dmaBufferNumb) //выбор буфера на отправку
        {
            dmaSetBuffer(DmaBuffer2);//зарядил буфер на отправку
            dmaBufferPointer =DmaBuffer1;
        }
        else
        {
            dmaSetBuffer(DmaBuffer1);//зарядил буфер на отправку
            dmaBufferPointer =DmaBuffer2;
        }


        for (uint32_t i = 0; i < currentBufferSize; i += OP_SIZE) //подготовил новые данные
        {

            if(imgMonoGetPix(imgByte,bitPos))
            {
                dmaBufferPointer[i] =   table1_ColorFront;
                dmaBufferPointer[i + 2] = table2_ColorFront;
            }
            else
            {
                dmaBufferPointer[i] =   table1_ColorBack;
                dmaBufferPointer[i + 2] = table2_ColorBack;
            }

            {//пересчет позиций в буфере
                bitPos++;
                if (bitPos == 8)
                {
                    imageBufferIdx++;
                    imgByte = Image->data[imageBufferIdx];
                    bitPos = 0;
                }
            }
        }
        dmaProcessing();                //ждем окончания отправки пакета
        dmaBufferNumb = !dmaBufferNumb; //смена номера буфера

    }
    DrawingIsBussy = false;
}
void LCD_drawImgMono(uint16_t x,uint16_t y,DisplayColors_t color_front,DisplayColors_t color_back, const tImage *Image)
{
    DrawingIsBussy = true;
	uint16_t x2 = x+Image->width;// > LCD_WIDTH ? LCD_WIDTH : Image->width;
	uint16_t y2 = y+Image->height;// > LCD_HEIGHT ? LCD_HEIGHT : Image->height;

	uint32_t totalBufferSize = calcTotalBufferSize((y2 - y), (x2 - x));//общий размер на отправку
	uint32_t currentBufferSize = totalBufferSize > DMA_BUFFER_SIZE ? DMA_BUFFER_SIZE: totalBufferSize;//текущий размер пакета

	uint32_t imageBufferIdx = 0;//индекс байта в буфере изображения

	///подготовительные данные, чтобы не заниматься этим внутри циклов
	uint32_t table1_ColorBack = table1_8_to_16[color_back];//цвет фона первых 8бит
	uint32_t table2_ColorBack = table2_8_to_16[color_back];//цвет фона последних 8бит
	uint32_t table1_ColorFront = table1_8_to_16[color_front];
	uint32_t table2_ColorFront = table2_8_to_16[color_front];

	uint8_t imgByte = Image->data[imageBufferIdx];//получил первый байт картинки из массива

	uint16_t bitPos = 0;//позиция бита в байте

	uint8_t dmaBufferNumb = 0;   //начинать с этого буфера
	uint32_t *dmaBufferPointer;//указатель на массив ДМА

	//подготовил первый пакет
	for (uint32_t i = 0; i < currentBufferSize; i += OP_SIZE)
	{
		if(imgMonoGetPix(imgByte,bitPos))
		{
			DmaBuffer1[i] = 	table1_ColorFront;
			DmaBuffer1[i + 2] = table2_ColorFront;
		}
		else
		{
			DmaBuffer1[i] = 	table1_ColorBack;
			DmaBuffer1[i + 2] = table2_ColorBack;
		}
		//DmaBuffer2 не заполнять, заполнится во время работы

		{//пересчет позиций в буфере
			bitPos++;
			if (bitPos == 8)
			{
				imageBufferIdx++;
				imgByte = Image->data[imageBufferIdx];
				bitPos = 0;
			}
		}
	}

	//подготовил дисплей к отрисовке
	lcdSetArea(x, x2, y, y2);//Выставили область

	while (totalBufferSize) //пока есть что отправлять
	{
		calcBufferSize(&totalBufferSize,&currentBufferSize,DMA_BUFFER_SIZE);//пересчитал размер буфера
		dmaSetBufferSize(currentBufferSize);//установил новый размер на отправку по дма

		if (dmaBufferNumb) //выбор буфера на отправку
		{
			dmaSetBuffer(DmaBuffer2);//зарядил буфер на отправку
			dmaBufferPointer =DmaBuffer1;
		}
		else
		{
			dmaSetBuffer(DmaBuffer1);//зарядил буфер на отправку
			dmaBufferPointer =DmaBuffer2;
		}


		for (uint32_t i = 0; i < currentBufferSize; i += OP_SIZE) //подготовил новые данные
		{

			if(imgMonoGetPix(imgByte,bitPos))
			{
				dmaBufferPointer[i] = 	table1_ColorFront;
				dmaBufferPointer[i + 2] = table2_ColorFront;
			}
			else
			{
				dmaBufferPointer[i] = 	table1_ColorBack;
				dmaBufferPointer[i + 2] = table2_ColorBack;
			}

			{//пересчет позиций в буфере
				bitPos++;
				if (bitPos == 8)
				{
					imageBufferIdx++;
					imgByte = Image->data[imageBufferIdx];
					bitPos = 0;
				}
			}
		}
		dmaProcessing();				//ждем окончания отправки пакета
		dmaBufferNumb = !dmaBufferNumb; //смена номера буфера

	}
	DrawingIsBussy = false;
}
void LCD_drawImgBitmap(uint16_t x,uint16_t y,const tImage *Image)
{

    DrawingIsBussy = true;
	uint16_t x2 = Image->width +x;
	uint16_t y2 = Image->height+y;

	uint32_t totalBufferSize = calcTotalBufferSize((y2 - y), (x2 - x));//общий размер на отправку
	uint32_t currentBufferSize = totalBufferSize > DMA_BUFFER_SIZE ? DMA_BUFFER_SIZE: totalBufferSize;//текущий пакет
	uint32_t imageBufferIdx = 0;//индекс байта в буфере изображения

	uint8_t dmaBufferNumb = 0;   //начинать с этого буфера
	uint32_t *dmaBufferPointer;//указатель на массив ДМА


//подготовил первый пакет
	for (uint32_t i = 0; i < currentBufferSize; i += OP_SIZE)
	{
		DmaBuffer1[i] = table1_8_to_16[Image->data[imageBufferIdx]];
		DmaBuffer1[i + 2] = table2_8_to_16[Image->data[imageBufferIdx]];
		imageBufferIdx++;
	}
	//подготовил дисплей к отрисовке
	lcdSetArea(x, x2, y, y2);

	while (totalBufferSize) //пока есть что отправлять
	{
		calcBufferSize(&totalBufferSize,&currentBufferSize,DMA_BUFFER_SIZE);//пересчитал размер буфера
		dmaSetBufferSize(currentBufferSize);//установил новый размер на отправку по дма

		if (dmaBufferNumb) //выбор буфера на отправку
		{
			dmaSetBuffer(DmaBuffer2);//зарядил буфер на отправку
			dmaBufferPointer =DmaBuffer1;
		}
		else
		{
			dmaSetBuffer(DmaBuffer1);//зарядил буфер на отправку
			dmaBufferPointer =DmaBuffer2;
		}
		for (uint32_t i = 0; i < currentBufferSize; i += OP_SIZE) //подготовил новые данные
		{
			dmaBufferPointer[i] = table1_8_to_16[Image->data[imageBufferIdx]];
			dmaBufferPointer[i + 2] = table2_8_to_16[Image->data[imageBufferIdx]];
			imageBufferIdx++;
		}
		dmaProcessing();				//ждем окончания отправки пакета
		dmaBufferNumb = !dmaBufferNumb; //смена номера буфера
	}
	DrawingIsBussy = false;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * ТЕКСТ * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "string.h"
#define SPEC_LF 10// адрес символа переноса строки /n

void LCD_text16(const char *str, uint16_t x, uint16_t y, uint16_t color_front, uint16_t color_back, const tFont *font)
{
    DrawingIsBussy = true;
    uint16_t posX = x;
    uint16_t posY = y;

    uint16_t strSize = strlen(str);

    /*ограничения по размерам выводимых сиволов */
    uint16_t maxWidth = LCD_WIDTH - 1;
    uint16_t maxHeight = LCD_HEIGHT - 1;

    //по каждому симолву в строке
    for (uint16_t i = 0; i < strSize; i++)
    {
        if (str[i] == SPEC_LF)//если перенос строки
        {
            posY += font->height;
            posX = x;
        }
        else//иначе символ
        {
            posX += drawCharacter16(str[i], posX, posY, color_front, color_back,font);//рисовка символа
            if (posX > maxWidth)//если конец строки
            {
                posX = x;
                posY += font->height;//переход на новую
            }
        }
        if (posY > maxHeight)//если конец по высоте - выход
            return;
    }
    DrawingIsBussy = false;
}


void LCD_text(const char *str, uint16_t x, uint16_t y, DisplayColors_t color_front, DisplayColors_t color_back, const tFont *font)
{
    DrawingIsBussy = true;
	uint16_t posX = x;
	uint16_t posY = y;

	uint16_t strSize = strlen(str);

	/*ограничения по размерам выводимых сиволов */
	uint16_t maxWidth = LCD_WIDTH - 1;
	uint16_t maxHeight = LCD_HEIGHT - 1;

	//по каждому симолву в строке
	for (uint16_t i = 0; i < strSize; i++)
	{
		if (str[i] == SPEC_LF)//если перенос строки
		{
			posY += font->height;
			posX = x;
		}
		else//иначе символ
		{
			posX += drawCharacter(str[i], posX, posY, color_front, color_back,font);//рисовка символа
			if (posX > maxWidth)//если конец строки
			{
				posX = x;
				posY += font->height;//переход на новую
			}
		}
		if (posY > maxHeight)//если конец по высоте - выход
			return;
	}
	DrawingIsBussy = false;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * СИСТЕМНЫЕ * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LCD_init()
{

	//prepare lcd pins
	//LL_GPIO_SetOutputPin(LCD_BL_EN_PORT, LCD_BL_EN_PIN);//PWM now
	LL_GPIO_SetOutputPin(LCD_RST_PORT, LCD_RST_PIN);
	LL_GPIO_SetOutputPin(LCD_WR_PORT, LCD_WR_PIN | LCD_RD_PIN | LCD_DC_PIN);

	//init LCD driver
	St7789_init();
	LL_mDelay(12);
	dmaInit();

	dmaLoadBuffers();//предподготовка значений в буфере
}

void LCD_deinit()
{
	St7789_deinit();
	LL_GPIO_ResetOutputPin(LCD_BL_EN_PORT, LCD_BL_EN_PIN);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t LightingIntencity = 0;
// проверить по факту
#define TIMEOUT_80US 3000//частота шины 32Mhz, значит 1/32Mhz * 3000 = 93uS должно хватить.
volatile uint16_t LightHiIntesTimeout = 0;

void LCD_setLightningIntencity(uint8_t percent)
{
    //если текущий уровень яркости 0, и пришло новое задание яркости
    if((LightingIntencity == 0)&& (LightingIntencity!=percent))
    {
        //зарядить на 80мкс шим в 100%
        PWM_setLightningPWMwidth(1);//percent to float
        PWM_processing();
        LightHiIntesTimeout = TIMEOUT_80US;
        while(--LightHiIntesTimeout);
       // LL_mDelay(1000);//проверка что работает
    }
	if(percent > 100)percent = 100;
	LightingIntencity = percent;
	PWM_setLightningPWMwidth(LightingIntencity/100.0f);//percent to float
	PWM_processing();
}

uint8_t  LCD_getLightningIntencity()
{
	return LightingIntencity;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// вспомогательные функции

#define SYMBOLS_TABLE_SHIFT 32 //сдвиг в таблице кодировки, т.к. первые 32 символа не храним в таблице шрифта
//рисовка одного символа

static inline uint8_t getSymbol(const char ch)
{
	//если символ из диапазона непечатаемых 0-32
	if (ch < SYMBOLS_TABLE_SHIFT)
		return 0; // заменяем пробелом
	else
		return ch - SYMBOLS_TABLE_SHIFT; //иначе вернули символ
}
static inline uint8_t drawCharacter(const char ch,uint16_t x, uint16_t y, DisplayColors_t color_front,DisplayColors_t color_back,const tFont* font)
{

    const tImage *image = font->chars[getSymbol(ch)].image;

    LCD_drawImgMono(x, y, color_front, color_back, image); //символы рисуем как монокартинки
    return image->width;
}
static inline uint8_t drawCharacter16(const char ch,uint16_t x, uint16_t y, uint16_t color_front,uint16_t color_back,const tFont* font)
{
    const tImage *image = font->chars[getSymbol(ch)].image;
    LCD_drawImgMono16(x, y, color_front, color_back, image); //символы рисуем как монокартинки
    return image->width;
}

static inline uint32_t calcTotalBufferSize(uint16_t width,uint16_t height)
{
	return OP_SIZE *width * height;//полная длина буфера изображения//4*240*320;//
}
static inline void lcdSetArea(uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2)
{
	St7789_setArea(x1, x2-1, y1, y2-1);//Выставили область
	St7789_startData();//разрешение на отправку буфера
}

/* перерасчет общей длины и текущей длины на отправку */
static inline void calcBufferSize(uint32_t *totalBufferSize, uint32_t *currentBufferSize,uint32_t MAX_SIZE)
{
	*currentBufferSize = *totalBufferSize > MAX_SIZE ? MAX_SIZE : *totalBufferSize;		//текущий пакет
	*totalBufferSize -= *currentBufferSize;
}


// функции работы с ДМА. которые должны отсюда съехать

/* перешел на дефайны для канала и флагов для удобного перехода на любой ДМА и канал*/
#define DMAx 					DMA2
#define DMAx_CHANNELy 			DMA2_Channel5
#define DMA_IS_ACTIVE_FLAG_TC 	LL_DMA_IsActiveFlag_TC5
#define DMA_CLEAR_FLAG_TC 		LL_DMA_ClearFlag_TC5
void dmaInit()
{
	//init dma
	DMAx_CHANNELy->CMAR = (uint32_t) &LCD_D0_PORT->BSRR; // SetMemoryAddress
	DMAx_CHANNELy->CPAR = (uint32_t) &DmaBuffer1;  // SetPeriphAddress
}


void dmaLoadBuffers()
{
	for (uint32_t i = 0; i < DMA_BUFFER_SIZE; i += OP_SIZE)
	{
		DmaBuffer1[i + 1] = BSRR_WR_SET;
		DmaBuffer1[i + 3] = BSRR_WR_SET;

		DmaBuffer2[i + 1] = BSRR_WR_SET;
		DmaBuffer2[i + 3] = BSRR_WR_SET;
	}
}


/* выставление новой длины пакета для отправки по ДМА */
static inline void dmaSetBufferSize(uint32_t currentBufferSize)
{
	DMAx_CHANNELy->CCR &= (uint16_t) (~DMA_CCR_EN); //disable DMA
	DMAx_CHANNELy->CNDTR = currentBufferSize; //set buf size
}

/* смена источника для ДМА */
static inline void dmaSetBuffer(uint32_t *buffer)
{
	DMAx_CHANNELy->CPAR = (uint32_t) buffer; //set buff
	DMAx_CHANNELy->CCR |= DMA_CCR_EN; //enable DMA
}
/* ождиание конца отправки ДМА*/
static inline void dmaProcessing()
{
	while (!(DMA_IS_ACTIVE_FLAG_TC(DMAx)))
		;
	DMA_CLEAR_FLAG_TC(DMAx); //reset flag
}
/* полный набор действий с ДМА */
static inline void dmaProcessingFull(uint32_t *buffer, uint32_t currentBufferSize)
{
	//DMA1_Channel1->CCR &= (uint16_t) (~DMA_CCR_EN); //disable DMA
	//DMA1_Channel1->CNDTR = currentBufferSize; //set buf size
	dmaSetBufferSize(currentBufferSize);

	/*DMA1_Channel1->CPAR =(uint32_t) buffer; //set buff
	 DMA1_Channel1->CCR |= DMA_CCR_EN; //enable DMA*/
	dmaSetBuffer(buffer);

	//	while(!(LL_DMA_IsActiveFlag_TC1(DMA1)));
	//	LL_DMA_ClearFlag_TC1(DMA1);//reset flag
	dmaProcessing();
}
