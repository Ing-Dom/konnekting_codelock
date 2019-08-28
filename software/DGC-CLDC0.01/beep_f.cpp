#include "beep_f.h"

Beep_F::Beep_F(unsigned int pin)
{
  m_pin = pin;
}

void Beep_F::Setup()
{
  pinMode(m_pin, OUTPUT);
}

void Beep_F::SingleBeep(unsigned int duration_ms)
{
  unsigned long current_ms = millis();
  m_start1 = current_ms;
  m_stop1 = current_ms + duration_ms;
  m_start2 = m_stop2 = 0;
}

void Beep_F::DoubleBeep(unsigned int duration_beep1_ms, unsigned int duration_pause1_ms, unsigned int duration_beep2_ms)
{
  digitalWrite(m_pin, HIGH);
  unsigned long current_ms = millis();
  m_stop1 = current_ms + duration_beep1_ms;
  m_start2 = current_ms + duration_beep1_ms + duration_pause1_ms;
  m_stop2 = current_ms + duration_beep1_ms + duration_pause1_ms + duration_beep2_ms;
}

void Beep_F::Cyclic()
{
  unsigned long current_ms = millis();
  if(current_ms >= m_start1 && current_ms < m_stop1 && m_start1 != 0)
  {
    digitalWrite(m_pin, m_toggle);
    m_toggle = !m_toggle;
  }
  else if(current_ms >= m_start2 && current_ms < m_stop2 && m_start2 != 0)
  {
    digitalWrite(m_pin, m_toggle);
    m_toggle = !m_toggle;
  }
}