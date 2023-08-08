#define R 5

float w1;
float w2;
float w3;
float tujuan1;
float tujuan2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void IMU_calibration(){
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

float toRad(float degree) {
  return degree * M_PI / 180;
}

void loop() {
  // put your main code here, to run repeatedly:
  
}


float Keliling = 2*3.14*R;

void jarak(float target1, float target2){
  tujuan1 = target1/Keliling*360;
  tujuan2 = target2/Keliling*360;
  kinematic(tujuan1,tujuan2);
}

void kinematic(float x, float y){
  w1 = 1/R*(-sin(toRad( po))*x + cos(toRad( 60))*y+5) ;
  w2 = 1/R*(-sin(toRad(180))*x - cos(toRad(180))*y+5);
  w3 = 1/R*(-sin(toRad(300))*x + cos(toRad(300))*y+5);
  Serial.print('!'); Serial.println(w1);
  Serial.print('@'); Serial.println(w2);
  Serial.print('#'); Serial.println(w3);
}
void position(){
  float Vx = -sin(toRad(IMU 
}
