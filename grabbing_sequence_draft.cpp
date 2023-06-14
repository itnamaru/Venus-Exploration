#include <Servo.h>

// Pin assignments
const int rightSensorPin = 2;   // Right IR sensor pin
const int leftSensorPin = 3;    // Left IR sensor pin
const int centerSensorPin = 4;  // Center (main) IR sensor pin
const int servoPin = 9;         // Servo control pin

// Servo configuration
Servo myservo;
int servoPosition = 0;          // Initial servo position

// Variables for IR sensor
int rightSensorState = LOW;     // Current state of the right IR sensor
int leftSensorState = LOW;      // Current state of the left IR sensor
int centerSensorState = LOW;    // Current state of the center IR sensor

void setup() {
  Serial.begin(9600);     // Initialize serial communication
  pinMode(rightSensorPin, INPUT);    // Set right IR sensor pin as input
  pinMode(leftSensorPin, INPUT);     // Set left IR sensor pin as input
  pinMode(centerSensorPin, INPUT);   // Set center IR sensor pin as input
  myservo.attach(servoPin);          // Attach servo to the servo pin
}

void loop() {
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