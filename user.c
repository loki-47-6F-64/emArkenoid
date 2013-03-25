/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__PIC24E__)
#include <p24Exxxx.h>
#elif defined (__PIC24F__)
//#include <p24Fxxxx.h>
#include <p24FJ64GB002.h>
#elif defined(__PIC24H__)
#include <p24Hxxxx.h>
#endif

#include "user.h"
//#include "emMalloc.h"
#include "DogM.h"
#include "emAssert.h"
#include "interrupts.h"            /* variables/params used by user.c */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

/* TODO Initialize User Ports/Peripherals/Project here */

extern ButtonDown button;

void initTimer() {
    // Set timer
    T1CON = 0x00; //Stops the Timer1 and reset control reg.
    TMR1 = 0x00; //Clear contents of the timer register
    PR1 = 0x2000; //Load the Period register with the value 0xFFFF
    IPC0bits.T1IP = 0x05; //Setup Timer1 interrupt for desired priority level

    IFS0bits.T1IF = 0; //Clear the Timer1 interrupt status flag
    IEC0bits.T1IE = 1; //Enable Timer1 interrupts
    T1CONbits.TCKPS = 2; //Set prescaler settings to 1:256
    T1CONbits.TON = 1; //Start Timer1
    //clock source set to the internal instruction cycle
}

void InitApp(void) {
    // Setup analog functionality and port direction
    AD1PCFGL = 0xFFFF; // Make analog pins digital

    // Initialize peripherals
    // set up I/O ports
    TRISB = 0x0000; // all pins as output
    LATB = 0x0; // all set to 0

    // CN interrupts
    CNEN1 = 0; /* Disable all CN */
    CNEN2 = 0;

    CNEN1bits.CN2IE = 1;
    CNEN1bits.CN3IE = 1;
    CNEN2bits.CN29IE = 1;
    CNEN2bits.CN30IE = 1;

    IPC4bits.CNIP0 = 1;
    IPC4bits.CNIP1 = 0;
    IPC4bits.CNIP2 = 0;

    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;

    // All buttons are up.
    button.state = 0x00;
}

void intToString(int val, char *buf, int size) {
    int tmp = val, x = 0;

    while (tmp) {
        tmp /= 10;
        x++;
    }
    assert(x < size);

    buf += x;

    *buf = '\0';
    while (val) {
        *(--buf) = (val - (val / 10)*10) + '0';
        val /= 10;
    }
}

void AssertFailed(const char* file, int line, const char* expression) {
    // max_int has 6 digits.
    char str[7];
    intToString(line, str, 7);

    clearDisplay();
    writeString(boldFont, 0x00, 0x00, "Assert Failed:");

    writeString(boldFont, 0x02, 0x00, "File:");
    writeString(boldFont, 0x02, FONT_WIDTH * 5 - 1, (char*) file);

    writeString(boldFont, 0x03, 0x00, "Line:");
    writeString(boldFont, 0x03, FONT_WIDTH * 5 - 1, str);

    writeString(boldFont, 0x04, 0x00, (char*) expression);

    while (1);
}