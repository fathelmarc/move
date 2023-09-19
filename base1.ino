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

float Keliling = 2 * 3.14 * R;
float w1, w2, w3, w4, fx, fy, v1, v2, v3, v4;

void setup() {
  // put your setup code here, to run once:
  Serial2.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  jarak(0,50);
}
void jarak (float target_x, float target_y) {
  fx = target_x / Keliling * 360;
  fy = target_y / Keliling * 360;
  kinematic(fx, fy);
}
void kinematic(float x, float y) {
  w1 = -sin(toRad( 45 )) * x + cos(toRad( 45 )) * y ;
  w2 = -sin(toRad(135 )) * x + cos(toRad(135 )) * y ;
  w3 = -sin(toRad(225 )) * x + cos(toRad(225 )) * y ;
  w4 = -sin(toRad(315 )) * x + cos(toRad(315 )) * y ;
  Serial2.print('!'); Serial2.println(w1);
  Serial2.print('@'); Serial2.println(w2);
  Serial2.print('#'); Serial2.println(w3);
  Serial2.print('$'); Serial2.println(w4);
}
