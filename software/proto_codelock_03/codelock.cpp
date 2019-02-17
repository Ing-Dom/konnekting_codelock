#include "codelock.h"

Codelock::Codelock(Beep *a_beeper, unsigned long param_code)
{
	m_beeper = a_beeper;
	m_param_code = param_code;
}

void Codelock::addEventListener(void (*listener)(int))
{
	cmdEventListener = listener;
}

void Codelock::Cyclic()
{

}

void Codelock::KeyPress(char key)
{
	Debug.println(F("Codelock.KeyPress %d"),key);
	int oldstate = m_state;
	if(m_state == 0 || m_state == 1)
	{
		m_code += key;
		if(IsValidCode())
		{
			m_beeper->SingleBeep(1000);
			ExecuteCode();
			m_state = 0;
			m_code = "";
			Debug.println(F("codelock %d=>%d"),oldstate,m_state);
		}
		else
		{
			if(m_code.length() >= CODE_LENGTH + 2)
			{
				m_beeper->DoubleBeep(500,200,500);
				m_state = 0;
				m_code = "";
				Debug.println(F("codelock %d=>%d"),oldstate,m_state);
			}
			else
			{
				m_beeper->SingleBeep(50);
				m_state = 1;
				Debug.println(F("codelock %d=>%d"),oldstate,m_state);
			}
		}
	}
}


bool Codelock::IsValidCode()
{
  //ToDo
  unsigned long loc_insertedcode = 0;
  if(m_code.length() == CODE_LENGTH+2)
  {
    if(m_code.charAt(0) >= '0' && m_code.charAt(0) <= '9' && m_code.charAt(1) == '#')
    {
      m_code = m_code.substring(2,CODE_LENGTH+1);
    }
    else
    {
      return false;
    }
  }
  
  if(m_code.length() == CODE_LENGTH)
  {
		Debug.println(F("IsValidCode code: %d"),m_code.toInt());
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
	if(m_code.charAt(1) == '#')
	{
		if(cmdEventListener!=NULL)
		{
			cmdEventListener(m_code.charAt(0) - '0');
		}
	}
	else
	{
		cmdEventListener(10);
	}
}

