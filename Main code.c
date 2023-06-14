#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
enum state { left,
             right };
state var;
Servo myservo;
int pos;
long duration, cm;
const int pingPin = 7;
int checking = 0;
int del = 50;
int potpin = 0;
int val1;
int val2;
int ramp = 1;
int go_to_base = 0;
int direction;
int sam = 0;
int froto = 0;
int vald;
void setup() {

  Serial.begin(9600);  // serial connection for communication

  int potpin = 0;
  myservo.attach(11);
  var = left;
  pos = 0;
}

void nav_traverse(int direction)  // code for navigating the map
{
  myservo1.attach(12);  // right wheel
  myservo2.attach(13);  // left wheel
  val1 = analogRead(potpin);
  val2 = analogRead(potpin);
  if (direction == 1)  // forward
  {
    val1 = map(val1, 0, 1023, 180, 0);
    val2 = map(val2, 0, 1023, 0, 180);
    // delay(50);
  } else if (direction == 2)  // backward
  {
    val1 = map(val1, 0, 1023, 0, 180);
    val2 = map(val2, 0, 1023, 180, 0);
    delay(50);
  } else if (direction == 3)  // right
  {
    val1 = map(val1, 0, 1023, 180, 0);
    val2 = map(val2, 0, 1023, 180, 0);
    delay(500);
    myservo1.detach();
    myservo2.detach();
  } else if (direction == 4)  // left
  {
    val1 = map(val1, 0, 1023, 0, 180);
    val2 = map(val2, 0, 1023, 0, 180);
    delay(500);
    myservo1.detach();
    myservo2.detach();
  } else if (direction == 5)  // stop
  {
    myservo1.detach();
    myservo2.detach();
  } else {
    return;
  }
  myservo1.write(val1);
  myservo2.write(val2);
  delay(15);
  return 0;
}

void loop() {

  vald = digitalRead(2);
  if (var == left) {
    pos += 1;
    myservo.write(pos);
    // delay(1);
    if (pos == 90) {
      var = right;
      // checking = 1;
    }
  }

  if (var == right) {
    pos -= 1;
    myservo.write(pos);
    // delay(1);
    if (pos == 30) {
      var = left;
      // froto = 1;
    }
  }

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  cm = duration / 29 / 2;
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if (cm <= 25) {
    nav_traverse(3);
    // delay(1000);
    nav_traverse(5);
    // sam = 0;
  }

  else if (vald == 0) {
    nav_traverse(3);
    // delay(1000);
    nav_traverse(5);
  }
  else if (vald == 1) {
    nav_traverse(1);
    delay(25);
  }
}
