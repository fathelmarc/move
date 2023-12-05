#include <ros.h>
#include <geometry_msgs/Quaternion.h>

ros::NodeHandle nh;

geometry_msgs::Quaternion pImu;
ros::Publisher pub("chit_chat", &pImu);

struct gy25 {
  char buffer[50];
  int counter;
  float heading;
  float roll;
  float pitch;
} cmps;

void setup() {
  nh.initNode();
  Serial.begin(57600); // Serial monitor
  nh.advertise(pub);
  calibration();
}

//void loop() {
//  // Baca data GY25 secara realtime
//  Serial.println(Serial3.readStringUntil('\n'));
//}

void loop() {
  updateCMPS();
//  pImu.data = {1, 2, 3, 4, 5};
  pImu.x = cmps.heading;
  pImu.y = cmps.pitch;
  pImu.z = cmps.roll;
  pub.publish(&pImu);
  nh.spinOnce();
}

void updateCMPS() {
  char tmp; // Variabel temporary
  while (Serial3.available()) {
    tmp = Serial3.read();
    cmps.buffer[cmps.counter++] = tmp;
    if (tmp == '\n') { // Langkah 1
      cmps.buffer[cmps.counter] = 0; // Karakter terminator
      cmps.heading = atof(strtok(cmps.buffer + 5, ","));
      cmps.pitch = atof(strtok(cmps.buffer + 5, ","));
      cmps.roll = atof(strtok(cmps.buffer + 5, ","));
      cmps.counter = 0;
    }
  }
}

void calibration() {
  Serial3.begin(115200); // Serial GY25
  delay(3000); // Jeda 3 detik

  // Kalibrasi Tilt
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
}
