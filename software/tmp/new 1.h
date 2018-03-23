class statemachine_insert_code
{
	private int state = 0; // 0: start
	private char[16] code = "";
	private int code_pointer = 0;
	
	public statemachine_code()
	{
	
	}
	
	
	
	public void trigger_keyPress(char key)
	{
		switch(state)
		{
			case 0:
				state = 1;
				action_0_1(key);
			case 1:
				action_1_1(key);
			break;
		}
	}
	
	public void trigger_codematch()
	{
		switch(state)
		{
			case 1:
				state = 0;
				action_1_0();
			break;
		}
	}
	
	private void action_0_1(char key)
	{
		code[code_pointer] = key;
		code_pointer++;
		if(codematch)
		{
			trigger_codematch();
		}
	}
	
	private void action_1_1(char key)
	{
		code[code_pointer] = key;
		code_pointer++;
		if(codematch)
		{
			trigger_codematch();
		}
	}
	
	private void action_1_0()
	{
		beep(2);
		code_execute();
		code_pointer = 0;
	}
	
	private bool codematch()
	{
		// check if inserted code matches any valid code
		return false;
	}
	
	private void  code_execute()
	{
		
		
	}


}