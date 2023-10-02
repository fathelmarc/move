int baca_imu(){
  updateCMPS();
  hadap= cmps.heading;
  if (hadap > 180) {
    float selisih = 180 - hadap;
    hadap = 180 + selisih;
    hadap *= -1;
  }
}

void Kinematic(float x, float y, float arah) {
  //baca_imu();
  v1 = (-sin(torad(45*hadap)) * y + cos(torad(45)) * x ) / keliling * totdeg + R_robot * arah/R_roda;
  v2 = (-sin(torad(315*hadap)) * y + cos(torad(315)) * x ) / keliling * totdeg + R_robot * arah/R_roda;
  v3 = (-sin(torad(225*hadap)) * y + cos(torad(225)) * x ) / keliling * totdeg + R_robot * arah/R_roda;
  v4 = (-sin(torad(135*hadap)) * y + cos(torad(135*hadap)) * x ) / keliling * totdeg + R_robot * arah/R_roda;
  Serial2.print("!"); Serial2.println(v1);
  Serial2.print("@"); Serial2.println(v2);
  Serial2.print("#"); Serial2.println(v3);
  Serial2.print("$"); Serial2.println(v4);
}

void calibrate_IMU(){
  Serial3.begin(115200);//Serial gy25
  delay(2000);
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
void calibrate_IMUt(){
  Serial3.begin(115200);

  Serial.println("Mulai Kalibret");

  delay(3000);

  Serial3.write(0xA5);
  Serial3.write(0x54);

  delay(1000); // Jeda sebelum kalibrasi heading

  // Kalibrasi Heading
  Serial3.write(0xA5);
  Serial3.write(0x55);

  delay(100); // Jeda sebelum konfigurasi output

  // Output ASCII
  Serial3.write(0xA5);
  Serial3.write(0x53);

  delay(100); // Jeda sebentar
  Serial.println("selesai kalibret IMU");
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

void lacak() {
  Serial.print("  p1=");
  monitor_koreksi(posi1);
  Serial.print("  p2=");
  monitor_koreksi(posi2);
  Serial.print("  p3=");
  monitor_koreksi(posi3);
  Serial.print("  p4=");
  monitor_koreksi(posi4);
}

void monitor_koreksi(float nilai_enc) {
  float sudut = 360 * (nilai_enc/ 3830);
  Serial.print(sudut);
}


void readEncoder1() {
  int b = digitalRead(encB1); if (b > 0) {
    posi1++;
  } else {
    posi1--;
  }
}
void readEncoder2() {
  int b = digitalRead(encB2); if (b > 0) {
    posi2++;
  } else {
    posi2--;
  }
}
void readEncoder3() {
  int b = digitalRead(encB3); if (b > 0) {
    posi3++;
  } else {
    posi3--;
  }
}
void readEncoder4() {
  int b = digitalRead(encB4); if (b > 0) {
    posi4++;
  } else {
    posi4--;
  }
}
