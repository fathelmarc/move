#include<Wire.h>
struct gy25 {
  char buffer[50];
  int counter;
  float heading;
} cmps;

void setup() {
  Serial.begin(115200);//Serial monitor
  Serial3.begin(115200);//Serial gy25
  delay(1000);
  //kalibrasi tilt
  Serial3.write(0xA5);
  Serial3.write(0x54);
  delay(1000);

  //kalibrasi Heading
  Serial3.write(0xA5);
  Serial3.write(0x55);
  delay(100);

  //output ASCII
  Serial3.write(0xA5);
  Serial3.write(0x53);
  delay(100);
}

void updateCMPS() {
  char tmp; // Variabel temporary
  
  while (Serial3.available()) {
    tmp = Serial3.read();
    cmps.buffer[cmps.counter++] = tmp;
    if (tmp == '\n') { // Langkah 1
      cmps.buffer[cmps.counter] = 0; // Karakter terminator
      cmps.heading = atof(strtok(cmps.buffer + 5, ",")); // Langkah 2-4 
      cmps.counter = 0;
    }
  }
}

void loop() {
  //baca data gy25 secara realtime
  updateCMPS();
  Serial.print("yaw = ");
  Serial.println(cmps.heading );
  Serial.print("   ");
  //Serial.println(Serial3.readStringUntil('\n'));
}
