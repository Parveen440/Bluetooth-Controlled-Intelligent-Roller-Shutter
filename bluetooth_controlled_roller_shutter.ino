#include <SoftwareSerial.h>

// Define the pins for RX and TX
const int RX_PIN = 10;
const int TX_PIN = 11;

// Create a SoftwareSerial object
SoftwareSerial bluetooth(RX_PIN, TX_PIN);

// Define motor pins
const int motorPin1 = 3; // Motor 1 pin 1
const int motorPin2 = 4; // Motor 1 pin 2
const int enablePin = 5; // Enable pin

void setup() {
  // Start the built-in Serial communication at a baud rate of 9600
  Serial.begin(9600);

  // Start the SoftwareSerial communication at a baud rate of 9600
  bluetooth.begin(9600);

  // Print a message to the Serial Monitor
  Serial.println("Bluetooth communication started. Waiting for data...");

  // Set all the motor control pins to outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Initially, disable the motor
  digitalWrite(enablePin, LOW);
}

void loop() {
  // Check if data is available from the Bluetooth module
  if (bluetooth.available()) {
    // Read the incoming data
    char incomingData = bluetooth.read();

    // Print the incoming data to the Serial Monitor
    Serial.print("Received: ");
    Serial.println(incomingData);

    // Control the motor based on the received data
    if (incomingData == 'F') { // Forward command
      // Enable the motor
      digitalWrite(enablePin, HIGH);

      // Spin the motor in one direction
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      delay(3000); // Wait for 3 seconds

      // Stop the motor
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
    } else if (incomingData == 'B') { // Backward command
      // Enable the motor
      digitalWrite(enablePin, HIGH);

      // Spin the motor in the opposite direction
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      delay(3000); // Wait for 3 seconds

      // Stop the motor
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
    } else {
      // Disable the motor if any other command is received
      digitalWrite(enablePin, LOW);
    }
  }
}
