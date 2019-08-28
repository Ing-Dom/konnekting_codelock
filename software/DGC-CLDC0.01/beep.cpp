#include "beep.h"

Beep::Beep(unsigned int pin)
{
  m_pin = pin;
}

void Beep::Setup()
{
  pinMode(m_pin, OUTPUT);
}

void Beep::SingleBeep(unsigned int duration_ms)
{
  digitalWrite(m_pin, HIGH);
  m_stop1 = millis() + duration_ms;
  m_start2 = m_stop2 = 0;
}

void Beep::DoubleBeep(unsigned int duration_beep1_ms, unsigned int duration_pause1_ms, unsigned int duration_beep2_ms)
{
  digitalWrite(m_pin, HIGH);
  unsigned long current_ms = millis();
  m_stop1 = current_ms + duration_beep1_ms;
  m_start2 = current_ms + duration_beep1_ms + duration_pause1_ms;
  m_stop2 = current_ms + duration_beep1_ms + duration_pause1_ms + duration_beep2_ms;
}

void Beep::Cyclic()
{
  unsigned long current_ms = millis();
  if(current_ms >= m_stop1 && m_stop1 != 0)
    digitalWrite(m_pin, LOW);
  if(current_ms >= m_start2 && m_start2 != 0)
    digitalWrite(m_pin, HIGH);
  if(current_ms >= m_stop2 && m_stop2 != 0)
    digitalWrite(m_pin, LOW);
}