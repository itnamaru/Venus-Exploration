
#include <servo.h>
servo myservo1;
servo myservo2;
servo myservo3;
servo myservo4;
enum state
{
    left,
    right
};
state var;
Servo myservo;
int pos;
long duration, cm;
const int pingPin = 7;

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

    int potpin = 0;
    var = left;
    pos = 60;
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
    switch (var)
    {

    case left:
        pos += 1;
        myservo3.write(pos); // sets the servo position based on the variable 'pos'
        delay(15);
        if (pos == 120)
        {
            var = right;
        }
        break;

    case right:
        pos -= 1;
        myservo3.write(pos);
        delay(15); // sets the servo position based on the variable 'pos'
        if (pos == 60)
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
    // Serial.print(cm);
    // Serial.print("cm");
    // Serial.println();
}

void grabby()
{
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
        delay(10000);
        nav_traverse(5);
        delay(5000);

        // release box
        grabby();
        // drive back
        nav_traverse(2);
        delay(10000);
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

int Base_IR_front() // code for checking base LED
{
    int detected = 0;
    return detected;
}

int Base_IR_top() // code for checking base LED
{
    int detected = 0;
    return detected;
}

void locate_ramp(int go_to_base)
{
    int detected1 = 0;   // sensor pointed towards base
    int detected2 = 0;   // sensor to check if we reached the base
    if (go_to_base == 1) // check if go to base is triggered
    {
        while (detected2 == 0)
        {
            detected2 = Base_IR_top();
            while (detected == 0)
            {
                for (int i = 0; i < 10; i++) // first 360
                {
                    detected1 = Base_IR();
                    if (detected1 == 0) // start nav to locate base
                    {
                        nav_grab(3);
                    }
                    else // detects base
                    {
                        break;
                    }
                }
                if (detected1 == 0)
                {
                    for (int i = 0; i < 5; i++) // 45 degree turn to the right
                    {
                        nav_grab(3);
                    }
                    nav_traverse(1);
                    delay(1000);
                    for (int i = 0; i < 10; i++) // second 360
                    {
                        detected1 = Base_IR();
                        if (detected1 == 0) // start nav to locate base
                        {
                            nav_grab(3);
                        }
                        else // detects base
                        {
                            break;
                        }
                    }
                }
                if (detected1 == 0)
                {
                    nav_traverse(2);
                    delay(1000);
                    nav_traverse(4);
                    nav_traverse(1);
                    delay(1000);
                    for (int i = 0; i < 10; i++) // second 360
                    {
                        detected1 = Base_IR();
                        if (detected1 == 0) // start nav to locate base
                        {
                            nav_grab(3);
                        }
                        else // detects base
                        {
                            break;
                        }
                    }
                }
                if (detected1 == 0)
                {
                    nav_traverse(3);
                }
            }
            if (detected1 == 1)
            {
                nav_traverse(1);
                delay(3000);
            }
            detected2 = Base_IR_top();
        }
        if (detected2 == 1)
        {
            delay(500);
            ramp_sequence();
            go_to_base = 0;
        }
        
    }

    return;
}

void loop()
{
    delay(5000);
    locate_ramp(1);
    Serial.print('Done');
}
