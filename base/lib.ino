struct gy25 {
  char buffer[50];
  int counter;
  float yaw, pitch, roll;
} cmps;

float toRad(float degree) {
  return degree * M_PI / 180;
}

void updateCMPS() {
  char tmp; // Variabel temporary
  while (Serial3.available()) {
    tmp = Serial3.read();
    cmps.buffer[cmps.counter++] = tmp;
    if (tmp == '\n') { // Langkah 1
      cmps.buffer[cmps.counter] = 0; // Karakter terminator
      cmps.yaw = atof(strtok(cmps.buffer + 5, ",")); // Langkah 2-4
      cmps.counter = 0;
    }
  }
}
void calibrate_IMU(){
Serial3.begin(115200);
  Serial.println("calibrating imu");
  Serial3.write(0xA5);
  Serial3.write(0x54);
  delay(200);
  Serial3.write(0xA5);
  Serial3.write(0x55);
  delay(200);
  Serial3.write(0xA5);
  Serial3.write(0x53);
  delay(200);
  Serial.println("done calibrating");
}
void jarak(float target_x, float target_y) {
  
  fx = target_x / Keliling * 360;
  fy = target_y / Keliling * 360;
  kinematic(fx, fy);
}
void kinematic(float x, float y) {
  w1 = 1 / R * (-sin(toRad( 45)) * x + cos(toRad( 45)) * y + R );
  w2 = 1 / R * (-sin(toRad(135)) * x + cos(toRad(135)) * y + R );
  w3 = 1 / R * (-sin(toRad(225)) * x + cos(toRad(225)) * y + R );
  w4 = 1 / R * (-sin(toRad(315)) * x + cos(toRad(315)) * y + R );
  Serial2.print('!'); Serial2.println(w1);
  Serial2.print('@'); Serial2.println(w2);
  Serial2.print('#'); Serial2.println(w3);
  Serial2.print('$'); Serial2.println(w4);
}
