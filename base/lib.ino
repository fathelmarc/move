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
      cmps.pitch = atof(strtok(cmps.buffer + 7, ","));
      cmps.roll = atof(strtok(cmps.buffer + 9, ","));
      cmps.counter = 0;
    }
  }
}



void jarak(float target_x, float target_y, float hadap) {
  
  fx = target_x / Keliling * 360;
  fy = target_y / Keliling * 360;
  kinematic(fx, fy, hadap);
}

void kinematic(float x, float y, float heading) {
  w1 = 1 / R * (-sin(toRad( 45)) * x + cos(toRad( 45)) * y + R * heading);
  w2 = 1 / R * (-sin(toRad(135)) * x + cos(toRad(135)) * y + R * heading);
  w3 = 1 / R * (-sin(toRad(225)) * x + cos(toRad(225)) * y + R * heading);
  w4 = 1 / R * (-sin(toRad(315)) * x + cos(toRad(315)) * y + R * heading);
  Serial.print('!'); Serial.println(w1);
  Serial.print('@'); Serial.println(w2);
  Serial.print('#'); Serial.println(w3);
  Serial.print('$'); Serial.println(w4);
}
void posisi() {
  
}
