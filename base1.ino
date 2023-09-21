#define M_PI 3.14159265359
#define R 5 //m
struct gy25 {
  char buffer[50];
  int counter;
  float yaw;
} cmps;

float toRad(float degree) {
  return degree * M_PI / 180;
}

float Keliling = 2 * M_PI * R;
float w1, w2, w3, w4, fx, fy, v1, v2, v3, v4;

void setup() {
  // put your setup code here, to run once:
  Serial2.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  kinematic(100,0);delay(3000);
  kinematic(0,100);delay(3000);
  kinematic(-100,0);delay(3000);
  kinematic(0,-100);
}
void kinematic(float x, float y) {
  w1 = (-sin(toRad( 45 )) * x + cos(toRad( 45 )) * y )/Keliling;
  w2 = (-sin(toRad(315 )) * x + cos(toRad(315 )) * y )/Keliling;
  w3 = (-sin(toRad(225 )) * x + cos(toRad(225 )) * y )/Keliling;
  w4 = (-sin(toRad(135 )) * x + cos(toRad(135 )) * y )/Keliling;
  Serial2.print('!'); Serial2.println(w1);
  Serial2.print('@'); Serial2.println(w2);
  Serial2.print('#'); Serial2.println(w3);
  Serial2.print('$'); Serial2.println(w4);
}
