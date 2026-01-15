/*Replace ? in the code*/
#include <Arduino.h>
#include "NewPing.h"

// Hook up HC-SR04 with Trig and Echo to ESP32 Pins
#define TRIG_PIN 5                  // ESP32 pin connected to Trig pin of ultrasonic sensor
#define ECHO_PIN 6                  // ESP32 pin connected to Echo pin of ultrasonic sensor
// ESP 32 pin connected to LED (built-in LED on IO1)
#define LED 1

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// variable value to store the duty cycle value in 8 bit (0-255) of PWM
int value;

void setup() {
  
    Serial.begin(9600); // Initialize the Serial Monitor and set a baud rate
    pinMode(LED, OUTPUT); // Set LED pin as output for PWM
}

void loop() {
    
    // Get the distance from the Ultrasonic Sensor
    float distance = sonar.ping_cm();

    // Print the distance to the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(500); // Delay 0.5s to avoid reading the distance too fast 
    
    // Distance > 10cm, LED is OFF
    // Distance < 10 cm, the closer the target, the brighter the LED 
    // set the duty cycle value in 8-bit (0-255) to use analogWrite() to generate PWM signal to set the LED brightness
    // When distance < 10cm: brightness = 255 at 0cm, decreasing to 0 at 10cm
    // Formula: brightness = 255 * (1 - distance/10.0) but ensure value stays in 0-255 range
    if (distance > 10 || distance == 0)
    {
        // Distance > 10cm or invalid reading (0), LED is OFF
        value = 0;
    } else
    {
        // Distance < 10cm, calculate brightness: closer = brighter
        // At distance 0cm: brightness = 255 (maximum)
        // At distance 10cm: brightness = 0 (minimum)
        // Formula: brightness = 255 * (1 - distance/10.0)
        value = (int)(255 * (1.0 - distance / 10.0));
        // Ensure value is between 0 and 255
        if (value < 0) value = 0;
        if (value > 255) value = 255;
    }
    // print the duty cycle value 
    Serial.print("duty cycle value: ");
    Serial.println(value); 
    // generate PWM signal to set the LED brightness
    analogWrite(LED, value);

}
