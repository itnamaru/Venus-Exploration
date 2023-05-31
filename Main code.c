#include <servo.h>
#define pinIRt 4
#define pinIRo 7
servo myservo1;
servo myservo2;
servo myservo3;
servo myservo4;
enum state {left, right};
state var;
Servo myservo; 
int pos;
long duration, cm;
const int pingPin = 7;
int valIRt;
int valIRo;
int pos = 0;
void setup()
{
    myservo1.attach(12); // right wheel
    myservo2.attach(13); // left wheel
    myservo3.attach(11); // Ultrasonic motor
    myservo4.attach(10); // grabbing motor
    Serial.begin(9600);  // serial connection for communication
    int potpin = 0;
  myservo.attach(10);
  var = left;
  pos = 60;
}

void nav_traverse (int direction)
{
    val1 = analogRead(potpin);
    val2 = analogRead(potpin);
    myservo1.attach(12); // right wheel
    myservo2.attach(13); // left wheel
    switch (direction)
    {
    case '1': // forward
        val1 = map(val1, 0, 1023, 180, 0);
        val2 = map(val2, 0, 1023, 0, 180);
        delay(50);
        break;
    case '2': // backward
        val1 = map(val1, 0, 1023, 0, 180);
        val2 = map(val2, 0, 1023, 180, 0);
        delay(50);
        break;
    case '3': // right
        val1 = map(val1, 0, 1023, 180, 0);
        val2 = map(val2, 0, 1023, 180, 0);
        delay(500);
        myservo1.detach();
        myservo2.detach();
        break;
    case '4': // left
        val1 = map(val1, 0, 1023, 0, 180);
        val2 = map(val2, 0, 1023, 0, 180);
        delay(500);
        myservo1.detach();
        myservo2.detach();
        break;
    case '5': // stop
        myservo1.detach();
        myservo2.detach();
        break;
    default:
        return;
    }
    myservo1.write(val1);
    myservo2.write(val2);
    return 0;
}
void nav_grab(){
    val1 = analogRead(potpin);
    val2 = analogRead(potpin);
    myservo1.attach(12); // right wheel
    myservo2.attach(13); // left wheel
    switch (direction)
    {
    case '1': // forward
        val1 = map(val1, 0, 1023, 180, 0);
        val2 = map(val2, 0, 1023, 0, 180);
        delay(300);
        myservo1.detach();
        myservo2.detach();
        break;
    case '2': // backward
        val1 = map(val1, 0, 1023, 0, 180);
        val2 = map(val2, 0, 1023, 180, 0);
        delay(300);
        myservo1.detach();
        myservo2.detach();
        break;
    case '3': // right
        val1 = map(val1, 0, 1023, 180, 0);
        val2 = map(val2, 0, 1023, 180, 0);
        delay(50);
        myservo1.detach();
        myservo2.detach();
        break;
    case '4': // left
        val1 = map(val1, 0, 1023, 0, 180);
        val2 = map(val2, 0, 1023, 0, 180);
        delay(50);
        myservo1.detach();
        myservo2.detach();
        break;
    case '5': // stop
        myservo1.detach();
        myservo2.detach();
        break;
    default:
        return;
    }
    myservo1.write(val1);
    myservo2.write(val2);
    return 0;
}

void IR()
{
    return 0;
}

void ultrasonic()
{
  switch (var) {

    case left:
    pos += 1;
    myservo3.write(pos);                   // sets the servo position based on the variable 'pos'
    delay(15);
    if (pos ==  120)
    {
      var = right;
    }
    break;

    case right:
    pos -= 1;
    myservo3.write(pos);
    delay(15);                   // sets the servo position based on the variable 'pos'
    if (pos ==  60)
    {
      var = left;
    }
    break;
    
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
}
void IRt()
{
  valIR = digitalRead(pinIR);
  if (valIR == 0)
  {
    // Serial.println("STOP");
  }
  else
  {
    // Serial.println("GO");
  }
}
void IRt()
{
  valIR = digitalRead(pinIRt);
  if (valIRt == 0)
  {
    // Serial.println("STOP");
  }
  else
  {
    // Serial.println("GO");
  }
}
void IRo()
{
  valIR = digitalRead(pinIRo);
  if (valIRo == 1)
  {
//     Serial.println("STOP");
  }
  else
  {
//     Serial.println("GO");
  }
}
void ramp_sequence()
{

    return 0;
}
void Communicate()
{
    
}
void loop()
{
}
