#define R 0.1 //m

float Keliling = 2 * 3.14 * R;

float w1, w2, w3, w4, fx, fy;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateCMPS();

}
