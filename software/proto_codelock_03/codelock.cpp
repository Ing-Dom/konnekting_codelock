#include "codelock.h"
#include "config.h"

Codelock::Codelock(Keypad *a_keypad)
{
	m_keypad = a_keypad;
}

void Codelock::Cyclic()
{
	//timerhandling
	current_ms = millis();
	
	if(current_ms >= last_ms)
	{
		elapsed_ms = current_ms - last_ms;
	}
	else
	{
		//overflow of ms counter has happend, handle this
		elapsed_ms = MAX_UINT - last_ms + current_ms;
	}
	
	if(keypresstimer > 0)
	{
		if(keypresstimer > elapsed_ms)
			keypresstimer = keypresstimer - elapsed_ms;
		else
			keypresstimer = 0;
	}
	
	
	last_ms = current_ms;
	
	
	switch(state)
	{
    case 0:
     DoState0();
     break;
    case 1:
     DoState1();
     break;
    case 2:
     DoState2();
     break;
	}
}

void Codelock::GoToState0()
{
	switch(state)
	{
		case 1:
			beep(3);
		break;
		
		case 2:
			//ExecuteCode(code); //ToDo
		break;
	}	
	
	state = 1;
}


void Codelock::DoState0()
{
	myKey = GetKey();
	if(myKey != NO_KEY)
	{
		GoToState1();
	}
}


void Codelock::GoToState1()
{
	switch(state)
	{
		case 0:
			code = String(myKey);
			beep(0);
			keypresstimer = KEYPRESSTIMEOUT;
		break;
		case 1:
			code += myKey;
			beep(0);
			keypresstimer = KEYPRESSTIMEOUT;
		break;
	}	
	
	state = 1;
}


void Codelock::DoState1()
{
	if(IsValidCode())
	{
		GoToState2();
	}
	else if(keypresstimer == 0 || code.length() == CODE_LENGTH)
	{
		GoToState0();
	}
	else
	{	
		myKey = GetKey();
		if(myKey != NO_KEY)
		{
			GoToState1();
		}
	}
}


void Codelock::GoToState2()
{
	switch(state)
	{
		case 1:
			beep(2);
		break;
	}	
	
	state = 1;
}


void Codelock::DoState2()
{
	GoToState0();
}

bool Codelock::IsValidCode()
{
  //ToDo
  unsigned long param_code = 0;
  unsigned long loc_insertedcode = 0;
  if(code.length() == CODE_LENGTH+2)
  {
    if(code.charAt(0) >= '0' && code.charAt(0) <= '9' && code.charAt(1) == '#')
    {
      code = code.substring(2,CODE_LENGTH+1);
    }
    else
    {
      return false;
    }
  }
  
  if(code.length() == CODE_LENGTH)
  {
    for(int i=0;i<CODE_LENGTH;i++)
    {
      char c = code.charAt(CODE_LENGTH);
      if(c >= '0' && c <= '9')
      {
        c = c - '0';
        loc_insertedcode += c * (10^(CODE_LENGTH-1-i));
      }
    }
    if(loc_insertedcode == param_code)
      return true;
  }
  return false;
}

void Codelock::ExecuteCode()
{
	
}
	
void Codelock::beep(int beepcode)
{
	
}

char Codelock::GetKey()
{
  return m_keypad->getKey();
}
