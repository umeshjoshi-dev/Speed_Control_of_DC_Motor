/*
 * Speed Control of DC Motor using Arduino PWM - Keypad Control
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
 *   User enters desired motor speed as a percentage (0–100) using a 4x3 keypad.
 *   Arduino maps the entered value to a PWM duty cycle (0–255) and drives the IGBT.
 *   Speed is displayed on a 20x4 LCD for confirmation.
 */

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// Buffer to hold 3-digit speed input (e.g., "075" for 75%)
#define SpeedLength 3
char buffer[SpeedLength];
byte buffer_count = 0;

// LCD: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(8, A1, A2, A3, A4, A5);

char Key;
int x = 0;

// 4x3 Keypad Layout
const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// Keypad row/column pin connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};   // Row pins
byte colPins[COLS] = {5, 4, 3};       // Column pins

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Pin Definitions
#define PWM_OUT  10   // PWM output to IGBT gate drive
#define DIR_PIN1 11   // Motor direction control
#define DIR_PIN2 12   // Motor direction control

void setup() {
  pinMode(PWM_OUT, OUTPUT);
  pinMode(DIR_PIN1, OUTPUT);
  pinMode(DIR_PIN2, OUTPUT);

  // Set motor direction (forward)
  digitalWrite(DIR_PIN1, HIGH);
  digitalWrite(DIR_PIN2, LOW);

  lcd.begin(20, 4);

  // Welcome screen
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO    ");
  lcd.setCursor(0, 1);
  lcd.print("   OUR PROJECT   ");
  delay(1500);
  lcd.clear();

  delay(150);
  lcd.print("  SPEED CONTROL  ");
  lcd.setCursor(0, 1);
  lcd.print("   OF DC MOTOR   ");
  delay(1500);
  lcd.clear();
}

void loop() {
  // Prompt user to enter speed
  lcd.setCursor(0, 0);
  lcd.print("  ENTER % SPEED  ");

  Key = keypad.getKey();
  giveSpeed();

  // Process after 3 digits entered
  if (buffer_count == 3) {
    processData();
  }
}

// Store each keypress into the buffer and show on LCD
void giveSpeed() {
  if (Key) {
    buffer[buffer_count] = Key;
    lcd.setCursor(buffer_count, 1);
    lcd.print(buffer[buffer_count]);
    buffer_count++;
  }
}

// Map entered speed % to PWM and drive motor
void processData() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  YOU ENTERED  ");

  x = atoi(buffer);   // Convert char array to integer
  lcd.setCursor(0, 1);
  lcd.print(x);
  lcd.print(" %");

  // Map 0–100% to PWM 0–255
  int s = map(x, 0, 100, 0, 255);
  analogWrite(PWM_OUT, s);

  delay(2000);   // Show entered speed on LCD before clearing
  lcd.clear();
  clearBuffer();
}

// Reset the input buffer for next entry
void clearBuffer() {
  while (buffer_count != 0) {
    buffer[buffer_count--] = 0;
  }
}
