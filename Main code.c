#include <servo.h>
servo myservo1;
servo myservo2;
servo myservo3;
servo myservo4;

int pos = 0;
void setup()
{
    myservo1.attach(12); // right wheel
    myservo2.attach(13); // left wheel
    myservo3.attach(11); // Ultrasonic motor
    myservo4.attach(10); // grabbing motor
    Serial.begin(9600);  // serial connection for communication
    int potpin = 0;
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
    return 0;
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
