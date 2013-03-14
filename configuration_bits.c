/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

 #include <p24FJ64GB002.h>

/******************************************************************************/
/* Configuration Bits                                                         */
/*                                                                            */
/* This is not all available configuration bits for all PIC24 devices.        */
/* Refer to the PIC24 device specific .h file in the compiler                 */
/* support\PIC24x\h (x=F,H,E) directory for complete options specific to the  */
/* selected device.  For additional information about what the hardware       */
/* configurations mean in terms of device operation, refer to the device      */
/* datasheet 'Special Features' chapter.                                      */
/*                                                                            */
/******************************************************************************/

/* DONE : Fill in your configuration bits here.  The general style is below:    */
#if 0
// DONE Config settings !!Warning epic fail if mofified incorrectly!!
// Config values incase of a standalone version without the USB HID bootloader.
// Ask : Ferry if incorrectly modified

#ifdef __PIC24FJ64GB002__ //Defined by MPLAB when using 24FJ256GB110 device
        _CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
        _CONFIG2(POSCMOD_NONE & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_ON)
        _CONFIG3(WPFP_WPFP0 & SOSCSEL_SOSC & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
        _CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_SOSC & DSBOREN_OFF & DSWDTEN_OFF)
#endif

#endif

#if 0

/* Selects internal oscillator with no switching */
_FOSCSEL(FNOSC_FRC & IESO_OFF);

/* Disables clock switching and selects pri osc of HS with OSCIO clock output */
_FOSC(FCKSM_CSECME & OSCIOFNC_ON & POSCMD_HS);

/* Turns off JTAG and selects debug channel */
_FICD(JTAGEN_OFF & ICS_PGD1);

#endif
