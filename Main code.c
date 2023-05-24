#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

int pos = 0;
int potpin = 0;
int val1;
int val2;
int ramp = 1;
int go_to_base = 0;
int direction;
void setup()
{
    myservo1.attach(12); // right wheel
    myservo2.attach(13); // left wheel
    myservo3.attach(11); // Ultrasonic motor
    myservo4.attach(10); // grabbing motor
    Serial.begin(9600);  // serial connection for communication
}

void nav_traverse(int direction) // code for navigating the map
{
    val1 = analogRead(potpin);
    val2 = analogRead(potpin);
    myservo1.attach(12); // right wheel
    myservo2.attach(13); // left wheel
    if (direction == 1)  // forward
    {
        val1 = map(val1, 0, 1023, 180, 0);
        val2 = map(val2, 0, 1023, 0, 180);
        delay(50);
    }
    else if (direction == 2) // backward
    {
        val1 = map(val1, 0, 1023, 0, 180);
        val2 = map(val2, 0, 1023, 180, 0);
        delay(50);
    }
    else if (direction == 3) // right
    {
        val1 = map(val1, 0, 1023, 180, 0);
        val2 = map(val2, 0, 1023, 180, 0);
        delay(500);
        myservo1.detach();
        myservo2.detach();
    }
    else if (direction == 4) // left
    {
        val1 = map(val1, 0, 1023, 0, 180);
        val2 = map(val2, 0, 1023, 0, 180);
        delay(500);
        myservo1.detach();
        myservo2.detach();
    }
    else if (direction == 5) // stop
    {
        myservo1.detach();
        myservo2.detach();
    }
    else
    {
        return;
    }
    myservo1.write(val1);
    myservo2.write(val2);
    delay(15);
    return 0;
}

void nav_grab(int direction) // code for small increment movement for the grabbing sequence
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

void IR() // IR sensor code
{
    return 0;
}

void ultrasonic() // US sensor code
{
    return 0;
}

void grabby(){
return 0;
}

void ramp_sequence(int ramp)
{
    if (ramp == 1)
    {
        Serial.print('R'); // notify over wifi ramp is occupied
                           // start sequence

        // check youve reached ramp

        // allign with ramp

        // drive forward until stopped at end
        nav_traverse(1);
        delay(7000);
        nav_traverse(5);
        delay(5000);

        // release box
        grabby();
        // drive back
        nav_traverse(2);
        delay(7000);
        nav_traverse(5);
        // validate out of ramp

        // close set arms back to initial position

        // turn 180 degrees and continue exploring

        // finish sequence
        Serial.print('G');
    }
    else
    {
        return;
    }

    return 0;
}

void Check_Partner_statues(int ramp) // check if ramp is clear or not
{
    int incomingByte;
    if (Serial.available() > 0)
    { // read the oldest byte in the serial buffer:

        incomingByte = Serial.read();

        // if it's a capital G, set ramp to open:

        if (incomingByte == 'G')
        {
            ramp = 1;
        }

        // if it's a capital R, set ramp to occupied:

        if (incomingByte == 'R')
        {
            ramp = 0;
        }
    }
}

void locate_ramp(int go_to_base)
{
    go_to_base = 1; // tell robot to focus on reaching the base
    return;
}

void loop()
{
    delay(5000);
    ramp_sequence(1);
    delay(5000);
    Serial.print('Done');
}
