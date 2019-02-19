#include "Motorlock.h"

Motorlock::Motorlock(Beep *a_open, Beep *a_lock, Beep *a_unlock)
{
	m_open = a_open;
	m_lock = a_lock;
	m_unlock = a_unlock;
}

void Motorlock::Open()
{
	m_open->SingleBeep(MOTORLOCK_EMULATED_KEYPRESS_TIME);
}

void Motorlock::Lock()
{
	m_lock->SingleBeep(MOTORLOCK_EMULATED_KEYPRESS_TIME);
}

void Motorlock::Unlock()
{
	m_unlock->SingleBeep(MOTORLOCK_EMULATED_KEYPRESS_TIME);
}
