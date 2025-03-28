#include <SoftwareSerial.h>
#include <string.h>
#include <Arduino.h>
#include <SPI.h>

#define TRIG_PIN A0 // Define Arduino pins for the ultrasonic sensor
#define ECHO_PIN A1
#define DISTANCE_THRESHOLD 10  // Distance threshold in cm
#define servoPin 7 // Define Arduino pin for the servo motor
int positions[] = {0, 90, 180, 270, 360};
int index = 0;

// Motor Driver 1 (Motors A & B)
int enA = 3;  
int in1 = 4;
int in2 = 2;
int enB = 3;
int in3 = 4;
int in4 = 2;
// Motor Driver 2 (Motors C & D)
int enC = 5;  
int in5 = 6;
int in6 = 7;
int enD = 5;
int in7 = 6;
int in8 = 7;

int motorSpeed = 100;


void integrateSetup() {
    Serial.begin(115200);
    // Set up the ultrasonic sensor
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    // Set up the servo sensor
    pinMode(servoPin, OUTPUT);
    // Set up the motors
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enC, OUTPUT);
    pinMode(enD, OUTPUT);
    pinMode(in5, OUTPUT);
    pinMode(in6, OUTPUT);
    pinMode(in7, OUTPUT);
    pinMode(in8, OUTPUT);
}

void moveServo(int position){
    int pulseWidth;

    if (position == 0 || position == 360) pulseWidth = 600; // 0 degrees
    else if(position == 90) pulseWidth = 1450; // 90 degrees
    else if(position == 180) pulseWidth = 2300; // 180 degrees
    else if(position == 270) pulseWidth = 3150; // 270 degrees 

    // Send pulse to move servo
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(servoPin, LOW);
    delay(500);
}

void stopMotors() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(in5, LOW);
    digitalWrite(in6, LOW);
    digitalWrite(in7, LOW);
    digitalWrite(in8, LOW);
}

void beginmotors(){
    // Set motors to a speed (a moderate number like motorSpeed in this case)
    analogWrite(enA, motorSpeed);
    analogWrite(enB, motorSpeed);
    analogWrite(enC, motorSpeed);
    analogWrite(enD, motorSpeed);

    // Move all motors forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);
}

void backwards(){
    // Set motors to a speed (a moderate number like motorSpeed in this case)
    analogWrite(enA, motorSpeed);
    analogWrite(enB, motorSpeed);
    analogWrite(enC, motorSpeed);
    analogWrite(enD, motorSpeed);

    // Move all motors backwards
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(in5, HIGH); 
    digitalWrite(in6, LOW);
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
}

void turnLeft() {
  Serial.println("Turning Left");

  // Left side moves backward, right side moves forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);

  // Set speed
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
  analogWrite(enC, motorSpeed);
  analogWrite(enD, motorSpeed);
}

void turnRight() {
  Serial.println("Turning Right");

  // Left side moves backward, right side moves forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);

  // Set speed
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
  analogWrite(enC, motorSpeed);
  analogWrite(enD, motorSpeed);
}


void changedirection(){
    if(digitalRead(in1) == HIGH){
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      digitalWrite(in5, HIGH); 
      digitalWrite(in6, LOW);
      digitalWrite(in7, HIGH);
      digitalWrite(in8, LOW);
    }
    else{
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      digitalWrite(in5, LOW);
      digitalWrite(in6, HIGH);
      digitalWrite(in7, LOW);
      digitalWrite(in8, HIGH);
    }
}

void ultrasonicSensing() {
    // Send trigger pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read echo pulse
    long duration = pulseIn(ECHO_PIN, HIGH);
    int distance = duration * 0.034 / 2;  // Convert to cm

    if (distance > 0 && distance <= DISTANCE_THRESHOLD) {
        Serial.println("The distance is: ");
        Serial.println(distance);
        Serial.println("cm");
        Serial.println("Obstacle Detected!");

        // Also activate the pusher (servo motor) when there is an object detection
        moveServo(positions[index]);
        index++;
        if(index >= 5) index = 0;
    }

    delay(1000);  // Delay for stability
}
