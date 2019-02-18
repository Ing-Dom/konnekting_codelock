#pragma once
#include <KonnektingDevice.h>
#include "config.h"
#include "beep.h"


class Motorlock
{
	//members
  private: Beep *m_open;
	private: Beep *m_lock;
	private: Beep *m_unlock;

	//constructors
	public: Motorlock(Beep *a_open, Beep *a_lock, Beep *a_unlock);

	//functions
  public: void Open();
	public: void Lock();
	public: void Unlock();
};
