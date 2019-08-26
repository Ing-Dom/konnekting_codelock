#include "codelock.h"

Codelock::Codelock(Beep_F *a_beeper, unsigned long param_code,
                    unsigned short param_codelock_wrongcode_timeout1_no,
                    unsigned short param_codelock_wrongcode_timeout1_time,
                    unsigned short param_codelock_wrongcode_timeout2_no,
                    unsigned short param_codelock_wrongcode_timeout2_time,
                    unsigned short param_codelock_keypress_timeout_time)
{
	m_beeper = a_beeper;
	m_param_code = param_code;
	m_param_codelock_wrongcode_timeout1_no = param_codelock_wrongcode_timeout1_no;
	m_param_codelock_wrongcode_timeout1_time = param_codelock_wrongcode_timeout1_time;
	m_param_codelock_wrongcode_timeout2_no = param_codelock_wrongcode_timeout2_no;
	m_param_codelock_wrongcode_timeout2_time = param_codelock_wrongcode_timeout2_time;
	m_param_codelock_keypress_timeout_time = param_codelock_keypress_timeout_time;
  
}

void Codelock::addEventListener(void (*listener)(int))
{
	cmdEventListener = listener;
}

void Codelock::Cyclic()
{
	//ToDo
	//when state = 1 and no key has pressed for a while, then goto state 0
	if(m_insert_timeout_cntdown > 0)
	{
	 m_insert_timeout_cntdown--;
	 if(m_insert_timeout_cntdown == 0)
	 {
		 //cntdown reached 0
		 m_beeper->DoubleBeep(500,200,500); // Error-Beep
			WrongCode();
			m_state = 0;
			m_code = "";
			Debug.println(F("Timeout keypress"));
	 }
	}

	if(m_blocked_cntdown > 0)
	 m_blocked_cntdown--;
}

void Codelock::KeyPress(char key)
{
	Debug.println(F("Codelock.KeyPress %d"),key);
	int oldstate = m_state;
	if(m_blocked_cntdown > 0)
	{
		BeepError();
	}
	else if(m_state == 0 || m_state == 1)
	{
		m_code += key;
		m_insert_timeout_cntdown = TICKS_PER_SECOND * m_param_codelock_keypress_timeout_time;
		if(IsValidCode())
		{
			BeepCodeOK();
			ExecuteCode();
			m_state = 0;
			m_code = "";
			Debug.println(F("codelock %d=>%d"),oldstate,m_state);
		}
		else
		{
			if(m_code.length() >= CODE_LENGTH + 2)
			{
				BeepError();
				WrongCode();
				m_state = 0;
				m_code = "";
				Debug.println(F("codelock %d=>%d"),oldstate,m_state);
			}
			else
			{
				BeepKeypress();
				m_state = 1;
				Debug.println(F("codelock %d=>%d"),oldstate,m_state);
			}
		}
	}
}


bool Codelock::IsValidCode()
{
  unsigned long loc_insertedcode = 0;
  if(m_code.length() == CODE_LENGTH+2)
  {
		Debug.println(F("IsValidCode8"));
    if(m_code.charAt(0) >= '0' && m_code.charAt(0) <= '9' && m_code.charAt(1) == '#')
    {
			m_cmdno = m_code.charAt(0);
      m_code = m_code.substring(2,CODE_LENGTH+3);
			Debug.println(F("IsValidCode8 ok"));
    }
    else
    {
			Debug.println(F("IsValidCode8 false"));
      return false;
    }
  }
  
  if(m_code.length() == CODE_LENGTH)
  {
		Debug.println(F("IsValidCode codeToInt: %d"),m_code.toInt());
    for(int i=0;i<CODE_LENGTH;i++)
    {
      char c = m_code.charAt(i);
      if(c <= '0' && c >= '9')
    		return false;
    }
		loc_insertedcode = m_code.toInt();
		Debug.println(F("IsValidCode6 %d %d"),loc_insertedcode,m_param_code);
    if(loc_insertedcode == m_param_code)
      return true;
  }
  return false;
}

void Codelock::ExecuteCode()
{
	Debug.println("Execute Code");
	if(m_cmdno > 0)
	{
		if(cmdEventListener!=NULL)
		{
			cmdEventListener(m_cmdno - '0');
		}
	}
	else
	{
		if(cmdEventListener!=NULL)
		{
			cmdEventListener(10);
		}
	}
	m_no_wrong_codes = 0;
	m_insert_timeout_cntdown = 0;
	m_cmdno = 0;
}

void Codelock::WrongCode()
{
	Debug.println("Wrong Code");
	if(cmdEventListener!=NULL)
	{
		cmdEventListener(-1);
	}
	m_no_wrong_codes++;
	m_insert_timeout_cntdown = 0;

	if(m_no_wrong_codes > 5)
		m_blocked_cntdown = TICKS_PER_SECOND * 60 * m_param_codelock_wrongcode_timeout2_time;
	else if(m_no_wrong_codes > 3)
		m_blocked_cntdown = TICKS_PER_SECOND * m_param_codelock_wrongcode_timeout1_time;
}

void Codelock::BeepKeypress()
{
	m_beeper->SingleBeep(BEEP_LENGTH_KEYPRESS);
}

void Codelock::BeepCodeOK()
{
	m_beeper->SingleBeep(1000);
}

void Codelock::BeepError()
{
	m_beeper->DoubleBeep(500,200,500);
}
