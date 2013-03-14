#include <p24FJ64GB002.h>
#include "DogM.h"
#include "../emAssert.h"

#define 	ST7565R_SERIAL_INTERFACE 0x00
#define 	ST7565R_CMD_DISPLAY_ON   0xAF
#define 	ST7565R_CMD_DISPLAY_OFF   0xAE
#define 	ST7565R_CMD_START_LINE_SET(line)   (0x40 | (line))
#define 	ST7565R_CMD_PAGE_ADDRESS_SET(page)   (0xB0 | (page))
#define 	ST7565R_CMD_COLUMN_ADDRESS_SET_MSB(column)   (0x10 | (column))
#define 	ST7565R_CMD_COLUMN_ADDRESS_SET_LSB(column)   (0x00 | (column))
#define 	ST7565R_CMD_ADC_NORMAL   0xA0
#define 	ST7565R_CMD_ADC_REVERSE   0xA1
#define 	ST7565R_CMD_DISPLAY_NORMAL   0xA6
#define 	ST7565R_CMD_DISPLAY_REVERSE   0xA7
#define 	ST7565R_CMD_DISPLAY_ALL_POINTS_OFF   0xA4
#define 	ST7565R_CMD_DISPLAY_ALL_POINTS_ON   0xA5
#define 	ST7565R_CMD_LCD_BIAS_1_DIV_5_DUTY33   0xA1
#define 	ST7565R_CMD_LCD_BIAS_1_DIV_6_DUTY33   0xA2
#define 	ST7565R_CMD_NORMAL_SCAN_DIRECTION   0xC0
#define 	ST7565R_CMD_REVERSE_SCAN_DIRECTION   0xC8
#define 	ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_0   0x20
#define 	ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_1   0x21
#define 	ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_2   0x22
#define 	ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_3   0x23
#define 	ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_4   0x24
#define 	ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_5   0x25
#define 	ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_6   0x26
#define 	ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_7   0x27
#define 	ST7565R_CMD_POWER_CTRL_ALL_ON   0x2F
#define 	ST7565R_CMD_SLEEP_MODE   0xAC
#define 	ST7565R_CMD_NORMAL_MODE   0xAD
#define 	ST7565R_CMD_RESET   0xE2
#define 	ST7565R_CMD_NOP   0xE3
#define 	ST7565R_CMD_ELECTRONIC_VOLUME_MODE_SET   0x81
#define 	ST7565R_CMD_ELECTRONIC_VOLUME(volume)   (0x3F & (~volume))
#define 	ST7565R_CMD_BOOSTER_RATIO_SET   0xF8
#define 	ST7565R_CMD_BOOSTER_RATIO_2X_3X_4X   0x00
#define 	ST7565R_CMD_BOOSTER_RATIO_5X   0x01
#define 	ST7565R_CMD_BOOSTER_RATIO_6X   0x03
#define 	ST7565R_CMD_STATUS_READ   0x00
#define 	ST7565R_CMD_END   0xEE
#define 	ST7565R_CMD_READ_MODIFY_WRITE   0xE0
#define		ST7565R_DISPLAY_CONTRAST_MIN  30
#define		ST7565R_DISPLAY_CONTRAST_MAX  40

#define ST7565R_A0_PIN		LATBbits.LATB13
#define ST7565R_A0_TRIS         TRISBbits.TRISB13

#define ST7565R_CS_PIN		LATBbits.LATB9
#define ST7565R_CS_TRIS         TRISbbits.TRISB9

#define ST7565R_CLK_PIN         LATBbits.LATB14
#define ST7565R_CLK_TRIS	TRISBbits.TRISB14

#define ST7565R_SDO_PIN 	LATBbits.LATB15
#define ST7565R_SDO_TRIS	TRISBbits.TRISB15

void mdog_Init(char con1, char con2) {
    ST7565R_A0_PIN = 0;
    ST7565R_CS_PIN = 1; // SS pin
    ST7565R_CLK_PIN = 0;
    SPI_cmd_send(0x40);
    SPI_cmd_send(0xA1);
    SPI_cmd_send(0xC0);
    SPI_cmd_send(0xA6);
    SPI_cmd_send(0xA2);
    SPI_cmd_send(0x2F);
    SPI_cmd_send(0xF8);
    SPI_cmd_send(0x00);
    SPI_cmd_send(0x27);
    //    SPI_cmd_send(0x81);
    //    SPI_cmd_send(0x16);
    SPI_cmd_send(con1);
    SPI_cmd_send(con2);
    SPI_cmd_send(0xAC);
    SPI_cmd_send(0x00);
    SPI_cmd_send(0xAF);
}

void mdog_spi_out(unsigned char data) {
    char i = 0;
    for (i = 0; i < 8; i++) {
        if (data & 0x80) // Test HIGH bit
            ST7565R_SDO_PIN = 0x1; // SET
        else
            ST7565R_SDO_PIN = 0x0; // CLEAR
        ST7565R_CLK_PIN = 1; // Clock goes HIGH
        data <<= 1; // NEXT bit
        ST7565R_CLK_PIN = 0; // CLOCK goes low
    }
}

void SPI_cmd_send(unsigned char CmdToSend) {
    // sending block start ============================================================================
    ST7565R_CLK_PIN = 0;
    ST7565R_A0_PIN = 0;
    ST7565R_CS_PIN = 0; // ss active
    mdog_spi_out(CmdToSend);
    ST7565R_CS_PIN = 1; // SS deactivated

}

void SPI_data_send(unsigned char dataToSend) {
    ST7565R_CLK_PIN = 0;
    ST7565R_A0_PIN = 1;
    ST7565R_CS_PIN = 0; // ss active
    mdog_spi_out(dataToSend);
    ST7565R_CS_PIN = 1; // SS deactivated
}

void clearDisplay(void) {
    char saveClockBit;
    char saveSDOBit;

    saveClockBit = ST7565R_CLK_PIN;
    saveSDOBit = ST7565R_SDO_PIN;

    unsigned char page = 0b10110000;
    unsigned char column = 0;
    st7565r_set_page_address(page); // call st7565r_set_page_address(unsigned char address) here !!
    st7565r_set_column_address(0);
    while (page < 0b10111000) {
        for (column = 0; column < 128; column++) {
            SPI_data_send(0x00);
        }
        page = page + 0b00000001;
        SPI_cmd_send(page);
        st7565r_set_column_address(0);
    }
    ST7565R_CLK_PIN = saveClockBit;
    ST7565R_SDO_PIN = saveSDOBit;
}

void drawScreen(unsigned char screenData[8][128], int rows, int colums) {
    int rowCount = 0;
    int colCount = 0;
    unsigned char page = 0b10110000;
    char saveClockBit;
    char saveSDOBit;

    saveClockBit = ST7565R_CLK_PIN;
    saveSDOBit = ST7565R_SDO_PIN;

    // Select first page
    SPI_cmd_send(page); // call st7565r_set_page_address(unsigned char address) here !!
    st7565r_set_column_address(0);
    rowCount = 0;
    //=================================================
    while (rowCount < rows) {
        for (colCount = 0; colCount < colums; colCount++) {
            SPI_data_send(screenData[rowCount][colCount]);
        }
        //=================================================
        page = page + 0b00000001;
        SPI_cmd_send(page);
        st7565r_set_column_address(0);
        rowCount++;
    }
    ST7565R_CLK_PIN = saveClockBit;
    ST7565R_SDO_PIN = saveSDOBit;

}

void updateScreen(unsigned char screenData[8][128],
        unsigned char rowL, unsigned char columnL,
        unsigned char rowR, unsigned char columnR)
{
    char saveClockBit;
    char saveSDOBit;

    unsigned char column = columnL;

    saveClockBit = ST7565R_CLK_PIN;
    saveSDOBit = ST7565R_SDO_PIN;

    while( rowL < rowR ) {
        st7565r_set_page_address(rowL);
        st7565r_set_column_address(columnL);
        for(column = columnL; column < columnR; column++) {
            //st7565r_set_column_address(column);
            SPI_data_send( screenData[rowL][column] );
        }
        rowL++;
    }


    ST7565R_CLK_PIN = saveClockBit;
    ST7565R_SDO_PIN = saveSDOBit;
}

void drawBitmap(unsigned char *romString, int size) {
    int donebitmapSize = 0;
    int byteAddress = 0;
    unsigned char column = 0;
    unsigned char page = 0b10110000;

    char saveClockBit;
    char saveSDOBit;

    saveClockBit = ST7565R_CLK_PIN;
    saveSDOBit = ST7565R_SDO_PIN;


    SPI_cmd_send(page); // call st7565r_set_page_address(unsigned char address) here !!
    st7565r_set_column_address(0);
    donebitmapSize = 0;
    //=================================================
    while (donebitmapSize < size) {
        for (column = 0; column < 128; column++) {
            SPI_data_send(romString[byteAddress]);
            byteAddress++;
        }
        //=================================================
        page = page + 0b00000001;
        SPI_cmd_send(page);
        st7565r_set_column_address(0);
        donebitmapSize++;
    }
    ST7565R_CLK_PIN = saveClockBit;
    ST7565R_SDO_PIN = saveSDOBit;

}

void writeChar(unsigned char *font_ptr, unsigned char pageAdd, unsigned char columnAdd, unsigned char Character) {
    int column = 0;
    int base = 0;
    char saveClockBit;
    char saveSDOBit;

    saveClockBit = ST7565R_CLK_PIN;
    saveSDOBit = ST7565R_SDO_PIN;


    base = Character - 32;
    base *= 7;

    st7565r_set_page_address(pageAdd);
    st7565r_set_column_address(columnAdd);

    for (column = 0; column < 7; column++) {
        SPI_data_send(font_ptr[base]);
        base++;
    }
    ST7565R_CLK_PIN = saveClockBit;
    ST7565R_SDO_PIN = saveSDOBit;

}

void writeString(unsigned char *font_ptr, unsigned char pageAdd, unsigned char columnAdd, char *string_ptr) {
    int num = 0, column = 0;

    while (string_ptr[num] != 0) {
        if ((columnAdd + 7) >= 127) {
            pageAdd++;
            columnAdd = 0;
        }
        writeChar(font_ptr, pageAdd, columnAdd, string_ptr[num++]);
        columnAdd += 7;
    }
}

// note that the next address functions receive bytes (8 bits)

void st7565r_set_column_address(unsigned char address) {
    address &= 0x7F; // ended with (01111111)
    SPI_cmd_send(ST7565R_CMD_COLUMN_ADDRESS_SET_MSB(address >> 4));
    SPI_cmd_send(ST7565R_CMD_COLUMN_ADDRESS_SET_LSB(address & 0x0F));
}

void st7565r_set_page_address(unsigned char address) {
    // I Make sure that the address is 3 bits (only 4 pages up to 0b00000100) before using this function
    // you should know your own number of pages
    // the way I know mine is as follows:
    // my res is 122*32, since pages are horizontal, and each is 8 bits wide, then 32/8 = 4 !
    address &= 0x07; // anded with 0b00000111
    SPI_cmd_send(ST7565R_CMD_PAGE_ADDRESS_SET(address));
}