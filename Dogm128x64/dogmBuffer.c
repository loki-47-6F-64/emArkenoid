#include "dogmBuffer.h"
#include "../emAssert.h"
unsigned char dogmBuffer[8][128];
int frameBuffer;

void initBuffer() {
    int rowCount = 0;
    int colCount = 0;
    for (rowCount = 0; rowCount < 8; rowCount++) {
        for (colCount = 0; colCount < 128; colCount++)
            dogmBuffer[rowCount][colCount] = 0x00;
    }

    frameBuffer = 1;
}

__inline void setPixel(const int x, const int y) {
    assert(x < 128); assert( x >= 0);
    assert(y < 64); assert( y >= 0);

    int page = y / 8;
    int pix = y % 8;
    dogmBuffer[page][x] |= (1 << pix);
}

__inline void clearPixel(const int x, const int y) {
    assert(x < 128); assert( x >= 0);
    assert(y < 64); assert( y >= 0);

    int page = y / 8;
    int pix = y % 8;
    dogmBuffer[page][x] &= ~(0x1 << pix);
}

void loadBitmap( unsigned char* bitmap,
        unsigned int columnL, unsigned int rowL,
        unsigned int width, unsigned int height)
{
    unsigned int x, y, _bit;

    y = 0;
    while( y < height ) {
        for( x = 0; x < width; x++ ) {
            for( _bit = 0; _bit < 8; _bit++ ) {
                if(bitmap[x] & (1 << (7 - _bit)))
                    setPixel( x + columnL, y + _bit + rowL );
            }
        }
        y++;
    }
}

void clearBitmap( unsigned char* bitmap,
        unsigned int columnL, unsigned int rowL,
        unsigned int width, unsigned int height)
{
    unsigned int x, y, _bit;

    y = 0;
    while( y < height ) {
        for( x = 0; x < width; x++ ) {
            for( _bit = 0; _bit < 8; _bit++ ) {
                if(bitmap[x] & (1 << (7 - _bit)))
                    clearPixel( x + columnL, y + _bit + rowL );
            }
        }
        y++;
    }
}