#define encA 3
#define encB 4
#define PWM 9
#define IN1 7
#define IN2 8

long prevT = 0;
volatile int posi = 0;
float eprev, eintegral, ederivative;

char packetBuffer[512];
struct PG45 {
  char buffer[50];
  int counter;
  float vel;
} base;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(encA, INPUT);
  pinMode(encB, INPUT);
  pinMode(PWM, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(12,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(encA), readEncoder, RISING);
  //read encoder
}

void updateVel() {
  char tmp; // Variabel temporary
  while (Serial.available()) {
    tmp = Serial.read();
    base.buffer[base.counter++] = tmp;
    if (tmp == '\n') { // Langkah 1
      base.buffer[base.counter] = 0; // Karakter terminator
      if (base.buffer[0] == '$') {
        base.vel = atof(strtok(base.buffer + 1, '='));
      }
      base.counter = 0;
    }
  }
}

void loop() {
  updateVel();
  PID(base.vel);
}
void PID(float sudut) {
  // put your main code here, to run repeatedly:
  float target = 3830 * (sudut / 360);

  // PID constants
  float kp = 2;//4,8;//1.6;//4.8//2//0.8
  float ki = 0.015;//0.2952;//0.984;//0.54// //11.352
  float kd = 0.1;//0,000019512//17.17;//2.16// //0.0372
  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;

  // Read the position
  int pos = 0;
  noInterrupts(); // disable interrupts temporarily while reading
  pos = posi;
  interrupts(); // turn interrupts back on

  // error
  int e = target - pos;

  // derivative
  ederivative = (e - eprev) / (deltaT);
  //store the previous error
  eprev = e;
  // integral
  eintegral += e * deltaT;

  // control signal
  float u = kp * e + kd * ederivative + ki * eintegral;
  //float u = 0.9*target/e * e + 0* dedt + e/0.3 * eintegral;
  // motor power
  float pwr = fabs(u);
  if ( pwr > 150 ) {
    pwr = 90;
  }
//  float pwr = 70
  // motor direction
  int dir = 1;
  if (u < 0) {
    dir = -1;
  }
//  int zero = 0;
  // signal the motor
  setMotor(dir, pwr, PWM, IN1, IN2); 
//  Serial.println(u);/
//  Serial.print(sudut);Serial.print(",");
//  Serial.print(pos);
//  Serial.print(", ");
//  Serial.println(target);
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2) {
  analogWrite(pwm, pwmVal);
  if (dir == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (dir == -1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

//read the encoder
void readEncoder() {
  int b = digitalRead(encB);
  if (b > 0) {
    posi++;
  } else {
    posi--;
  }
}
