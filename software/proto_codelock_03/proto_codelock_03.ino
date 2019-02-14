/*

ToDo:
//measeure keypad.getkey()

*/




#include <KonnektingDevice.h>
// include device related configuration code, created by "KONNEKTING CodeGenerator"
#include "kdevice_CodeLock_Door_Controller.h"
#include <FlashAsEEPROM.h>
#include <Key.h>
#include <Keypad.h>
#include "codelock.h"
#include "config.h"
#include "timeslice.h"

// ################################################
// ### DEBUG CONFIGURATION
// ################################################
#define KDEBUG // comment this line to disable DEBUG mode
#ifdef KDEBUG
#include <DebugUtil.h>
#endif

#define DEBUGSERIAL Serial


// ################################################
// ### IO Configuration
// ################################################
#define PROG_LED_PIN 13
#define PROG_BUTTON_PIN 7


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
byte rowPins[rows] = {9, 10, 11, 12}; //connect to the row pinouts of the keypad
byte colPins[cols] = {A5, A4, A3}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );



unsigned short param_device_mode; 
unsigned long param_code;
unsigned short param_default_cmd;
unsigned short param_cmd_out_mode[10];

// ################################################
// ### KONNEKTING Configuration
// ################################################

#define KNX_SERIAL Serial1 // Leonardo/Micro etc. use Serial1


//FlashStorage
int readMemory(int index)
{
    Debug.println(F("FLASH read on index %d"),index);
    return EEPROM.read(index);
}
void writeMemory(int index, int val)
{
    Debug.println(F("FLASH write value %d on index %d"),val, index);
    EEPROM.write(index, val);
}
void updateMemory(int index, int val)
{
    Debug.println(F("FLASH update"));
    if (EEPROM.read(index) != val) {
        EEPROM.write(index, val);
    }
}
void commitMemory()
{
    Debug.println(F("FLASH commit"));
    EEPROM.commit();
}

// ################################################
// ### KNX EVENT CALLBACK
// ################################################

void knxEvents(byte index)
{
  switch (index)
  {
    case COMOBJ_lock_open:
    {
    }
    break;
    case COMOBJ_lock_unlock:
    {
    }
    break;
    case COMOBJ_door_input:
    {
    }
    break;
    default:
    {
    }
    break;
  }
}

void keypadEvent(KeypadEvent key)
{
  if(keypad.getState() == PRESSED)
  {
    #ifdef KDEBUG  
    Debug.println(F("keyevent %d"),key);
    #endif
    Knx.write(COMOBJ_key_output, (unsigned short)key);
  }   
}

void setup()
{
  // debug related stuff
  #ifdef KDEBUG
  // Start debug serial with 9600 bauds
  DEBUGSERIAL.begin(9600);

  // make debug serial port known to debug class
  // Means: KONNEKTING will sue the same serial port for console debugging
  Debug.setPrintStream(&DEBUGSERIAL);
  #endif

  Konnekting.setMemoryReadFunc(&readMemory);
  Konnekting.setMemoryWriteFunc(&writeMemory);
  Konnekting.setMemoryUpdateFunc(&updateMemory);
  Konnekting.setMemoryCommitFunc(&commitMemory);

  pinMode(A0, INPUT_PULLUP);

  // Initialize KNX enabled Arduino Board
  Konnekting.init(KNX_SERIAL, PROG_BUTTON_PIN, PROG_LED_PIN, MANUFACTURER_ID, DEVICE_ID, REVISION);
  if (!Konnekting.isFactorySetting())
  {
    param_device_mode = (unsigned short)Konnekting.getUINT8Param(PARAM_device_mode);
    param_code = (unsigned long)Konnekting.getUINT32Param(PARAM_code);
    param_default_cmd = (unsigned short)Konnekting.getUINT8Param(PARAM_default_cmd);
    for(int i=0;i<10;i++)
      param_cmd_out_mode[i] = (unsigned short)Konnekting.getUINT8Param(PARAM_cmd0_out_mode+i);
    
    timeslice_setup();
    keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  }
  Debug.println(F("Setup is ready. go to loop..."));

}

void loop()
{
    Knx.task();
    
    if (Konnekting.isReadyForApplication())
    {
      keypad.getKey();
      timeslice_scheduler();
    }
}

void T1()
{}
void T2()
{}
void T3()
{}
void T4()
{
}
void T5()
{
  Knx.write(COMOBJ_error_code, digitalRead(A0));
  Debug.println(F("T5"));
}
