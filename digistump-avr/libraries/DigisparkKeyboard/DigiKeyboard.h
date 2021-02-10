/*
 * Based on Obdev's AVRUSB code and under the same license.
 *
 * TODO: Make a proper file header. :-)
 * Modified for Digispark by Digistump
 */
#ifndef __DigiKeyboard_h__
#define __DigiKeyboard_h__

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#include "usbdrv.h"
#include "keylayouts.h"

typedef uint8_t byte;

#define TEST_STRING "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890 !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"

#define BUFFER_SIZE 2 // Minimum of 2: 1 for modifiers + 1 for keystroke

static uchar idleRate;           // in 4 ms units

/* We use a simplifed keyboard report descriptor which does not support the
 * boot protocol. We don't allow setting status LEDs and but we do allow
 * simultaneous key presses.
 * The report descriptor has been created with usb.org's "HID Descriptor Tool"
 * which can be downloaded from http://www.usb.org/developers/hidpage/.
 * Redundant entries (such as LOGICAL_MINIMUM and USAGE_PAGE) have been omitted
 * for the second INPUT item.
 */
const PROGMEM uchar usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = { /* USB report descriptor */
0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
        0x09, 0x06,                    // USAGE (Keyboard)
        0xa1, 0x01,                    // COLLECTION (Application)
        0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
        0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
        0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
        0x75, 0x01,                    //   REPORT_SIZE (1)
        0x95, 0x08,                    //   REPORT_COUNT (8)
        0x81, 0x02,                    //   INPUT (Data,Var,Abs)
        0x95, 0x01,                    //   REPORT_COUNT (simultaneous keystrokes)
        0x75, 0x08,                    //   REPORT_SIZE (8)
        0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
        0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
        0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
        0xc0                           // END_COLLECTION
        };

#define MOD_CONTROL_LEFT    MODIFIERKEY_LEFT_CTRL
#define MOD_SHIFT_LEFT      MODIFIERKEY_LEFT_SHIFT
#define MOD_ALT_LEFT        MODIFIERKEY_LEFT_ALT
#define MOD_GUI_LEFT        MODIFIERKEY_LEFT_GUI
#define MOD_CONTROL_RIGHT   MODIFIERKEY_RIGHT_CTRL
#define MOD_SHIFT_RIGHT     MODIFIERKEY_RIGHT_SHIFT
#define MOD_ALT_RIGHT       MODIFIERKEY_RIGHT_ALT
#define MOD_GUI_RIGHT       MODIFIERKEY_RIGHT_GUI

class DigiKeyboardDevice: public Print {
public:
    DigiKeyboardDevice() {
        noInterrupts();
        usbDeviceDisconnect();
        _delay_ms(250);
        usbDeviceConnect();

        usbInit();

        interrupts();

        // TODO: Remove the next two lines once we fix
        //       missing first keystroke bug properly.
        memset(reportBuffer, 0, sizeof(reportBuffer));
        usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
    }

    void update() {
        usbPoll();
    }

    // delay while updating until we are finished delaying
    void delay(long milli) {
        unsigned long last = millis();
        while (milli > 0) {
            unsigned long now = millis();
            milli -= now - last;
            last = now;
            update();
        }
    }

    //sendKeyStroke: sends a key press AND release
    void sendKeyStroke(byte keyStroke) {
        sendKeyStroke(keyStroke, 0);
    }

    void enableLEDFeedback() {
        sUseFeedbackLed = true;
    }

    void disableLEDFeedback() {
        sUseFeedbackLed = false;
    }

    //sendKeyStroke: sends a key press AND release with modifiers
    void sendKeyStroke(byte keyStroke, byte modifiers) {
        sendKeyStroke(keyStroke, modifiers,false);
    }

    //sendKeyStroke: sends a key press AND release with modifiers
    void sendKeyStroke(byte keyStroke, byte modifiers, bool aUseFeedbackLed) {
        if(aUseFeedbackLed) {
            digitalWrite(LED_BUILTIN, HIGH);
        }
        sendKeyPress(keyStroke, modifiers);
        // This stops endlessly repeating keystrokes:
        sendKeyPress(0, 0);
        if(aUseFeedbackLed) {
            digitalWrite(LED_BUILTIN, LOW);
        }
    }

    //sendKeyPress: sends a key press only - no release
    //to release the key, send again with keyPress=0
    void sendKeyPress(byte keyPress) {
        sendKeyPress(keyPress, 0);
    }

    //sendKeyPress: sends a key press only, with modifiers - no release
    //to release the key, send again with keyPress=0
    void sendKeyPress(byte keyPress, byte modifiers) {
        while (!usbInterruptIsReady()) {
            // Note: We wait until we can send keyPress
            //       so we know the previous keyPress was
            //       sent.
            usbPoll();
            _delay_ms(5);
        }

        memset(reportBuffer, 0, sizeof(reportBuffer));

        reportBuffer[0] = modifiers;
        reportBuffer[1] = keyPress;

        usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
    }

    uint8_t keycode_to_modifier(KEYCODE_TYPE keycode) {
        uint8_t modifier = 0;

#ifdef SHIFT_MASK
        if (keycode & SHIFT_MASK)
            modifier |= MODIFIERKEY_SHIFT;
#endif
#ifdef ALTGR_MASK
        if (keycode & ALTGR_MASK)
            modifier |= MODIFIERKEY_RIGHT_ALT;
#endif
#ifdef RCTRL_MASK
        if (keycode & RCTRL_MASK) modifier |= MODIFIERKEY_RIGHT_CTRL;
#endif
        return modifier;
    }

    /*
     * Mask keycodes to ascii subset (+ a few F keys)
     */
    uint8_t keycode_to_key(KEYCODE_TYPE keycode) {
        uint8_t key = keycode;
        // the only valid ASCII code > 63
        if (keycode != KEY_NON_US_BS) {
            key = key & 0x3F;
        }
        return key;
    }

    /*
     * Convert ASCII to USB code
     */
    size_t write(uint8_t chr) {
        uint8_t data = 0;
        if (chr == 0x09) {
            data = (uint8_t) KEY_TAB;
        } else if (chr == 0x0a) {
            data = (uint8_t) KEY_ENTER;
        } else if (chr >= 0x20) {
            // read from mapping table
            data = pgm_read_byte_near(keycodes_ascii + (chr - 0x20));
        }
        if (data) {
            sendKeyStroke(keycode_to_key(data), keycode_to_modifier(data),sUseFeedbackLed);
        }
        return 1;
    }

    bool sUseFeedbackLed = false;
    uchar reportBuffer[2];    // buffer for HID reports [ 1 modifier byte + (len-1) key strokes]
    using Print::write;
};

DigiKeyboardDevice DigiKeyboard = DigiKeyboardDevice();

#ifdef __cplusplus
extern "C" {
#endif
// USB_PUBLIC uchar usbFunctionSetup
uchar usbFunctionSetup(uchar data[8]) {
    usbRequest_t *rq = (usbRequest_t *) ((void *) data);

    usbMsgPtr = DigiKeyboard.reportBuffer; //
    if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {
        /* class request type */

        if (rq->bRequest == USBRQ_HID_GET_REPORT) {
            /* wValue: ReportType (highbyte), ReportID (lowbyte) */

            /* we only have one report type, so don't look at wValue */
            // TODO: Ensure it's okay not to return anything here?
            return 0;

        } else if (rq->bRequest == USBRQ_HID_GET_IDLE) {
            //usbMsgPtr = &idleRate;
            //return 1;
            return 0;

        } else if (rq->bRequest == USBRQ_HID_SET_IDLE) {
            idleRate = rq->wValue.bytes[1];

        }
    } else {
        /* no vendor specific requests implemented */
    }

    return 0;
}
#ifdef __cplusplus
} // extern "C"
#endif

#endif // __DigiKeyboard_h__
