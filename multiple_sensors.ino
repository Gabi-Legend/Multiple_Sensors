int button = 6;
int touch = 7;

int cnt = 0;
const int totalSensors = 2;

bool buttonProcessed = false;
bool touchProcessed = false;
void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(touch, INPUT);
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

  if(cnt == totalSensors){
    Serial.println("Gata");
    while(true); 
  }
}
