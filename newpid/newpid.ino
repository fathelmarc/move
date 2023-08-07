#define encA 3
#define encB 4
#define PWM 9
#define IN1 7
#define IN2 8

long prevT =0;
volatile float pos = 0;
float eprev =0;
float eintegral = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(encA, INPUT);
  pinMode(encB, INPUT);
  pinMode(PWM,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(encA), readEncoder, RISING);//read encoder
  Serial.println("target pos");
}

void loop() {
  // put your main code here, to run repeatedly:
  //set target position for the motor to move
  pid(3600);
}

void pid(float sudut){
  //convert pwm value to international angle value
  int target = 135*(sudut/360);
  float kp = 30;   //proportional
  float ki = 2;   //integral => for co
  float kd = 1;   //PID constants//0.5
  
  long currT = micros();
  float deltaT = (float(currT - prevT))/(1.0e6);
  prevT = currT;
  int e = pos - target;
  float  derv = (e-eprev)/(deltaT);
  float u = kp*e +kd*derv + ki*eintegral;
  float pwr = fabs(u);
  if (pwr > 255){
    pwr =200;
  }
  //control the direction
  int dir = 1;
  if(u<0){
    dir = -1;
  }
  setMotor(dir,pwr, PWM,IN1,IN2);
  eprev = e;
}
void setMotor(int dir,int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm, pwmVal);
  if(dir == 1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }else if(dir == -1){
    digitalWrite(in1, LOW);
    digitalWrite(in2,HIGH);
  }else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }
}
//read the encoder 
void readEncoder(){
  int b= digitalRead(encB);
  if(b > 0){
    pos++;
  }else{
    pos--;
  }
}
