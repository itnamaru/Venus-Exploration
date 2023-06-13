#include <Servo.h>

// Pin assignments
const int rightSensorPin = 2;   // Right IR sensor pin
const int leftSensorPin = 3;    // Left IR sensor pin
const int centerSensorPin = 4;  // Center (main) IR sensor pin
const int servoPin = 9;         // Servo control pin

// Servo configuration
Servo myservo;
int angle=0;          // Initial servo position

// Variables for IR sensor
int rightSensorState = LOW;     // Current state of the right IR sensor
int leftSensorState = LOW;      // Current state of the left IR sensor
int centerSensorState = LOW;    // Current state of the center IR sensor

void setup() {
  Serial.begin(9600);     // Initialize serial communication
  pinMode(rightSensorPin, INPUT);    // Set right IR sensor pin as input
  pinMode(leftSensorPin, INPUT);     // Set left IR sensor pin as input
  pinMode(centerSensorPin, INPUT);   // Set center IR sensor pin as input
  myservo.attach(10); //attaches the servo on pin 9 to the servo object
}

void loop() {
  
  //for grabbing sequence
  for (angle=90; angle>=40; angle-=1) //goes from 90 to 0 degrees
{
myservo.write(angle); //moves servo back in opposite direction
delay(20); //waits 20ms between servo commands
}
for (angle=0; angle<90; angle+=1)//goes from 0 to 90 degrees in steps of 1 degree
{
myservo.write(angle); //directs servo to go to position in variable 'angle'
delay(20);
//waits 20ms between servo commands
}
  
  
  // Read the current state of each IR sensor
  rightSensorState = digitalRead(rightSensorPin);
  leftSensorState = digitalRead(leftSensorPin);
  centerSensorState = digitalRead(centerSensorPin);

  // Check the right sensor
  if (rightSensorState == HIGH) {
    Serial.println("Right sensor activated!");
    moveRight();  // Call the function for the right sequence
    delay(1000);  // Delay to prevent false triggering
  }

  // Check the left sensor
  if (leftSensorState == HIGH) {
    Serial.println("Left sensor activated!");
    moveLeft();   // Call the function for the left sequence
    delay(1000);  // Delay to prevent false triggering
  }

  // Check the center sensor
  if (centerSensorState == HIGH) {
    Serial.println("Center sensor activated!");
    moveStraight();  // Call the function for the straight sequence
    delay(1000);     // Delay to prevent false triggering
  }
}

void moveRight() {
  // Move the servo to the right position
  myservo.write(180);
  delay(500);  // Delay to allow the servo to reach the position

  // Perform right moving sequence (add your code here)

  // Move the servo back to the initial position
  myservo.write(0);
  delay(500);  // Delay to allow the servo to reach the position
}

void moveLeft() {
  // Move the servo to the left position
  myservo.write(0);
  delay(500);  // Delay to allow the servo to reach the position

  // Perform left moving sequence (add your code here)

  // Move the servo back to the initial position
  myservo.write(0);
  delay(500);  // Delay to allow the servo to reach the position
}

void moveStraight() {
  // Move the servo to the straight position
  myservo.write(90);
  delay(500);  // Delay to allow the servo to reach the position

  // Perform straight moving sequence (add your code here)

  // Move the servo back to the initial position
  myservo.write(0);
  delay(500);  // Delay to allow the servo to reach the position
}
