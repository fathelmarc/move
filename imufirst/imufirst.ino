#include <Wire.h>

void setup(){
  Serial.begin(115200);//Serial monitor
  Serial3.begin(115200);//Serial gy25
  delay(1000);

  //kalibrasi tilt
  Serial3.write(0xA5);
  Serial3.write(0x54);
  delay(100);

  //kalibrasi Heading
  Serial3.write(0xA5);
  Serial3.write(0x55);
  delay(100);

  //output ASCII
  Serial3.write(0xA5);
  Serial3.write(0x53);
  delay(100);
}
void loop(){
  //baca data gy25 secara realtime
  Serial.println(Serial3.readStringUntil('\n'));
}
