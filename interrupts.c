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

/* TODO Add interrupt routine code here. */
#include "Dogm128x64/DogM.h"
#include "Dogm128x64/dogmBuffer.h"
#include "interrupts.h"
#include "game/game.h"

extern volatile ButtonDown button;

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
    IFS1bits.CNIF = 0;

    button.up = ~PORTAbits.RA0;
    button.down = ~PORTAbits.RA1;
    button.left = ~PORTAbits.RA2;
    button.right = ~PORTAbits.RA3;

}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    IFS0bits.T1IF = 0;

    if(frameBuffer > 3)
        return;


    gameMain();

    if(isGameOver())
        while(1);
        
    gameMain();

    if(isGameOver())
        while(1);
    
    frameBuffer++;
}