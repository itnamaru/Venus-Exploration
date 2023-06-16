#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
enum state { left,
             right };
// state grabby;
state var;
int pos;
// int rob;
long duration, cm;
const int pingPin = 7;
int potpin = 0;
int val1;
int val2;
int direction;
int vald;
int vals;
int Block = 0;

void setup() {

  Serial.begin(9600);  // serial connection for communication
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  int potpin = 0;
  myservo3.attach(11);
  myservo4.attach(10);
  var = left;
  pos = 0;
  // grabby = left;

  // for (int angle = 0; angle < 90; angle += 1)  //goes from 0 to 90 degrees in steps of 1 degree
  // {
  //   myservo4.write(angle);  //directs servo to go to position in variable 'angle'
  //   delay(20);
  //   //waits 20ms between servo commands
  // }
}

void loop() {

  vald = digitalRead(2);
  vals = digitalRead(3);
  if (var == left) {
    pos += 1;
    myservo3.write(pos);
    if (pos == 90) {
      var = right;
    }
  }

  if (var == right) {
    pos -= 1;
    myservo3.write(pos);
    if (pos == 30) {
      var = left;
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

  if (cm <= 25) {
    nav_grab(3);
    nav_grab(5);
  } else if (vald == 0) {
    nav_traverse(2);
    nav_traverse(5);
  } else {
    nav_grab(1);
    if (Block != 1) {
      if (vals == 1) {
        Serial.println("v");
        Block = 1;
        nav_traverse(2);
        nav_traverse(2);
        nav_traverse(2);
        nav_traverse(2);
        nav_grab(5);
        // for (int angle = 0; angle < 90; angle += 1)  //goes from 0 to 90 degrees in steps of 1 degree
        // {
        //   myservo4.write(angle);  //directs servo to go to position in variable 'angle'
        //   delay(20);
        //   //waits 20ms between servo commands
        // }
        for (int angle = 90; angle >= 40; angle -= 1)  //goes from 90 to 0 degrees
        {
          myservo4.write(angle);  //moves servo back in opposite direction
          delay(20);              //waits 20ms between servo commands
        }
      }
    }
  }
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

void nav_grab(int direction)  // code for small increment movement for the grabbing sequence
{
  val1 = analogRead(potpin);
  val2 = analogRead(potpin);
  myservo1.attach(12);  // right wheel
  myservo2.attach(13);  // left wheel
  if (direction == 1) {
    val1 = map(val1, 0, 1023, 180, 0);
    val2 = map(val2, 0, 1023, 0, 180);
    myservo1.write(val1);
    myservo2.write(val2);
    delay(25);
    myservo1.detach();
    myservo2.detach();
  } else if (direction == 2) {
    val1 = map(val1, 0, 1023, 0, 180);
    val2 = map(val2, 0, 1023, 180, 0);
    myservo1.write(val1);
    myservo2.write(val2);
    delay(25);
    myservo1.detach();
    myservo2.detach();
  } else if (direction == 3) {
    val1 = map(val1, 0, 1023, 180, 0);
    val2 = map(val2, 0, 1023, 180, 0);
    myservo1.write(val1);
    myservo2.write(val2);
    delay(25);
    myservo1.detach();
    myservo2.detach();
  } else if (direction == 4) {
    val1 = map(val1, 0, 1023, 0, 180);
    val2 = map(val2, 0, 1023, 0, 180);
    myservo1.write(val1);
    myservo2.write(val2);
    delay(25);
    myservo1.detach();
    myservo2.detach();
  } else if (direction == 5) {
    myservo1.detach();
    myservo2.detach();
  }
  myservo1.write(val1);
  myservo2.write(val2);
  return 0;
}
