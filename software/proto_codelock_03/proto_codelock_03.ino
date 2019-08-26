/*

ToDo:
hide CO 0-11 when keypad mode 0
Factory Mode (set IA ? or has already one)
*/



// Developed with Library Versions:
//
// KONNEKTING_Device_Library: 1.0.0-BETA4b
// Adafriut_Dotstar: 1.1.2
// Adafriut_SPIFlash: 1.0.8

#include <KonnektingDevice.h>
// include device related configuration code, created by "KONNEKTING CodeGenerator"
#include "kdevice_CodeLock_Door_Controller.h"
//#include <FlashAsEEPROM.h>
#include "FileAsEEPROM.h"
#include <Key.h>
#include <Keypad.h>
#include "codelock.h"
#include "config.h"
#include "timeslice.h"
#include "beep.h"
#include "beep_f.h"
#include "motorlock.h"
#include <Adafruit_DotStar.h>





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
#define PROG_BUTTON_PIN NONE

#define BEEP_PIN A2

#define OPEN_PIN MISO
#define LOCK_PIN 2
#define UNLOCK_PIN 9

//Use these pin definitions for the ItsyBitsy M0 Dotstar LED
#define DATAPIN    41
#define CLOCKPIN   40
#define NUMPIXELS   1

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
byte rowPins[rows] = {A4, A0, A5, A1}; //connect to the row pinouts of the keypad
byte colPins[cols] = {SCK, A3, MOSI}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

Beep_F g_beep = Beep_F(BEEP_PIN);
Beep g_open = Beep(OPEN_PIN);
Beep g_lock = Beep(LOCK_PIN);
Beep g_unlock = Beep(UNLOCK_PIN);
Codelock *g_codelock;
Motorlock *g_motorlock;
bool g_door_openclose = 0;
unsigned int g_door_openclose_cntdown = 0;
unsigned long g_progkey_pressed_ms = 0;

unsigned short param_device_mode; 
unsigned long param_code;
unsigned short param_default_cmd;
unsigned short param_cmd_out_mode[10];
unsigned short param_motorlock_onclose;
unsigned short param_motorlock_open_cmd;
unsigned short param_motorlock_lock_cmd;
unsigned short param_motorlock_unlock_cmd;
unsigned short param_codelock_wrongcode_timeout1_no;
unsigned short param_codelock_wrongcode_timeout1_time;
unsigned short param_codelock_wrongcode_timeout2_no;
unsigned short param_codelock_wrongcode_timeout2_time;
unsigned short param_codelock_keypress_timeout_time;

//Dotstar LED
Adafruit_DotStar px(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

// ################################################
// ### KONNEKTING Configuration
// ################################################

#define KNX_SERIAL Serial1 // Leonardo/Micro etc. use Serial1


//FlashStorage
byte readMemory(int index)
{
    Debug.println(F("FLASH read on index %d"),index);
    return FileEEPROM.read(index);
}
void writeMemory(int index, byte val)
{
    Debug.println(F("FLASH write value %d on index %d"),val, index);
    FileEEPROM.write(index, val);
}
void updateMemory(int index, byte val)
{
    Debug.println(F("FLASH update"));
    if (FileEEPROM.read(index) != val) {
        FileEEPROM.write(index, val);
    }
}
void commitMemory()
{
    Debug.println(F("FLASH commit"));
    FileEEPROM.commit();
}

// ################################################
// ### set ProgLED status
// ################################################
//this function is used to indicate programming mode.
//you can use LED, LCD display or what ever you want...
void progLed(bool state)
{
    digitalWrite(PROG_LED_PIN, state);
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
      if(Knx.read(COMOBJ_lock_open))
      {
        g_motorlock->Open();
      }
    }
    break;
    case COMOBJ_lock_unlock:
    {
      if(Knx.read(COMOBJ_lock_unlock)) // DPT1.009: 0=Open, 1=Close
      {
        g_motorlock->Lock();
      }
      else
      {
        g_motorlock->Unlock();
      }
    }
    break;
    case COMOBJ_door_input:
    {
      //detect rising edge 0->1 Open->Close DPT1.009
      if(Knx.read(COMOBJ_door_input) != g_door_openclose)
      {
        if(!g_door_openclose)
        {
          g_door_openclose_cntdown = ((unsigned int)(100 / T3_CYCLETIME)) * param_motorlock_onclose;
        }
        g_door_openclose = !g_door_openclose;
      }
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
  if(keypad.getState() == RELEASED)
  {
    #ifdef KDEBUG  
    //Debug.println(F("keyevent %d"),key);
    #endif
    if(key == PROGKEY && g_progkey_pressed_ms != 0 && g_progkey_pressed_ms + PROGMODEMS < millis())
    {
      px.setPixelColor(0, 100, 0, 0); // green
      px.show();
      g_beep.SingleBeep(BEEP_LENGTH_PROGMODE);
      Konnekting.toggleProgState();
      return;
    }


    Knx.write(COMOBJ_key_output, (unsigned short)key);
    if(param_device_mode == 1 || param_device_mode == 2)
      g_codelock->KeyPress(key);
    else if(param_device_mode == 0)
      g_beep.SingleBeep(BEEP_LENGTH_KEYPRESS);
  }
  else if(keypad.getState() == PRESSED && key == PROGKEY)
  {
    g_progkey_pressed_ms = millis();
  }
}

void codelockEvent(int cmd)
{
    Debug.println(F("Execute cmd %d"),cmd);

    if(cmd >= 0 && cmd <= 9)
    {
      ExecuteCodelockCmd(cmd);
    }
    else if(cmd == 10)
    {
      ExecuteCodelockCmd(param_default_cmd);
    }
    else if(cmd < 0)
    {
      Knx.write(COMOBJ_cmd_wrong, 1);
    }
}

void ExecuteCodelockCmd(int cmd)
{
  if(cmd >= 0 && cmd <= 9)
  {
    if(param_cmd_out_mode[cmd] == 1)
    {
      Knx.write(COMOBJ_cmd0_out+cmd, 1);
    }
    else if(param_cmd_out_mode[cmd] == 2)
    {
      Knx.write(COMOBJ_cmd0_out+cmd, 0);
    }
    else if(param_cmd_out_mode[cmd] == 3)
    {
      Knx.write(COMOBJ_cmd0_out+cmd, !Knx.read(COMOBJ_cmd0_out+cmd));
    }
    Knx.write(COMOBJ_cmd_all, cmd);
  }
  Debug.println(F("ExecuteCodelockCmd dev mode: %d %d %d"),param_device_mode,param_motorlock_open_cmd,cmd);
  if(param_device_mode == 2)
  {
    //Motorlock enabled in device mode

    if(param_motorlock_open_cmd == cmd)
    {
      g_motorlock->Open();
    }
    if(param_motorlock_lock_cmd == cmd)
    {
      g_motorlock->Lock();
    }
    if(param_motorlock_unlock_cmd == cmd)
    {
      g_motorlock->Unlock();
    }
  }
}

void setup()
{
  px.begin(); // Initialize pins for output
  px.show();  // Turn all LEDs off ASAP
  px.setPixelColor(0, 50, 0, 0); // red
  px.show();


  // debug related stuff
  #ifdef KDEBUG
  // Start debug serial with 9600 bauds
  DEBUGSERIAL.begin(9600);
  while (!DEBUGSERIAL)

  px.setPixelColor(0, 0, 0, 50); // blue
  px.show();

  // make debug serial port known to debug class
  // Means: KONNEKTING will use the same serial port for console debugging
  Debug.setPrintStream(&DEBUGSERIAL);
  #endif

  Konnekting.setMemoryReadFunc(&readMemory);
  Konnekting.setMemoryWriteFunc(&writeMemory);
  Konnekting.setMemoryUpdateFunc(&updateMemory);
  Konnekting.setMemoryCommitFunc(&commitMemory);


  g_beep.Setup();
  g_open.Setup();
  g_lock.Setup();
  g_unlock.Setup();

  keypad.addEventListener(keypadEvent); //add an event listener for the keypad


  // Initialize KNX enabled Arduino Board
    Konnekting.init(KNX_SERIAL,
                    &progLed,
                    MANUFACTURER_ID,
                    DEVICE_ID,
                    REVISION);
  
  if (!Konnekting.isFactorySetting())
  {
    param_device_mode = (unsigned short)Konnekting.getUINT8Param(PARAM_device_mode);
    param_code = (unsigned long)Konnekting.getUINT32Param(PARAM_code);
    param_default_cmd = (unsigned short)Konnekting.getUINT8Param(PARAM_default_cmd);
    for(int i=0;i<10;i++)
      param_cmd_out_mode[i] = (unsigned short)Konnekting.getUINT8Param(PARAM_cmd0_out_mode+i);
    param_motorlock_onclose = (unsigned short)Konnekting.getUINT8Param(PARAM_motorlock_onclose);
    param_motorlock_open_cmd = (unsigned short)Konnekting.getUINT8Param(PARAM_motorlock_open_cmd);
    param_motorlock_lock_cmd = (unsigned short)Konnekting.getUINT8Param(PARAM_motorlock_lock_cmd);
    param_motorlock_unlock_cmd = (unsigned short)Konnekting.getUINT8Param(PARAM_motorlock_unlock_cmd);
    param_codelock_wrongcode_timeout1_no = (unsigned short)Konnekting.getUINT8Param(PARAM_codelock_wrongcode_timeout1_no);
    param_codelock_wrongcode_timeout1_time = (unsigned short)Konnekting.getUINT8Param(PARAM_codelock_wrongcode_timeout1_time);
    param_codelock_wrongcode_timeout2_no = (unsigned short)Konnekting.getUINT8Param(PARAM_codelock_wrongcode_timeout2_no);
    param_codelock_wrongcode_timeout2_time = (unsigned short)Konnekting.getUINT8Param(PARAM_codelock_wrongcode_timeout2_time);
    param_codelock_keypress_timeout_time = (unsigned short)Konnekting.getUINT8Param(PARAM_codelock_keypress_timeout_time);


    
    g_codelock = new Codelock(&g_beep, param_code, param_codelock_wrongcode_timeout1_no, param_codelock_wrongcode_timeout1_time,
                              param_codelock_wrongcode_timeout2_no, param_codelock_wrongcode_timeout2_time,
                              param_codelock_keypress_timeout_time);
    g_motorlock = new Motorlock(&g_open, &g_lock, &g_unlock);

    g_codelock->addEventListener(codelockEvent);
  }
  else
  {
      px.setPixelColor(0, 0, 50, 0); // green
      px.show();
      writeMemory(0,  0x7F);
      writeMemory(1,  (byte)(0xFFFF >> 8)); // 15.15.255
      writeMemory(2,  (byte)(0xFFFF)); // 15.15.255
      commitMemory();
  }
  timeslice_setup();
  Debug.println(F("Setup is ready. go to loop..."));

}

void loop()
{
    Knx.task();
    timeslice_scheduler();

    if (Konnekting.isReadyForApplication())
    {
      
    }
}

void T1() // 1ms
{
  g_beep.Cyclic();
}
void T2() // 5ms
{
  keypad.getKey();
  g_open.Cyclic();
  g_lock.Cyclic();
  g_unlock.Cyclic();
}
void T3() // 25ms
{
  if(g_door_openclose_cntdown > 0)
  {
    g_door_openclose_cntdown--;
    if(g_door_openclose_cntdown == 0)
    {
      g_motorlock->Lock();
    }
  }
  g_codelock->Cyclic();
}
void T4() // 500ms
{
}
void T5() // 10000ms
{
  //Knx.write(COMOBJ_error_code, 0);
  //Debug.println(F("T5"));
}
