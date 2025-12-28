int button = 6;
int touch = 7;
int laser = 8;
int redLED = 9;
int greenLED = 10;
int blueLED = 11;
int buzzer = 12;
int swRotary = 5;
int clkRotary = 3;
int dtRotary = 4;
int start_reset_button = 2;

int cnt = 0;
int cntSW = 0;
int cntRotary = 0;
const int totalSensors = 5;

bool buttonProcessed = false;
bool touchProcessed = false;
bool lightProcessed = false;
bool swProcessed = false;
bool lastSWState = HIGH;
int lastCLKState = LOW;

bool timerRunning = false;
unsigned long startTime = 0;
const unsigned long timerDuration = 60000; // 60 secunde
int lastSecondPrinted = -1;

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(touch, INPUT);
  pinMode(laser, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(swRotary, INPUT_PULLUP);
  pinMode(clkRotary, INPUT);
  pinMode(dtRotary, INPUT);
  pinMode(start_reset_button, INPUT_PULLUP);
  Serial.begin(9600);
  lastCLKState = digitalRead(clkRotary);
}

void resetLabirint() {
  cnt = 0;
  cntSW = 0;
  cntRotary = 0;
  buttonProcessed = false;
  touchProcessed = false;
  lightProcessed = false;
  swProcessed = false;
  timerRunning = false;
  lastSecondPrinted = -1;
  digitalWrite(laser, LOW);
  analogWrite(redLED, 0);
  analogWrite(greenLED, 0);
  analogWrite(blueLED, 0);
  digitalWrite(buzzer, LOW);
  
  Serial.println("Labirint resetat!");
}

void loop() {
  // START / RESET button
  if(!digitalRead(start_reset_button)) {
    resetLabirint();
    startTime = millis();
    timerRunning = true;
    Serial.println("JOC INCEPUT");
    delay(200);  
  }

  // Timer logic
  if(timerRunning) {
    unsigned long elapsed = millis() - startTime;
    if(elapsed >= timerDuration) {
      Serial.println("Timpul a expirat!");
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      resetLabirint();
    } else if (elapsed >= 55000) { 
      int secLeft = 60 - (elapsed / 1000);
      if(secLeft != lastSecondPrinted) {
        Serial.println(secLeft);
        lastSecondPrinted = secLeft;
      }
    }
  }
  // Button
  if(!digitalRead(button) && !buttonProcessed){ 
    cnt++;
    buttonProcessed = true;
    Serial.println("Buton apasat");
    delay(200); 
  }
  // Touch sensor
  if(digitalRead(touch) && !touchProcessed){ 
    cnt++;
    touchProcessed = true;
    Serial.println("Senzor atins");
    delay(200);
  }

  // Light sensor
  if(analogRead(A5)<400 && !lightProcessed){
    cnt++;
    lightProcessed = true;
    Serial.println("Lumina inchisa");
    delay(200);
  }

  // Rotary encoder SW
  bool currentSWState = digitalRead(swRotary);
  if(lastSWState == HIGH && currentSWState == LOW && !swProcessed){
    cntSW++;
    Serial.println("SW Apasat");
    if(cntSW == 3){
      cnt++;
      swProcessed = true;
    }
    delay(50);
  }
  lastSWState = currentSWState;

  // Rotary encoder rotation
  int currentCLKState = digitalRead(clkRotary);
  if(currentCLKState != lastCLKState){ 
    if(digitalRead(dtRotary) != currentCLKState){ 
      cntRotary++;
      Serial.print("Ai rotit in dreapta: ");
      Serial.println(cntRotary);
      if(cntRotary == 3){
        cnt++;
        cntRotary = 0; 
      }
    }
  }
  lastCLKState = currentCLKState;

  // Labirint complet
  if(cnt == totalSensors){
    timerRunning = false; 
    Serial.println("FELICITARI! AI CASTIGAT!");
    
    for(int repeat = 0; repeat < 3; repeat++) {
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(100);
    }
    
    while(true){
      // Roșu
      analogWrite(greenLED, 0);
      analogWrite(blueLED, 0);
      for(int i = 20; i <= 240; i+=40){
        analogWrite(redLED, i);
        digitalWrite(laser, HIGH);
        delay(50);
        digitalWrite(laser, LOW);
        delay(50);
      }
      for(int i = 240; i >= 20; i-=40){
        analogWrite(redLED, i);
        digitalWrite(laser, HIGH);
        delay(50);
        digitalWrite(laser, LOW);
        delay(50);
      }
      
      // Verde
      analogWrite(redLED, 0);
      analogWrite(blueLED, 0);
      for(int i = 20; i <= 240; i+=40){
        analogWrite(greenLED, i);
        digitalWrite(laser, HIGH);
        delay(50);
        digitalWrite(laser, LOW);
        delay(50);
      }
      for(int i = 240; i >= 20; i-=40){
        analogWrite(greenLED, i);
        digitalWrite(laser, HIGH);
        delay(50);
        digitalWrite(laser, LOW);
        delay(50);
      }
      
      // Albastru
      analogWrite(redLED, 0);
      analogWrite(greenLED, 0);
      for(int i = 20; i <= 240; i+=40){
        analogWrite(blueLED, i);
        digitalWrite(laser, HIGH);
        delay(50);
        digitalWrite(laser, LOW);
        delay(50);
      }
      for(int i = 240; i >= 20; i-=40){
        analogWrite(blueLED, i);
        digitalWrite(laser, HIGH);
        delay(50);
        digitalWrite(laser, LOW);
        delay(50);
      }
    }
  }
}