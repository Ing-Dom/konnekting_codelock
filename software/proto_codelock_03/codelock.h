//#include <KonnektingDevice.h>
#include "config.h"
#include <Key.h>
#include <Keypad.h>

class Codelock
{
	//members
	private: char myKey = 0;
	private: unsigned int keypresstimer = 0;
	private: int wrongcodetimer = 0;
	private: int state = 0;
	private: unsigned int current_ms = 0;
	private: unsigned int last_ms = 0;
	private: unsigned int elapsed_ms = 0;
	private: String code = "";
  private: Keypad *m_keypad;

	//constructors
	public: Codelock(Keypad *a_keypad);

	//functions
	public: void Cyclic();
	
	private: void GoToState0();
	private: void DoState0();
	private: void GoToState1();
	private: void DoState1();
	private: void GoToState2();
	private: void DoState2();
	
	private: bool IsValidCode();

	private: void ExecuteCode();
	
	private: void beep(int beepcode);

 private: char GetKey();
};
