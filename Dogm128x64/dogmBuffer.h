/* 
 * File:   dogmBuffer.h
 * Author: Loki
 *
 * Created on 08 March 2013, 10:57
 */

#ifndef DOGMBUFFER_H
#define	DOGMBUFFER_H

#define clearBuffer initBuffer
extern unsigned char dogmBuffer[8][128];

void initBuffer();

__inline void setPixel(const int, const int);
__inline void clearPixel(const int, const int);

void loadBitmap( unsigned char *bitmap,
        unsigned int height, unsigned int width,
        unsigned int rowL, unsigned int columnL );
#endif	/* DOGMBUFFER_H */

