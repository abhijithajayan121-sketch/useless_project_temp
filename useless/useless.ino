#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Change I2C address to 0x3F if 0x27 shows blank screen/blocks
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int potPin   = A0;
const int btnAdd   = 2;
const int btnSub   = 3;
const int btnMul   = 4;
const int btnDiv   = 5;
const int btnClear = 6;  // Clear/Reset screen button

int num1 = 0;
int num2 = 0;
char selectedOp = ' ';
enum State { SELECT_NUM1, SELECT_NUM2, WAITING_RESPONSE };
State currentState = SELECT_NUM1;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 250; 

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  pinMode(btnAdd, INPUT_PULLUP);
  pinMode(btnSub, INPUT_PULLUP);
  pinMode(btnMul, INPUT_PULLUP);
  pinMode(btnDiv, INPUT_PULLUP);
  pinMode(btnClear, INPUT_PULLUP);

  resetCalculator();
}

void loop() {
  // 1. Read incoming responses from Python
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    message.trim();
    if (message.length() > 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      if (message.length() <= 16) {
        lcd.print(message);
      } else {
        lcd.print(message.substring(0, 16));
        lcd.setCursor(0, 1);
        lcd.print(message.substring(16, min((int)message.length(), 32)));
      }
    }
  }

  // 2. Read Potentiometer mapped from 0 to 99
  int potVal = analogRead(potPin);
  int currentVal = map(potVal, 0, 1023, 0, 99);

  // 3. Render current input state on LCD
  if (currentState == SELECT_NUM1) {
    num1 = currentVal;
    lcd.setCursor(0, 0);
    lcd.print("Set Num 1:      ");
    lcd.setCursor(0, 1);
    lcd.print("N1 = ");
    lcd.print(num1);
    lcd.print("   ");
  } 
  else if (currentState == SELECT_NUM2) {
    num2 = currentVal;
    lcd.setCursor(0, 0);
    lcd.print("Set Num 2:      ");
    lcd.setCursor(0, 1);
    lcd.print(String(num1) + " " + selectedOp + " " + String(num2) + "   ");
  }

  // 4. Handle Button Presses
  if (millis() - lastDebounceTime > debounceDelay) {
    
    // Clear/Reset LCD Button Press
    if (digitalRead(btnClear) == LOW) {
      lastDebounceTime = millis();
      resetCalculator();
      return;
    }

    // Operator Button Presses
    char pressedOp = ' ';
    if (digitalRead(btnAdd) == LOW) pressedOp = '+';
    else if (digitalRead(btnSub) == LOW) pressedOp = '-';
    else if (digitalRead(btnMul) == LOW) pressedOp = '*';
    else if (digitalRead(btnDiv) == LOW) pressedOp = '/';

    if (pressedOp != ' ') {
      lastDebounceTime = millis();

      if (currentState == SELECT_NUM1) {
        selectedOp = pressedOp;
        currentState = SELECT_NUM2;
        lcd.clear();
      } 
      else if (currentState == SELECT_NUM2) {
        currentState = WAITING_RESPONSE;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Thinking...");
        
        // Transmit equation format: "N1,OP,N2" to brain.py
        Serial.println(String(num1) + "," + selectedOp + "," + String(num2));
      }
    }
  }

  delay(50);
}

void resetCalculator() {
  num1 = 0;
  num2 = 0;
  selectedOp = ' ';
  currentState = SELECT_NUM1;
  lcd.clear();
}