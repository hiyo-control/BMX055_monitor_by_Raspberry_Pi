#include<Wire.h>
#define Addr_Accl 0x19

unsigned int data[6];
int Input_pin  = 3;
int Output_pin = 5;

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  
  BMX055_Init();

  pinMode(Input_pin , INPUT );
  pinMode(Output_pin, OUTPUT);
  
  delay(100);
}

void loop()
{
  int switch_value = digitalRead(Input_pin);

  BMX055_Accl();

  Serial.write('H');
  Serial.write( switch_value );
  for (int i=0; i<6; i++)
  {
    Serial.write( data[i] );
  }

  if (switch_value == 1)
  {
    digitalWrite(Output_pin, HIGH);
  }
  else
  {
    digitalWrite(Output_pin, LOW);
  }
  
  delay(500);
}

//=====================================//
void BMX055_Init()
{
  //-----------------------------------//
  Wire.beginTransmission(Addr_Accl);
  Wire.write(0x0F);
  Wire.write(0x03);
  Wire.endTransmission();
  delay(100);
  //-----------------------------------//
  Wire.beginTransmission(Addr_Accl);
  Wire.write(0x10);
  Wire.write(0x08);
  Wire.endTransmission();
  delay(100);
  //-----------------------------------//
  Wire.beginTransmission(Addr_Accl);
  Wire.write(0x11);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(100);
  
}
//=====================================//
void BMX055_Accl()
{
  for (int i = 0; i < 6; i++)
  {
    Wire.beginTransmission(Addr_Accl);
    Wire.write((2 + i));
    Wire.endTransmission();
    Wire.requestFrom(Addr_Accl, 1);
    if (Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
  }
}
