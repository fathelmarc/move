#define R 0.1 //m

float Keliling = 2 * 3.14 * R;

float w1, w2, w3, w4, fx, fy;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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

void loop() {
  // put your main code here, to run repeatedly:
  updateCMPS();

}
