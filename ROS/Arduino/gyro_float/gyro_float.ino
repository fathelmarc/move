#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;

std_msgs::Float32 test;

ros::Publisher p("chatter", &test);

struct gy25 {
  char buffer[50];
  int counter;
  float heading;
  float roll;
  float pitch;
} cmps;

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  calibration();
  nh.advertise(p);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateCMPS();
  test.data = cmps.heading;
  p.publish( &test );
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
//      cmps.pitch = atof(strtok(cmps.buffer + 5, ","));
//      cmps.roll = atof(strtok(cmps.buffer + 5, ","));
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
