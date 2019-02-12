#include <KonnektingDevice.h>

// include device related configuration code, created by "KONNEKTING CodeGenerator"
#include "kdevice_CodeLock_Door_Controller.h"

#include <Key.h>
#include <Keypad.h>
#include "codelock.h"
#include "config.h"

// ################################################
// ### DEBUG CONFIGURATION
// ################################################
#define KDEBUG // comment this line to disable DEBUG mode
#ifdef KDEBUG
#include <DebugUtil.h>

// Get correct serial port for debugging
#ifdef __AVR_ATmega32U4__
// Leonardo/Micro/ProMicro use the USB serial port
#define DEBUGSERIAL Serial
#elif ESP8266
// ESP8266 use the 2nd serial port with TX only
#define DEBUGSERIAL Serial1
#else
// All other, (ATmega328P f.i.) use software serial
#include <SoftwareSerial.h>
SoftwareSerial softserial(11, 10); // RX, TX
#define DEBUGSERIAL softserial
#endif
// end of debugging defs
#endif

// ################################################
// ### KONNEKTING Configuration
// ################################################
#ifdef __AVR_ATmega328P__
#define KNX_SERIAL Serial // Nano/ProMini etc. use Serial
#elif ESP8266
#define KNX_SERIAL Serial // ESP8266 use Serial
#else
#define KNX_SERIAL Serial1 // Leonardo/Micro etc. use Serial1
#endif

// ################################################
// ### IO Configuration
// ################################################
#define PROG_LED_PIN 13
#define PROG_BUTTON_PIN 2

#define OUTPIN1 4
#define OUTPIN2 5
#define OUTPIN3 6




// ################################################
// ### Global variables, sketch related
// ################################################
const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[rows] = {17, 16, 15, 14}; //connect to the row pinouts of the keypad
byte colPins[cols] = {7, 8, 9}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

// Callback function to handle com objects updates

void knxEvents(byte index)
{
    switch(index)
    {
        case COMOBJ_cmd1_out:
            //Knx.read(COMOBJ_cmd1_out);
            break;
        case COMOBJ_out1:
            digitalWrite(OUTPIN1, Knx.read(COMOBJ_out1));
 #ifdef KDEBUG
    //Debug.println(F("set out1"),Knx.read(COMOBJ_out1));
 #endif
            break;

        default:
            break;
    }
}


void setup()
{

    // debug related stuff
#ifdef KDEBUG

    // Start debug serial with 9600 bauds
    DEBUGSERIAL.begin(9600);

#ifdef __AVR_ATmega32U4__
    // wait for serial port to connect. Needed for Leonardo/Micro/ProMicro only
    while (!DEBUGSERIAL)
#endif

    // make debug serial port known to debug class
    // Means: KONNEKTING will sue the same serial port for console debugging
    Debug.setPrintStream(&DEBUGSERIAL);
#endif

    pinMode(OUTPIN1, OUTPUT);
    pinMode(OUTPIN2, OUTPUT);
    pinMode(OUTPIN3, OUTPUT);
    digitalWrite(OUTPIN1, LOW);
    digitalWrite(OUTPIN2, LOW);
    digitalWrite(OUTPIN3, LOW);

    // Initialize KNX enabled Arduino Board
    Konnekting.init(KNX_SERIAL, PROG_BUTTON_PIN, PROG_LED_PIN, MANUFACTURER_ID, DEVICE_ID, REVISION);
    if (!Konnekting.isFactorySetting())
    {
      keypad.addEventListener(keypadEvent); //add an event listener for this keypad
    }
    Debug.println(F("Setup is ready. go to loop..."));
}

void loop()
{
    Knx.task();
    unsigned long currentTime = millis();
    
    // only do measurements and other sketch related stuff if not in programming mode
    if (Konnekting.isReadyForApplication())
    {
      char key = keypad.getKey();

      if (key != NO_KEY)
      {
#ifdef KDEBUG  
     Debug.println(F("key: %d"),key);
#endif
          Knx.write(COMOBJ_key_output, (unsigned short)key);         
      }
    }
}

void keypadEvent(KeypadEvent key)
{
  #ifdef KDEBUG  
     Debug.println(F("keyevent %d"),key);
#endif
}
