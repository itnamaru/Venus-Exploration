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
    bool ramp = 1;
    bool go_to_base = 0;
}

void nav_traverse(int direction) // code for navigating the map
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

void nav_grab() // code for small increment movement for the grabbing sequence
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

void ramp_sequence(bool ramp)
{
    if (ramp == 1)
    {
        Serial.print('R'); // notify over wifi ramp is occupied
        // start sequence
        
        //check youve reached ramp

        //allign with ramp
        
        // drive forward until stopped at end
        for (i=0;i<=3;i++){
        nav_grab(1);
        }
        //release box

        //drive back
        for (i=0;i<=3;i++){
        nav_grab(2);
        }
        //validate out of ramp

        // close set arms back to initial position

        //turn 180 degrees and continue exploring

        // finish sequence
        Serial.print('G');
    }
    else
    {
        return;
    }

    return 0;
}

void Check_Partner_statues(bool ramp) // check if ramp is clear or not
{
    int incomingbyte;
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

void locate_ramp(bool go_to_base)
{
    go_to_base = 1; // tell robot to focus on reaching the base
    return;
}

void loop()
{
    ramp_sequence(1);
    delay(5000);
    Serial.print('Done');
}
