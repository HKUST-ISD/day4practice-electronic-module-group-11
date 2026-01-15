/*Replace all the ? in the code to read the value touchRead(GPIO pin) returned.*/

#define TOUCHPIN 4                    // ***Replace the ? with the GPIO pin you selected as touch pin
#define LED 1                         // ESP32S3 Universal Dev Board - Built-in LED on IO1 (GPIO 1)
#define THRESHOLD 50000               // ***Observe the reading when the pin is touched. Then modify this threshold.***


int touch_reading;

void setup() {
  Serial.begin(115200);        // ***Start the serial communication set baud rate.***
  pinMode(LED, OUTPUT);       // Set pin connected to LED as an output pin
  
  // Blink LED 3 times at startup to identify which LED is being controlled
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
  }
  Serial.println("Setup complete - LED test blink finished");
}

void loop() { 
  touch_reading = touchRead(TOUCHPIN); // Read the touch sensor
  Serial.print("Touch reading: ");
  Serial.print(touch_reading);
  
  // The LED can be turned on when the pin is touched.
  // Note: touch values INCREASE when touched (e.g., 220370) vs normal (20000)
  if (touch_reading > THRESHOLD) {
    digitalWrite(LED, HIGH);   // turn on LED when touched
    Serial.println(" -> TOUCHED! LED ON");
  } else {
    digitalWrite(LED, LOW);    // turn off LED when not touched
    Serial.println(" -> Not touched, LED OFF");
  }
    
  delay(100); // delay 0.1s
}
