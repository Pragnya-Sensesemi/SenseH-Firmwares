/*
   EEPROM Write

   Stores random values into the EEPROM.
   These values will stay in the EEPROM when the board is
   turned off and may be retrieved later by another sketch.
*/

#include "EEPROM.h"

#define FLASH_AREA2_START_ADDR  (0)



int addr = 0;
#define EEPROM_SIZE 64
void setup()
{
  Serial.begin(115200);
  Serial.println("start...");
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }

}

int flash_data = 0;

void loop()
{

  EEPROM.write(FLASH_AREA2_START_ADDR, 0x55);
  delay(100);
  EEPROM.commit();
delay(100);
  flash_data = (EEPROM.read(FLASH_AREA2_START_ADDR));

Serial.println("Flash Read ");
  if(flash_data == 0x55)
  {
    Serial.println("Flash Read Write working\n");
  }

Serial.print(flash_data,HEX);
  while(1){}
      
}
