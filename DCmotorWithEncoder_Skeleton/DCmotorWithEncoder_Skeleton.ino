/*Change all the ? in the code and add code in ??? to Control the speed of rotation.*/

#define IN1   4  // ESP32 GPIO pin connected to L298N IN1
#define IN2   5  // ESP32 GPIO pin connected to L298N IN2
#define A     15 // ESP32 GPIO pin connected to encoder phase A (C1)
#define B     16 // ESP32 GPIO pin connected to encoder phase B (C2)
#define PWM   6  // ESP32 GPIO pin connected to L298N ENA (PWM speed control)

// encoder output value
int A_data=0;
int B_data=0;

String command;

void setup() {
  /*setup baud and pin mode */
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(A, INPUT);
  pinMode(B, INPUT);

  /*Set rotation direction as forward rotation (CCW)*/
  // For CCW: IN1 = HIGH, IN2 = LOW
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

}

void loop() {
    // send the duty cycle of PWM to control the speed of DC motor
    if (Serial.available() > 0) {
        command = Serial.readStringUntil('\n'); // Read the incoming command
        command.trim(); // Remove any leading or trailing whitespace
        if (command == "0") {
        // output PWM signals with 0% duty cycle (0% of 255 = 0)
        analogWrite(PWM, 0);  
        Serial.println("PWM set to 0% (0/255)");
        } 
        else if (command == "25") {
        // output PWM signals with 25% duty cycle (25% of 255 = 64)
        analogWrite(PWM, 64);   
        Serial.println("PWM set to 25% (64/255)");
        }
        else if (command == "50") {
        // output PWM signals with 50% duty cycle (50% of 255 = 128)
        analogWrite(PWM, 128);   
        Serial.println("PWM set to 50% (128/255)");
        }
        else if (command == "75") {
        // output PWM signals with 75% duty cycle (75% of 255 = 191)
        analogWrite(PWM, 191);   
        Serial.println("PWM set to 75% (191/255)");
        }
        else if (command == "100") {
        // output PWM signals with 100% duty cycle (100% of 255 = 255)
        analogWrite(PWM, 255);   
        Serial.println("PWM set to 100% (255/255)");
        }
        }
    // Read values of A and B (encoder signals)
    A_data = digitalRead(A);
    B_data = digitalRead(B);
    // Plot A B in Serial Plotter
    Serial.print("A:");
    Serial.print(A_data);
    Serial.print(",");
    Serial.print("B:");
    Serial.print(B_data);
    Serial.println("\t"); 
    
}
