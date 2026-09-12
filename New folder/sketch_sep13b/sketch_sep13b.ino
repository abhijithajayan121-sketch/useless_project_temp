#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const char* ssid     = "ABHIJITH's A54";
const char* password = "abhijith3663";
const char* serverIp = "http://192.168.108.253:5000/eye-status";
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int potPin   = 34; 
const int btnAdd   = 13;
const int btnSub   = 12;
const int btnMul   = 14;
const int btnDiv   = 27;
const int btnClear = 26;

int num1 = 0;
int num2 = 0;
char selectedOp = ' ';
enum State { SELECT_NUM1, SELECT_NUM2, WAITING_RESPONSE };
State currentState = SELECT_NUM1;

int clearPressCount = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 250; 

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(35));
  
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  pinMode(btnAdd, INPUT_PULLUP);
  pinMode(btnSub, INPUT_PULLUP);
  pinMode(btnMul, INPUT_PULLUP);
  pinMode(btnDiv, INPUT_PULLUP);
  pinMode(btnClear, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  lcd.print("Connecting Wi-Fi");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("WiFi_Status:");
    Serial.println(0);
    delay(500);
  }

  for (int i = 0; i < 5; i++) {
    Serial.print("WiFi_Status:");
    Serial.println(1);
    delay(100);
  }

  resetCalculator();
}

void loop() {
  Serial.print("WiFi_Status:");
  Serial.println(WiFi.status() == WL_CONNECTED ? 1 : 0);

  int potVal = analogRead(potPin);
  int currentVal = map(potVal, 0, 4095, 0, 99); 

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

  if (millis() - lastDebounceTime > debounceDelay) {
    
    if (digitalRead(btnClear) == LOW) {
      lastDebounceTime = millis();
      clearPressCount++;
      resetCalculator();
      return;
    }

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
        
        processCalculationLocally(num1, selectedOp, num2);
      }
    }
  }

  delay(50);
}

// ==========================================
// LOCAL CALCULATION & HTTP EYE FETCH
// ==========================================
void processCalculationLocally(int n1, char op, int n2) {
  bool eyesOpen = false;
  bool serverSuccess = false;

  // 1. Fetch eye status over Wi-Fi
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverIp);
    http.setTimeout(2000); // 2-second timeout failsafe

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("Server Raw Response: ");
      Serial.println(response);

      if (response.indexOf("true") != -1) {
        eyesOpen = true;
      }
      serverSuccess = true;
    } else {
      Serial.print("HTTP Error Code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }

  // 2. Server connection failsafe check
  if (!serverSuccess) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Server Error");
    lcd.setCursor(0, 1);
    lcd.print("Check Connection");
    return;
  }

  Serial.print("Eyes Open Evaluated To: ");
  Serial.println(eyesOpen ? "YES (WRONG ANS)" : "NO (CORRECT ANS CONDITIONAL)");

  // 3. Playful Mode: 25% chance stall delay
  if (random(0, 4) == 0) {
    delay(1800);
  }

  lcd.clear();

  // 4. Reset Button Counter Insult Threshold
  if (clearPressCount > 3) {
    lcd.setCursor(0, 0);
    lcd.print("id10t error");
    lcd.setCursor(0, 1);
    lcd.print("too bad btr luck");
    return;
  }

  // 5. Calculate actual math result
  float realAnswer = calculateCorrect(n1, op, n2);

  // 6. Complex / High Value Check (> 2000)
  if (abs(realAnswer) > 2000.0) {
    int insultChoice = random(0, 3);
    lcd.setCursor(0, 0);
    if (insultChoice == 0) {
      lcd.print("wastage of ram");
      lcd.setCursor(0, 1);
      lcd.print("u fool...");
    } else if (insultChoice == 1) {
      lcd.print("too complex!");
      lcd.setCursor(0, 1);
      lcd.print("use ur brain dummy");
    } else {
      lcd.print("ans > 2000?");
      lcd.setCursor(0, 1);
      lcd.print("not doing it bot");
    }
    return;
  }

  // 7. Output Generation based on Eye Status & 30% Probability
  String line1Msg = "";
  String line2Msg = "";

  if (eyesOpen) {
    // EYES OPEN -> WRONG / ARROGANT ANSWER
    if (op == '/' && n2 == 0) {
      line1Msg = "Ans: infinity";
      line2Msg = "easy math bro";
    } else {
      int offsets[] = {-10, -5, -1, 1, 3, 7, 12, 100};
      float wrongVal = realAnswer + offsets[random(0, 8)];
      
      int msgType = random(0, 3);
      if (msgType == 0) {
        line1Msg = "Ans: " + String(wrongVal, 1);
        line2Msg = "(too easy)";
      } else if (msgType == 1) {
        line1Msg = "It is " + String(wrongVal, 1);
        line2Msg = "get good lol";
      } else {
        line1Msg = "Ans: " + String(wrongVal, 1);
        line2Msg = "you idiot";
      }
    }
  } else {
    // EYES CLOSED -> 30% CHANCE CORRECT, 70% CHANCE MODIFIED WRONG ANSWER
    if (op == '/' && n2 == 0) {
      line1Msg = "div0 error";
    } else {
      int roll = random(0, 100);

      if (roll < 30) {
        // 30% PROBABILITY: REAL/CORRECT ANSWER
        if (op == '/') {
          line1Msg = "Ans: " + String(realAnswer, 1);
        } else {
          line1Msg = "Ans: " + String((int)realAnswer);
        }
      } else {
        // 70% PROBABILITY: MODIFIED ARROGANT ANSWER
        int altType = random(0, 3);

        if (altType == 0) {
          float squaredVal = realAnswer * realAnswer;
          line1Msg = "Ans: " + String(squaredVal, 1);
          line2Msg = "squared it lol";
        } else if (altType == 1) {
          float x10Val = realAnswer * 10;
          line1Msg = "Ans: " + String(x10Val, 1);
          line2Msg = "close enough!";
        } else {
          float weirdVal = realAnswer + 42;
          line1Msg = "Ans: " + String(weirdVal, 1);
          line2Msg = "+42 for flavor";
        }
      }
    }
  }

  // Render to LCD
  lcd.setCursor(0, 0);
  lcd.print(line1Msg);
  if (line2Msg.length() > 0) {
    lcd.setCursor(0, 1);
    lcd.print(line2Msg);
  }
}

float calculateCorrect(int n1, char op, int n2) {
  if (op == '+') return n1 + n2;
  if (op == '-') return n1 - n2;
  if (op == '*') return n1 * n2;
  if (op == '/' && n2 != 0) return (float)n1 / (float)n2;
  return 0;
}

void resetCalculator() {
  num1 = 0;
  num2 = 0;
  selectedOp = ' ';
  currentState = SELECT_NUM1;
  lcd.clear();
}