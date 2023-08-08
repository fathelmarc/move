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
  attachInterrupt(digitalPinToInterrupt(encA), readEncoder, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(pos);
}

void readEncoder(){
  int b = digitalRead(encB);
  if (b>0){
    pos++;
  }else{
    pos--;
  }
}
