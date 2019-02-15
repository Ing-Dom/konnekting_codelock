#include <Arduino.h>

class Beep
{
  //members
  private: unsigned int m_pin = 0;
  private: unsigned long m_stop1 = 0;
  private: unsigned long m_start2 = 0;
  private: unsigned long m_stop2 = 0;

  //constructors
  public: Beep(unsigned int pin);

  //functions
  public: void Cyclic();

  public: void SingleBeep(unsigned int duration_ms);

  public: void DoubleBeep(unsigned int duration_beep1_ms, unsigned int duration_pause1_ms, unsigned int duration_beep2_ms);

  public: void Setup();
};
