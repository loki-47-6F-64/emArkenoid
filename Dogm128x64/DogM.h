/* 
 * File:   DogM.h
 * Author: Ferry
 *
 * Created on June 30, 2012, 3:51 PM
 */

#ifndef DOGM_H
#define	DOGM_H

#define FONT_WIDTH 8

extern unsigned char boldFont[];
extern unsigned char itopia[];
extern unsigned char dogmScreen[8][128] ;

void mdog_Init(char,char);
void clearDisplay(void);
void initScreen();
void drawScreen(unsigned char[8][128], int, int );
void updateScreen(unsigned char[8][128], unsigned char, unsigned char, unsigned char, unsigned char);

//void setPixel(int , int );
//void clearPixel(int , int );

void drawBitmap(unsigned char *romString, int size);

void writeChar(unsigned char *font_ptr, unsigned char pageAdd, unsigned char columnAdd, unsigned char Character);
void writeString(unsigned char *font_ptr, unsigned char pageAdd, unsigned char columnAdd, char *string_ptr);

void mdog_spi_out(unsigned char data);
void SPI_cmd_send(unsigned char CmdToSend);
void SPI_data_send(unsigned char dataToSend);

void st7565r_set_column_address(unsigned char address);
void st7565r_set_page_address(unsigned char address);

#endif	/* DOGM_H */

