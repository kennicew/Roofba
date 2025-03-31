#include <Servo.h>

// Define ultrasonic sensor and servo pins
#define TRIG_PIN 3
#define ECHO_PIN 2
#define servoPin 6
  
#define DISTANCE_THRESHOLD 20  // Ultrasonic sensor distance threshold in cm

Servo myServo;  // Create a Servo object

void setup() {
    // Setup serial connection and definition of ultrasonic sensor and servo pins
    Serial.begin(115200); 
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    myServo.attach(servoPin);
    myServo.write(200); // callibrated initial servo angle to be parallel with the vehicle
}

void push(){
    // Function to activate the servo pusher
    myServo.write(110); // rotate clockwise by 90 degrees
    delay(1000);
    myServo.write(200); // rotate back to original position
    delay(1000);
}

void loop() {
    // Send trigger pulse for ultrasonic sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read echo pulse from ultrasonic sensor
    long duration = pulseIn(ECHO_PIN, HIGH);
    int distance = duration * 0.034 / 2;  // Convert to cm

    // If an object is detected in the distance within the threshold, print the distance detected and trigger the pusher
    if (distance > 0 && distance <= DISTANCE_THRESHOLD) {
        Serial.print("The distance is: ");
        Serial.print(distance);
        Serial.println("cm");
        Serial.println("Obstacle Detected!");
        
        push(); // trigger servo pusher
    }
    delay(500);
}
