/*
 * Speed Control of DC Motor using Arduino PWM - Potentiometer Control
 * 
 * Project: Speed Control of a DC Motor using Arduino PWM Technique with IGBT Chopper Circuit
 * Institution: M. H. Saboo Siddik Polytechnic (Aided), Mumbai
 * Academic Year: 2017-2018
 * 
 * Team Members:
 *   - Simran Correia (15206)
 *   - Jadhav Sanket Suresh (15210)
 *   - Joshi Umesh Yadneshwar (15213)
 *   - Khan Ashfaque Hamid Hussain (15216)
 * 
 * Guide: Prof. (Mrs.) Kalaivani Muthuvelan & Mr. Arjun Lad
 * 
 * Description:
 *   Controls DC motor speed via a potentiometer connected to analog pin A0.
 *   PWM output drives the IGBT gate drive circuit.
 *   Includes soft start (20 sec ramp-up) and smooth stop features.
 *   Real-time duty cycle % and voltage displayed on 20x4 LCD.
 */

#include <Wire.h>
#include <LiquidCrystal.h>

// Pin Definitions
#define PWMpin 10        // PWM output to IGBT gate drive circuit
#define STOP_BUTTON 5    // Smooth stop trigger button
#define START_BUTTON 4   // Restart button

// LCD: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(8, A1, A2, A3, A4, A5);

void setup() {
  Serial.begin(9600);
  pinMode(PWMpin, OUTPUT);
  pinMode(STOP_BUTTON, INPUT_PULLUP);
  pinMode(START_BUTTON, INPUT_PULLUP);

  lcd.begin(20, 4);

  // Welcome screen
  lcd.setCursor(0, 0);
  lcd.print("  SPEED CONTROL  ");
  lcd.setCursor(0, 1);
  lcd.print("   OF DC MOTOR   ");
  lcd.setCursor(0, 2);
  lcd.print(" MHSSP - EE DEPT ");
  delay(2000);
  lcd.clear();

  // Soft Start: gradually ramp motor up over 20 seconds
  lcd.setCursor(0, 1);
  lcd.print(" DC MOTOR IS ");
  lcd.setCursor(0, 2);
  lcd.print(" STARTING SOFTLY ");
  lcd.setCursor(0, 3);
  lcd.print(" UP TO 20 SECONDS ");

  int softstart_time = 20 * 1000 / 110;  // Time per PWM step (ms)

  for (int sp = 0; sp < 110; sp++) {
    analogWrite(PWMpin, sp);
    Serial.println(sp);
    delay(softstart_time);
  }

  lcd.clear();
}

void loop() {
  // Read potentiometer and map to PWM range
  int sensorValue = analogRead(A0);
  int value = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(PWMpin, value);
  Serial.println(value);

  // Calculate duty cycle and equivalent voltage
  float dutycycle = (float)value / 255.0;
  float voltage = dutycycle * 230.0;

  // Display real-time parameters on LCD
  lcd.setCursor(0, 0);
  lcd.print("REAL TIME PARAMETERS");
  lcd.setCursor(0, 2);
  lcd.print(" DUTY CYCLE = ");
  lcd.print(dutycycle * 100);
  lcd.setCursor(0, 3);
  lcd.print("VOLTAGE = ");
  lcd.print(voltage);

  // Smooth Stop: when stop button pressed, gradually reduce speed over 15 sec
  if (digitalRead(STOP_BUTTON) == LOW) {
    int smoothstop_time = 15 * 1000 / value;

    for (int s = value; s > 0; s--) {
      analogWrite(PWMpin, s);
      Serial.println(s);
      delay(smoothstop_time);
    }

    digitalWrite(PWMpin, LOW);

    // Wait for restart button press
    while (digitalRead(START_BUTTON) == HIGH) {
      // Waiting...
    }
  }
}
