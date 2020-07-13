#ifndef Pins_Arduino_h
#define Pins_Arduino_h
// definitions for Chinese MH-ET LIVE Tiny88(16.0MHz) board
// pins 0 to 13 are equal.

#define ATTINYX8 1

#ifndef __AVR_ATtiny88__
#define __AVR_ATtiny88__
#endif

///////////////////////////////
// Additions from ATTiny core
#define USE_SOFTWARE_SPI 0
#define ADC_TEMPERATURE 8
#define TIMER_TO_USE_FOR_MILLIS                   0 //Must be timer 0!
/*
  Where to put the software serial? (Arduino Digital pin numbers)
*/
//WARNING, if using software, TX is on AIN0, RX is on AIN1. Comparator is favoured to use its interrupt for the RX pin.
#define USE_SOFTWARE_SERIAL           1
//Please define the port on which the analog comparator is found.
#define ANALOG_COMP_DDR               DDRD
#define ANALOG_COMP_PORT              PORTD
#define ANALOG_COMP_PIN               PIND
#define ANALOG_COMP_AIN0_BIT          6
#define ANALOG_COMP_AIN1_BIT          7
/*
  Analog reference bit masks.
*/
// AVCC used as analog reference
#define DEFAULT (1)
// Internal 1.1V voltage reference
#define INTERNAL (0)
#define INTERNAL1V1 INTERNAL
// END additions
////////////////////

// #define SERIAL_BUFFER_SIZE 16

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            26
#define NUM_ANALOG_INPUTS           8
#define analogInputToDigitalPin(p)  ((p == 3) ? 23 : (p == 5) ? 21 : (p < 13 && p > 5) ? p+14 : (p ==13) ? 24 : -1)

#define digitalPinHasPWM(p)         ((p) == 9 || (p) == 10)

#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)

static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

#define PIN_WIRE_SDA        (23)
#define PIN_WIRE_SCL        (24)

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

//Ax constants cannot be used for digitalRead/digitalWrite/analogWrite functions, only analogRead().
#define PIN_A0   (19)
#define PIN_A1   (20)
#define PIN_A2   (21)
#define PIN_A3   (22)
#define PIN_A4   (23)
#define PIN_A5   (24)
#define PIN_A6   (17)
#define PIN_A7   (18)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;

#define LED_BUILTIN 0

#define digitalPinToPCICR(p)    (&PCICR)
#define digitalPinToPCICRbit(p) ( ((p) <= 7) ? PCIE2 : ( ((p) <= 14) ? PCIE0 : ( ((p) <= 18) ? PCIE3 : PCIE1 ) ) )
#define digitalPinToPCMSK(p)    ( ((p) <= 7) ? (&PCMSK2) : ( ((p) <= 14) ? (&PCMSK0) : ( ((p) <= 18) ? (&PCMSK3) : (&PCMSK1) ) ) )
#define digitalPinToPCMSKbit(p) ( ((p) <= 7) ? (p) : (((p) <= 13) ? ((p) - 8) : (((p) == 14) ? 7 : (((p) <= 16) ? ((p) - 14) : (((p) <= 18) ? ((p) - 17) : (((p) == 25) ? 7 : ((p) - 19) ) ) ) ) ) )

#ifdef ARDUINO_MAIN

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] = 
{
	NOT_A_PORT,
	(uint16_t) &DDRA,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] = 
{
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] = 
{
	NOT_A_PORT,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = 
{
	PD, /* 0 */
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PB, /* 8 */
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PA,
	PA,  /* 16 */
	PA,
	PA,
	PC,
	PC,
	PC,
	PC,
	PC,
	PC,
	PC,
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = 
{
	_BV(0),  /* 0, port D */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0),  /* 8, port B */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(7),
	_BV(2),
	_BV(3),
	_BV(0),
	_BV(1),
	_BV(0),
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(7),
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = 
{
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER1A,
	TIMER1B,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
};

#endif

#endif
