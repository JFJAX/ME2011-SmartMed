#include <Servo.h>           // Include the Servo library
#include <LiquidCrystal.h>    // Include the LiquidCrystal library for LCD

// Constants
#define WATCHLED     6        // Watchdog LED on pin 6
#define STARTBUTTON  13       // Start button on pin 13

// Initialize the LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo servo1;  // Create Servo objects for each servo
Servo servo2;
Servo servo3;
Servo servo4;

// Watchdog indicator variables
bool isRunning = false;          // Tracks whether the robot is currently running
unsigned long previousMillis = 0; // Stores the last time the LED was toggled
const long onDuration = 250;      // LED on for 1/4 second
const long offDuration = 750;     // LED off for 3/4 second

// Function to control the servo sequence
void runSequence(Servo &servo, int repeatCount);

void setup() {
  pinMode(WATCHLED, OUTPUT);     // Set the LED pin as output
  pinMode(STARTBUTTON, INPUT);   // Set the button pin as input

  // LCD setup
  lcd.begin(16, 2);              // Set up the LCD's number of columns and rows
  lcd.setCursor(0, 0);
  lcd.print("SmartMed By"); // Display the standby message once
  lcd.setCursor(0, 1);
  lcd.print("Jace Flansburg");

  // Attach each servo to a specific pin
  servo1.attach(7);
  servo2.attach(8);
  servo3.attach(9);
  servo4.attach(10);

  // Set all servos to neutral position (0 degrees)
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);

  delay(1000);  // Wait for 1 second to ensure servos are in position
}

void loop() {
  // Check if the start button is pressed and if the robot is not currently running
  if (digitalRead(STARTBUTTON) == HIGH && !isRunning) {
    delay(1000);  // Debounce delay to ensure valid button press

    // Start the robot operation
    isRunning = true;
    lcd.clear();                    // Clear the standby message
    digitalWrite(WATCHLED, LOW);    // Turn off the LED during the operation
    
    // *******************ROBOT CODE START
    lcd.setCursor(0, 0);
    lcd.print("Dispensing...");
	lcd.setCursor(0, 1);
    lcd.print("PROZAC 20MG");
    
    runSequence(servo1, 2);
    delay(1000);

    lcd.setCursor(0, 0);
    lcd.print("Dispensing...");
	lcd.setCursor(0, 1);
    lcd.print("ABILIFY 5MG");
    
    runSequence(servo2, 1);
    delay(1000);
    
    lcd.setCursor(0, 0);
    lcd.print("Dispensing...");
	lcd.setCursor(0, 1);
    lcd.print("TRUVADA 200MG");
    
    runSequence(servo3, 1);
    delay(1000);
    
    lcd.setCursor(0, 0);
    lcd.print("Dispensing...");
	lcd.setCursor(0, 1);
    lcd.print("DEXEDRINE 30MG");
    
    runSequence(servo4, 2);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time to take");
    lcd.setCursor(0, 1);
    lcd.print("your pills!");

    delay(5000);  // Display message for 5 seconds
    lcd.clear();  // Clear the LCD after the dispensing message
    // *******************ROBOT CODE END

    // Reset state to allow another button press to start again
    isRunning = false;

    // Restore the standby message
    lcd.setCursor(0, 0);
    lcd.print("SmartMed By");
    lcd.setCursor(0, 1);
    lcd.print("Jace Flansburg");
  }

  // Watchdog indicator behavior when robot is not running
  if (!isRunning) {
    unsigned long currentMillis = millis();
    if (digitalRead(WATCHLED) == LOW && (currentMillis - previousMillis >= onDuration)) {
      digitalWrite(WATCHLED, HIGH);  // Turn the LED off after onDuration
      previousMillis = currentMillis;
    } else if (digitalRead(WATCHLED) == HIGH && (currentMillis - previousMillis >= offDuration)) {
      digitalWrite(WATCHLED, LOW);   // Turn the LED on after offDuration
      previousMillis = currentMillis;
    }
  }
}

// Function to control the servo sequence
void runSequence(Servo &servo, int repeatCount) {
  for (int i = 0; i < repeatCount; i++) {
    servo.write(0);  // Move servo close to maximum (175 degrees)
    delay(500);

    servo.write(135);  // Move back to 135 degrees
    delay(300);

    servo.write(90);   // Move back to midpoint (90 degrees)
    delay(300);

    servo.write(60);   // Move to 60 degrees
    delay(300);

    servo.write(45);   // Move to 45 degrees
    delay(300);

    servo.write(20);   // Move close to the neutral position
    delay(500);

    servo.write(0);    // Return to 0 degrees
    delay(2000);       // Delay before starting the sequence again
  }
}
