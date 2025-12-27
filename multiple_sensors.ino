int button = 6;
int touch = 7;
int laser = 8;
int redLED = 9;
int greenLED = 10;
int blueLED = 11;
int buzzer = 12;

int cnt = 0;
const int totalSensors = 3;

bool buttonProcessed = false;
bool touchProcessed = false;
bool lightProcessed = false;

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(touch, INPUT);
  pinMode(laser, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(!digitalRead(button) && !buttonProcessed){ 
    cnt++;
    buttonProcessed = true;
    Serial.println("Buton apast");
    delay(200); 
  }
  if(digitalRead(touch) && !touchProcessed){ 
    cnt++;
    touchProcessed = true;
    Serial.println("Senzor atins");
    delay(200);
  }
  if(analogRead(A5)<400 && !lightProcessed){
    cnt++;
    lightProcessed = true;
    Serial.println("Lumina inchisa");
    delay(200);
  }

  if(cnt == totalSensors){
    digitalWrite(buzzer, HIGH);
    Serial.println("Gata");
    while(true){
      for(int i = 20; i <= 240; i+=40){
        analogWrite(redLED, i);
        digitalWrite(laser, HIGH);
        delay(50);
        digitalWrite(laser, LOW);
        delay(50);
      }
      for(int i = 255; i >= 5; i-=40){
        analogWrite(redLED, i);
        digitalWrite(laser, HIGH);
        delay(50);
        digitalWrite(laser, LOW);
        delay(50);
      }
      for(int i = 20; i <= 240; i+=40){
        analogWrite(greenLED, i);
        digitalWrite(laser, HIGH);
        delay(50);
        digitalWrite(laser, LOW);
        delay(50);
      }
      for(int i = 255; i >= 5; i-=40){
        analogWrite(greenLED, i);
        digitalWrite(laser, HIGH);
        delay(50);
        digitalWrite(laser, LOW);
        delay(50);
      }
      for(int i = 20; i <= 240; i+=40){
        analogWrite(blueLED, i);
        digitalWrite(laser, HIGH);
        delay(50);
        digitalWrite(laser, LOW);
        delay(50);
      }
      for(int i = 255; i >= 5; i-=40){
        analogWrite(blueLED, i);
        digitalWrite(laser, HIGH);
        delay(50);
        digitalWrite(laser, LOW);
        delay(50);
      }
    }
  }
}
