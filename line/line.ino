#define V1 10  //kiri
#define V2 11  //kanan
#define dir1 12
#define dir2 13

uint16_t sensor1 = A1;
uint16_t sensor2 = A2;
uint16_t sensor3 = A3;
uint16_t sensor4 = A4;
uint16_t sensor5 = A5;
#define trig 3
#define echo 2

#define Set_point 47
#define vmax 65

float Pvalue, Ivalue, Dvalue, kp, ki, kd, u, kanan_kec, kiri_kec;
unsigned int pos, pwm;
int error, last_error, derivative, integral, duration_us, distance, sensor,
  a, b, c, d, e, tar, multiP = 1, multiI = 1, multiD = 1;

void setup() {
  Serial.begin(115200);
  pinMode(V1, OUTPUT);
  pinMode(V2, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
}

void motor(int l, int r) {
  l = fmax(-vmax, fmin(l, vmax));
  analogWrite(V1, abs(l));
  if (l > 0) digitalWrite(dir1, 0);
  else digitalWrite(dir1, 1);
  Serial.print(" nilai l = ");Serial.print(l);

  r = fmax(-vmax, fmin(r, vmax));
  analogWrite(V2, abs(r));
  if (r > 0) digitalWrite(dir2, 0);
  else digitalWrite(dir2, 1);
  Serial.print(" nilai r = ");Serial.print(r);
}

void motor2(int l, int r){
  analogWrite(V1, abs(l));
  if (l > 0) digitalWrite(dir1, 0);
  else digitalWrite(dir1, 1);

  analogWrite(V2, abs(r));
  if (r > 0) digitalWrite(dir1, 0);
  else digitalWrite(dir1, 1);
}

int bacasensor() {
  a = digitalRead(sensor1);
  b = digitalRead(sensor2);
  c = digitalRead(sensor3);
  d = digitalRead(sensor4);
  e = digitalRead(sensor5);
  tar;
  tar = ((40 * a + 30 * b + 20 * c + 10 * d + 0 * e) / (a + b + c + d + e)) * 3;
  return tar;
}

//1 kiri positif
//2 kanan negatif
void motor_mundur() {
  digitalWrite(trig, HIGH);
  digitalWrite(trig, LOW);
  duration_us = pulseIn(echo, HIGH);
  distance = 0.017 * duration_us;
  Serial.print("jarak benda =");Serial.println(distance);
  if (distance < 4 && distance != 0) {
    Serial.print(distance);
    motor(-60,-60);
    delay(600);
    motor(0,0);
    delay(100);
    motor(0,60);
    delay(500);
  }else{PID();}
}

void PID() {
  pos = bacasensor();
  error = 60 - pos;
  derivative = error - last_error;
  integral = error + last_error;
  kp = 11.25 ;
  ki = 0;
  kd = 0.8;

  Pvalue = (kp / pow(10, multiP)) * error;
  Ivalue = (ki / pow(10, multiI)) * integral;
  Dvalue = (kd / pow(10, multiD)) * derivative;
  u = Pvalue + Ivalue + Dvalue;
  kiri_kec = Set_point + u;
  kanan_kec = Set_point - u;
  Serial.print(" u= ");Serial.println(u);
  if (u > 0 && u < 75){
    motor(kiri_kec, kanan_kec); 
  } else if (u < 0 && u > -75) {
    motor(kiri_kec, kanan_kec);
  } else if (u < 1 && u > -1) {
    motor(kiri_kec, kanan_kec);
  } else if (u >= 75) {
    motor(kiri_kec, kanan_kec);
  }
  //delay(1);
}
void loop() {
  pos = bacasensor();
  PID();
  if (pos == 65533 ){
    motor_mundur();
    motor(0,70);
  }
  return 0;
}
