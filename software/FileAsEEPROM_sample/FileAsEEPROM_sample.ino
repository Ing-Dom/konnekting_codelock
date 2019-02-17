#include "FileAsEEPROM.h"

void setup() {

  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("FileAsEEPROM example");

  Serial.print("readMemory on idx 0: ");
  int a = readMemory(0);
  Serial.println(a);

  Serial.println("update memory on idx 0 to 66 ");
  updateMemory(0,67);

  Serial.print("readMemory on idx 0: ");
  a = readMemory(0);
  Serial.println(a);

  commitMemory();
}

void loop() {
  delay(5000);
Serial.print("readMemory on idx 0: ");
  int a = readMemory(0);
  Serial.println(a);
}


//FlashStorage
int readMemory(int index)
{
    Serial.print("FLASH read on index: ");
    Serial.println(index);
    return FileEEPROM.read(index);
}
void writeMemory(int index, int val)
{
    Serial.print("FLASH write value x on index y: ");
    Serial.print(val);
    Serial.print(" ");
    Serial.println(index);
    FileEEPROM.write(index, val);
}
void updateMemory(int index, int val)
{
    Serial.println("FLASH update");
    if (readMemory(index) != val) {
        writeMemory(index, val);
    }
}
void commitMemory()
{
    Serial.println("FLASH commit");
    FileEEPROM.commit();
}
