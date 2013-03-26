#include <p24FJ64GB002.h>

#include "DogM.h"
#include "dogmBuffer.h"
#include "game/game.h"
#include "interrupts.h"
#include "emAssert.h"
#include "user.h"
#include "emMalloc.h"

//extern byte block[];
//extern size_t size_block;
// This is a stupid delay function, it is NOT very precize
//

// TODO: make delay_ms more precise

void delay_ms(unsigned int Time) {
    unsigned int i, j;
    for (i = 0; i <= Time; i++) {
        asm("nop");
        for (j = 0; j <= 1140; j++) //1ms
        {
            asm("nop");
            asm("nop");
        }
    }
}

int main(void) {
    char str[32];
    emInit();

    //emInit();
    // Init ap set all ports to digital and enables the int on pin change 
    // needed for the buttons/
    InitApp();

    // Set up the hardware of the display
    mdog_Init(0x81, 0x19);

    clearDisplay();

    // Initscreen clears a internal bitmap used
    // in drawScreen to send out to the display
    initBuffer();

    //assert( 1 != 1 );
    // Beware writeString will write directly to the display
    // the internal bitmap is not modified.

    // while(1);
    //writeString(boldFont, 0x1, 0x3, "-PIC24JF64GB002-");
    //writeString(boldFont, 0x2, 0x3, "-Hit the buttons.");
    //writeString(boldFont, 0x3, 0x3, "-Muhahahaha >:)");
    initGame();

    //clearBrick( &brick );
    // Toggle leds
    LATBbits.LATB14 = LATBbits.LATB15 = 0;

    initTimer();
    //assert( 0 != 0 );
    while (1) {
        if(frameBuffer) {
            frameBuffer = 0;

            updateScreen(dogmBuffer, 0, 0, 8, 128);
        }
    };
}
