char myKey = 0;
uint keypresstimer = 0;
int wrongcodetimer = 0;
int state = 0;
uint current_ms = 0;
uint last_ms = 0;
uint elapsed_ms = 0;
string code = "";

void main()
{
	while(1)
	{
		//timerhandling
		current_ms = get_ms();
		
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
			 state = DoState0();
			 break;
		  case 1:
			 state = DoState1();
			 break;
		}
		



	}
}

void GoToState0()
{
	switch(state)
	{
		case 1:
			beep(3);
		break;
		
		case 2:
			ExecuteCode(code);
		break;
	}	
	
	state = 1;
}


void DoState0()
{
	myKey = getKey();
	if(myKey != NO_KEY)
	{
		GoToState(1)
	}
}


void GoToState1()
{
	switch(state)
	{
		case 0:
			code = myKey;
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


void DoState1()
{
	if(IsValidCode(code))
	{
		GoToState2();
	}
	else if(keypresstimer == 0 || length(code) == MAX_CODE_LENGTH)
	{
		GoToState0();
	}
	else
	{	
		myKey = getKey();
		if(myKey != NO_KEY)
		{
			GoToState(1)
		}
	}
}


void GoToState2()
{
	switch(state)
	{
		case 1:
			beep(2);
		break;
	}	
	
	state = 1;
}


void DoState2()
{
	GoToState0();
}