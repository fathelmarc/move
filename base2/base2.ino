#define encA1 2
#define encB1 46
#define encA2 3
#define encB2 40
#define encA3 18
#define encB3 42
#define encA4 19
#define encB4 48

#define R_roda 5
#define R_robot 16.149
#define totdeg 360

float torad(float degree) {
  return degree * PI / 180;
}

float keliling = 2 * PI * R_roda;

volatile int posi1 = 0;
volatile int posi2 = 0;
volatile int posi3 = 0;
volatile int posi4 = 0;
volatile int pos_imu = 0;
float v1, v2, v3, v4, prevT, eintegral, ederivative, eprev, hadap;

struct gy25 {
  char buffer[50];
  int counter;
  float heading;
} cmps;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);
  calibrate_IMU();
  pinMode(encA1, INPUT);
  pinMode(encB1, INPUT);
  pinMode(encA2, INPUT);
  pinMode(encB2, INPUT);
  pinMode(encA3, INPUT);
  pinMode(encB3, INPUT);
  pinMode(encA4, INPUT);
  pinMode(encB4, INPUT);
  attachInterrupt(digitalPinToInterrupt(encA1), readEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(encA2), readEncoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(encA3), readEncoder3, RISING);
  attachInterrupt(digitalPinToInterrupt(encA4), readEncoder4, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  move_with_imu(0, 0, 90);
  Serial.println();
}

void move_with_imu(float vx, float vy, float target) {

  float kp = 6;
  float ki = 0;
  float kd = 0;
  unsigned long currT = micros();
  float deltaT = ((float)(currT - prevT)) / (1.0e6);
  prevT = currT;
  baca_imu();
  int e = hadap - target;
  ederivative = (e - eprev) / (deltaT);
  eintegral += e * deltaT;

  float u = kp * e + ki * eintegral + kd * ederivative;
  Serial.print(target);
  Serial.print("  ");
  Serial.print(hadap);
  Kinematic(vx, vy, u);
}
