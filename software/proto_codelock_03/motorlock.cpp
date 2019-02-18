#include "Motorlock.h"

Motorlock::Motorlock(Beep *a_open, Beep *a_lock, Beep *a_unlock)
{
	m_open = a_open;
	m_lock = a_lock;
	m_unlock = a_unlock;
}

void Motorlock::Open()
{
	m_open->SingleBeep(300);
}

void Motorlock::Lock()
{
	m_lock->SingleBeep(300);
}

void Motorlock::Unlock()
{
	m_unlock->SingleBeep(300);
}
