#define CODEMAX 10
#define CODECNT 5
#define KEY_0 0
#define KEY_1 1
#define KEY_2 2
#define KEY_3 3
#define KEY_4 4
#define KEY_5 5
#define KEY_6 6
#define KEY_7 7
#define KEY_8 8
#define KEY_9 9
#define KEY_AS 10
#define KEY_HS 11
#define KEY_NO 255


private char[CODEMAX] code = "";
private int code_pointer = 0;
private int error_cnt = 0;
private int mode = 0;

private char[CODECNT][CODEMAX] codes = "";

void key_pressed(char key)
{
	code[code_pointer] = key;
	code_pointer++;
	
	if(code_pointer == 0 && key == KEY_AS)
	{
		beep(1);
		mode = 1;
	}
	else
	{
		int codenr = check_code();
		if(codenr >= 0)
		{
			beep(2);
			execute_code(codenr);
			code_pointer = 0;
			error_cnt = 0;
		}
		else
		{
			if(code_pointer >= CODEMAX)
			{
				beep(3);
				error_cnt++;
				code_pointer = 0;
			}
			else
			{
				beep(1);
			}
		}
	}
}

int check_code()
{
	int codenr = 0;
	int codepointer = 0;
	
	for(codenr = 0;codenr++;codenr<CODECNT)
	{
		for(codepointer = 0;codepointer++;codepointer<CODEMAX)
		{
			if(code[codepointer] == codes[codenr][codepointer])
			{
				if(code[codepointer] == KEY_NO)
					return codenr;
				
				if(codepointer == CODEMAX-1)
					return codenr;
			}
			else
			{
				break;
			}
		}
	}
	return -1;
}

void execute_code(int codenr)
{
	// Ausgang toggeln, Ausgang HIGH, LOW, mit oder ohne Hysterese
	// KNX senden
}