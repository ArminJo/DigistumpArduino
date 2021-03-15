/* Name: usbboardconfig.h
 * Board CPU specific configurations for the used USB pins
 */

#ifndef __usbboardconfig_h_included__
#define __usbboardconfig_h_included__

/*
General Description:
This file is an example configuration (with inline documentation) for the USB
driver. It configures V-USB for USB D+ connected to Port D bit 2 (which is
also hardware interrupt 0 on many devices) and USB D- to Port D bit 4. You may
wire the lines to any other port, as long as D+ is also wired to INT0 (or any
other hardware interrupt, as long as it is the highest level interrupt, see
section at the end of this file).
*/

/* ---------------------------- Hardware Config ---------------------------- */

#if defined (__AVR_ATtiny44__) || defined (__AVR_ATtiny84__)
#define USB_CFG_IOPORTNAME      B
/* This is the port where the USB bus is connected. When you configure it to
 * "B", the registers PORTB, PINB and DDRB will be used.
 */
 
#define USB_CFG_DMINUS_BIT      1
/* This is the bit number in USB_CFG_IOPORT where the USB D- line is connected.
 * This may be any bit in the port.
 * USB- has a 1.5k pullup resistor to indicate a low-speed device.
 */
 
#define USB_CFG_DPLUS_BIT       2
/* This is the bit number in USB_CFG_IOPORT where the USB D+ line is connected.
 * This may be any bit in the port. Please note that D+ must also be connected
 * to interrupt pin -preferably INT0- [You can also use other interrupts, see section
 * "Optional MCU Description" below, or you can connect D- to the interrupt, as
 * it is required if you use the USB_COUNT_SOF feature. If you use D- for the
 * interrupt, the USB interrupt will also be triggered at Start-Of-Frame
 * markers every millisecond.] 
  */
  
#elif defined (__AVR_ATtiny45__) || defined (__AVR_ATtiny85__)
#define USB_CFG_IOPORTNAME      B
#define USB_CFG_DMINUS_BIT      3
#define USB_CFG_DPLUS_BIT       4

#elif defined (__AVR_ATtiny48__) || defined (__AVR_ATtiny88__)
#define USB_CFG_IOPORTNAME      D
#define USB_CFG_DMINUS_BIT      1
#define USB_CFG_DPLUS_BIT       2

#elif defined (__AVR_ATtiny87__) || defined (__AVR_ATtiny167__)
#define USB_CFG_IOPORTNAME      B
#define USB_CFG_DMINUS_BIT      3
#define USB_CFG_DPLUS_BIT       6

#elif defined (__AVR_ATtiny461__) || defined (__AVR_ATtiny861__)
#define USB_CFG_IOPORTNAME      B
#define USB_CFG_DMINUS_BIT      5
#define USB_CFG_DPLUS_BIT       6
#else
/*	ATtiny2313, ATmega8/168	*/
#define USB_CFG_IOPORTNAME      D
#define USB_CFG_DMINUS_BIT      3
#define USB_CFG_DPLUS_BIT       2
#endif

/* ----------------------- Optional Hardware Config ------------------------ */

//#define USB_CFG_PULLUP_IOPORTNAME   D
/* If you connect the 1.5k pullup resistor from D- to a port pin instead of
 * V+, you can connect and disconnect the device from firmware by calling
 * the macros usbDeviceConnect() and usbDeviceDisconnect() (see usbdrv.h).
 * This constant defines the port on which the pullup resistor is connected.
 */
//#define USB_CFG_PULLUP_BIT          5
/* This constant defines the bit number in USB_CFG_PULLUP_IOPORT (defined
 * above) where the 1.5k pullup resistor is connected. See description
 * above for details.
 */


/* ----------------------- Optional MCU Description ------------------------ */

/* The following configurations have working defaults in usbdrv.h. You
 * usually don't need to set them explicitly. Only if you want to run
 * the driver on a device which is not yet supported or with a compiler
 * which is not fully supported (such as IAR C) or if you use a differnt
 * interrupt than INT0, you may have to define some of these.
 */
/* #define USB_INTR_CFG            MCUCR */
/* #define USB_INTR_CFG_SET        ((1 << ISC00) | (1 << ISC01)) */
/* #define USB_INTR_CFG_CLR        0 */
/* #define USB_INTR_ENABLE         GIMSK */
/* #define USB_INTR_ENABLE_BIT     INT0 */
/* #define USB_INTR_PENDING        GIFR */
/* #define USB_INTR_PENDING_BIT    INTF0 */
/* #define USB_INTR_VECTOR         INT0_vect */

#ifndef INT0_vect
#define INT0_vect               _VECTOR(1)
#endif

/*
 * PCINTS are used here, because they are more versatile
 */
 
#if defined (__AVR_ATtiny45__) || defined (__AVR_ATtiny85__) 
#define USB_INTR_CFG            PCMSK // Pin interrupt enable register
#define USB_INTR_CFG_SET        (1 << USB_CFG_DPLUS_BIT) // Mask for pin in pin interrupt enable register PCMSK to be set on usbInit
#define USB_INTR_CFG_CLR        0 // Mask for pin in pin interrupt enable register PCMSK to be cleared on usbInit. 0 = no clear
#define USB_INTR_ENABLE         GIMSK // Global interrupt enable register
#define USB_INTR_ENABLE_BIT     PCIE  // Bit position in global interrupt enable register
#define USB_INTR_PENDING        GIFR  // Register to read interrupt flag
#define USB_INTR_PENDING_BIT    PCIF  // Bit position in register to read interrupt flag
#define USB_INTR_VECTOR         PCINT0_vect

#elif defined (__AVR_ATtiny48__) || defined (__AVR_ATtiny88__)
#define USB_INTR_CFG            PCMSK2 // Pin interrupt enable register
#define USB_INTR_CFG_SET        (1 << USB_CFG_DPLUS_BIT) // Mask for pin in pin interrupt enable register PCMSK to be set on usbInit
#define USB_INTR_CFG_CLR        0 // Mask for pin in pin interrupt enable register PCMSK to be cleared on usbInit. 0 = no clear
#define USB_INTR_ENABLE         PCICR // Global interrupt enable register
#define USB_INTR_ENABLE_BIT     PCIE2 // Bit position in global interrupt enable register
#define USB_INTR_PENDING        PCIFR // Register to read interrupt flag
#define USB_INTR_PENDING_BIT    PCIF2 // Bit position in register to read interrupt flag
#define USB_INTR_VECTOR         PCINT2_vect

#elif defined (__AVR_ATtiny87__) || defined (__AVR_ATtiny167__)
#define USB_INTR_CFG            PCMSK1
#define USB_INTR_CFG_SET        (1 << USB_CFG_DPLUS_BIT)
#define USB_INTR_CFG_CLR        0
#define USB_INTR_ENABLE         PCICR
#define USB_INTR_ENABLE_BIT     PCIE1
#define USB_INTR_PENDING        PCIFR
#define USB_INTR_PENDING_BIT    PCIF1
#define USB_INTR_VECTOR         PCINT1_vect
#endif

/*
 * The next lines are extracted from usbdrv.h
 * The default for USB_INTR_VECTOR is set in usbdrvasm.S :-(
 */
/* ----- Try to find default registers and bits responsible for USB interrupt ----- */

#ifndef USB_INTR_CFG    /* allow user to override our default */
#   if defined  EICRA
#       define USB_INTR_CFG EICRA
#   else
#       define USB_INTR_CFG MCUCR
#   endif
/* included here since you can not use USB_COUNT_SOF or USB_SOF_HOOK with pin change interrupts, you must use INT0! */
/* This relies on the settings of USB_COUNT_SOF and USB_SOF_HOOK, so this file must be included after these defines */
# ifndef USB_INTR_CFG_SET    /* allow user to override our default */
#   if defined(USB_COUNT_SOF) || defined(USB_SOF_HOOK)
#       define USB_INTR_CFG_SET (1 << ISC01)                    /* cfg for falling edge */
        /* If any SOF logic is used, the interrupt must be wired to D- where
         * we better trigger on falling edge
         */
#   elif USB_INTR_CFG == MCUCR || USB_INTR_CFG == EICRA
#       define USB_INTR_CFG_SET ((1 << ISC00) | (1 << ISC01))   /* cfg for rising edge */
#   endif
# endif
#endif

#ifndef USB_INTR_CFG_CLR    /* allow user to override our default */
#   define USB_INTR_CFG_CLR 0    /* no bits to clear */
#endif

#ifndef USB_INTR_ENABLE     /* allow user to override our default */
#   if defined GIMSK
#       define USB_INTR_ENABLE  GIMSK
#   elif defined EIMSK
#       define USB_INTR_ENABLE  EIMSK
#   else
#       define USB_INTR_ENABLE  GICR
#   endif
#endif

#ifndef USB_INTR_ENABLE_BIT /* allow user to override our default */
#   define USB_INTR_ENABLE_BIT  INT0
#endif

#ifndef USB_INTR_PENDING    /* allow user to override our default */
#   if defined  EIFR
#       define USB_INTR_PENDING EIFR
#   else
#       define USB_INTR_PENDING GIFR
#   endif
#endif

#ifndef USB_INTR_PENDING_BIT    /* allow user to override our default */
#   define USB_INTR_PENDING_BIT INTF0
#endif

/*
The defines above don't work for the following chips
at90c8534: no ISC0?, no PORTB, can't find a data sheet
at86rf401: no PORTB, no MCUCR etc, low clock rate
atmega103: no ISC0? (maybe omission in header, can't find data sheet)
atmega603: not defined in avr-libc
at43usb320, at43usb355, at76c711: have USB anyway
at94k: is different...

at90s1200, attiny11, attiny12, attiny15, attiny28: these have no RAM
*/

#endif /* __usbboardconfig_h_included__ */
