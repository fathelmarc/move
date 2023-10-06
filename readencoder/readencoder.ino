#define encA 3
#define encB 4
#define PWM 9
#define IN1 7
#define IN2 8

int pos = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(encA, INPUT);
  pinMode(encB, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(PWM,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(encA), readEncoder, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(pos);
  setMotor(1,100,PWM,IN1,IN2);
}

void readEncoder(){
  int b = digitalRead(encB);
  if (b>0){
    pos++;
  }else{
    pos--;
  }
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
