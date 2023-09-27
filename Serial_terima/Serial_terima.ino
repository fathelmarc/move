
char packetBuffer[512];
struct PG45 {
  char buffer[50];
  int counter;
  float vel;
} base;
void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateVel();
  //PID(base.vel);
  digitalWrite(12,base.vel);
  digitalWrite(13,base.vel);
}

void updateVel() {
  char tmp; // Variabel temporary
  while (Serial.available()) {
    tmp = Serial.read();
    base.buffer[base.counter++] = tmp;
    if (tmp == '\n') { // Langkah 1
      base.buffer[base.counter] = 0; // Karakter terminator
      if (base.buffer[0] == '#') {
        base.vel = atof(strtok(base.buffer + 1, '='));
      }
      base.counter = 0;
    }
  }
}
