//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int BT_Rx_buff[500];
int *ptr = BT_Rx_buff ;

int c;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("SSH-00-01"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  memset(BT_Rx_buff,0x00,sizeof(BT_Rx_buff));
}

int count = 0;

int Read_Frame(int Rx_data[]);
int Rx_len;

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
  
   Rx_len =  Read_Frame(BT_Rx_buff);

   for(int i=0;i< Rx_len;i++)
   {
       Serial.write(BT_Rx_buff[i]);
   }

   if(BT_Rx_buff[1] == 0x71)
   {
    int tx = 0xC0;
     SerialBT.write(tx);
     tx=1;
     SerialBT.write(tx);
     tx=0;
      SerialBT.write(tx);
       SerialBT.write(tx);
     
   }
  }
  delay(20);
}

int Read_Frame(int Rx_data[])
{
  int index = 0;
  int frame_status = 0; 
  while(1)
  {
      if (SerialBT.available()) {
     
     Rx_data[index] = SerialBT.read();
    
      if( Rx_data[index] == 0xC0)
      {
        frame_status++;
      }
  index++;
      if(frame_status >= 1) frame_status++;

      if(frame_status == 3) break;

    }
  }

  return index;
}
