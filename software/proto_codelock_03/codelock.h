#pragma once
#include <KonnektingDevice.h>
#include "config.h"
#include <Key.h>
#include <Keypad.h>
#include "beep_f.h"

#define TICKS_PER_SECOND 40

class Codelock
{
	//members
	private: int m_state = 0;
	private: String m_code = "";
	private: char m_cmdno = 0;
  private: Beep_F *m_beeper;
  private: unsigned long m_param_code = 0;
  private: unsigned short m_param_codelock_wrongcode_timeout1_no = 0;
  private: unsigned short m_param_codelock_wrongcode_timeout1_time = 0;
  private: unsigned short m_param_codelock_wrongcode_timeout2_no = 0;
  private: unsigned short m_param_codelock_wrongcode_timeout2_time = 0;
  private: unsigned short m_param_codelock_keypress_timeout_time = 0;
	private: int m_no_wrong_codes = 0;
	private: unsigned long m_blocked_cntdown = 0;
	private: unsigned long m_insert_timeout_cntdown = 0;

	//constructors
	public: Codelock(Beep_F *a_beeper, unsigned long param_code,
                    unsigned short param_codelock_wrongcode_timeout1_no,
                    unsigned short param_codelock_wrongcode_timeout1_time,
                    unsigned short param_codelock_wrongcode_timeout2_no,
                    unsigned short param_codelock_wrongcode_timeout2_time,
                    unsigned short param_codelock_keypress_timeout_time);

	//functions
	public: void Cyclic();
  public: void KeyPress(char key);

  public: void addEventListener(void (*listener)(int));

  private: void (*cmdEventListener)(int);
	

	
	private: bool IsValidCode();

	private: void ExecuteCode();

	private: void WrongCode();

  private: void BeepKeypress();

  private: void BeepCodeOK();

  private: void BeepError();
};
