#pragma once
#include <KonnektingDevice.h>
#include "config.h"
#include <Key.h>
#include <Keypad.h>
#include "beep.h"

#define TICKS_PER_SECOND 40

class Codelock
{
	//members
	private: int m_state = 0;
	private: String m_code = "";
	private: char m_cmdno = 0;
  private: Beep *m_beeper;
  private: unsigned long m_param_code = 0;
	private: int m_no_wrong_codes = 0;
	private: unsigned long m_blocked_cntdown = 0;
	private: unsigned long m_insert_timeout_cntdown = 0;

	//constructors
	public: Codelock(Beep *a_beeper, unsigned long param_code);

	//functions
	public: void Cyclic();
  public: void KeyPress(char key);

  public: void addEventListener(void (*listener)(int));

  private: void (*cmdEventListener)(int);
	

	
	private: bool IsValidCode();

	private: void ExecuteCode();

	private: void WrongCode();
};
