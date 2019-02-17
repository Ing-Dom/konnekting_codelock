#pragma once
#include <KonnektingDevice.h>
#include "config.h"
#include <Key.h>
#include <Keypad.h>
#include "beep.h"

class Codelock
{
	//members
	private: int m_state = 0;
	private: String m_code = "";
  private: Beep *m_beeper;
  private: unsigned long m_param_code = 0;

	//constructors
	public: Codelock(Beep *a_beeper, unsigned long param_code);

	//functions
	public: void Cyclic();
  public: void KeyPress(char key);

  public: void addEventListener(void (*listener)(int));

  private: void (*cmdEventListener)(int);
	

	
	private: bool IsValidCode();

	private: void ExecuteCode();
};
