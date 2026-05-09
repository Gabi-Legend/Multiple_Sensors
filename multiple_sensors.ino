// =========================
// PIN DEFINITIONS
// =========================

const int BUTTON_PIN = 6;
const int TOUCH_PIN = 7;
const int LASER_PIN = 8;

const int RED_LED = 9;
const int GREEN_LED = 10;
const int BLUE_LED = 11;

const int BUZZER_PIN = 12;
const int PASSIVE_BUZZER = A4;

const int ROTARY_SW = 5;
const int ROTARY_CLK = 3;
const int ROTARY_DT = 4;

const int START_BUTTON = 2;
const int LIGHT_SENSOR = A5;

// =========================
// GAME CONFIG
// =========================

const int TOTAL_SENSORS = 5;

const int LIGHT_THRESHOLD = 400;

const int REQUIRED_ROTATIONS = 3;
const int REQUIRED_SW_PRESSES = 3;

const unsigned long TIMER_DURATION = 60000;

// =========================
// GAME STATES
// =========================

enum GameState {
  IDLE,
  PLAYING,
  WIN_STATE,
  LOSE_STATE
};

GameState currentState = IDLE;

// =========================
// GAME VARIABLES
// =========================

int progressCount = 0;

int rotaryButtonCount = 0;
int rotaryRotationCount = 0;

bool buttonProcessed = false;
bool touchProcessed = false;
bool lightProcessed = false;
bool rotarySwitchProcessed = false;

bool lastSWState = HIGH;
int lastCLKState = LOW;

unsigned long startTime = 0;
int lastSecondPrinted = -1;

// =========================
// SETUP
// =========================

void setup() {

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TOUCH_PIN, INPUT);

  pinMode(LASER_PIN, OUTPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PASSIVE_BUZZER, OUTPUT);

  pinMode(ROTARY_SW, INPUT_PULLUP);
  pinMode(ROTARY_CLK, INPUT);
  pinMode(ROTARY_DT, INPUT);

  pinMode(START_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);

  lastCLKState = digitalRead(ROTARY_CLK);

  resetGame();
}

// =========================
// RESET GAME
// =========================

void resetGame() {

  progressCount = 0;

  rotaryButtonCount = 0;
  rotaryRotationCount = 0;

  buttonProcessed = false;
  touchProcessed = false;
  lightProcessed = false;
  rotarySwitchProcessed = false;

  digitalWrite(LASER_PIN, LOW);

  analogWrite(RED_LED, 0);
  analogWrite(GREEN_LED, 0);
  analogWrite(BLUE_LED, 0);

  digitalWrite(BUZZER_PIN, LOW);

  noTone(PASSIVE_BUZZER);

  lastSecondPrinted = -1;

  currentState = IDLE;

  Serial.println("Game Reset");
}

// =========================
// START GAME
// =========================

void startGame() {

  resetGame();

  startTime = millis();

  currentState = PLAYING;

  Serial.println("GAME STARTED");
}

// =========================
// PROGRESS SOUND
// =========================

void playProgressSound() {

  int frequencies[] = {262, 330, 392, 494, 587};

  tone(PASSIVE_BUZZER, frequencies[progressCount - 1], 200);
}

// =========================
// LASER BLINK
// =========================

void blinkLaser() {

  digitalWrite(LASER_PIN, HIGH);
  delay(50);

  digitalWrite(LASER_PIN, LOW);
  delay(50);
}

// =========================
// LED FADE
// =========================

void fadeLED(int red, int green, int blue) {

  analogWrite(RED_LED, red);
  analogWrite(GREEN_LED, green);
  analogWrite(BLUE_LED, blue);
}

// =========================
// TIMER
// =========================

void updateTimer() {

  if(currentState != PLAYING) {
    return;
  }

  unsigned long elapsed = millis() - startTime;

  if(elapsed >= TIMER_DURATION) {

    currentState = LOSE_STATE;

    Serial.println("TIME EXPIRED");

    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);

    resetGame();
  }

  else if(elapsed >= 55000) {

    int secLeft = 60 - (elapsed / 1000);

    if(secLeft != lastSecondPrinted) {

      Serial.print("Seconds left: ");
      Serial.println(secLeft);

      lastSecondPrinted = secLeft;
    }
  }
}

// =========================
// INPUTS
// =========================

void handleInputs() {

  if(currentState != PLAYING) {
    return;
  }

  // BUTTON

  if(!digitalRead(BUTTON_PIN) && !buttonProcessed) {

    progressCount++;

    buttonProcessed = true;

    Serial.println("Button pressed");

    playProgressSound();

    delay(150);
  }

  // TOUCH SENSOR

  if(digitalRead(TOUCH_PIN) && !touchProcessed) {

    progressCount++;

    touchProcessed = true;

    Serial.println("Touch detected");

    playProgressSound();

    delay(150);
  }

  // LIGHT SENSOR

  if(analogRead(LIGHT_SENSOR) < LIGHT_THRESHOLD && !lightProcessed) {

    progressCount++;

    lightProcessed = true;

    Serial.println("Light blocked");

    playProgressSound();

    delay(150);
  }

  // ROTARY SWITCH

  bool currentSWState = digitalRead(ROTARY_SW);

  if(lastSWState == HIGH &&
     currentSWState == LOW &&
     !rotarySwitchProcessed) {

    rotaryButtonCount++;

    Serial.print("Rotary button count: ");
    Serial.println(rotaryButtonCount);

    if(rotaryButtonCount >= REQUIRED_SW_PRESSES) {

      progressCount++;

      rotarySwitchProcessed = true;

      playProgressSound();
    }

    delay(50);
  }

  lastSWState = currentSWState;

  // ROTARY ROTATION

  int currentCLKState = digitalRead(ROTARY_CLK);

  if(currentCLKState != lastCLKState) {

    if(digitalRead(ROTARY_DT) != currentCLKState) {

      rotaryRotationCount++;

      Serial.print("Rotations: ");
      Serial.println(rotaryRotationCount);

      if(rotaryRotationCount >= REQUIRED_ROTATIONS) {

        progressCount++;

        rotaryRotationCount = 0;

        playProgressSound();
      }
    }
  }

  lastCLKState = currentCLKState;
}

// =========================
// WIN CONDITION
// =========================

void checkWinCondition() {

  if(progressCount >= TOTAL_SENSORS) {

    currentState = WIN_STATE;

    Serial.println("YOU WIN!");

    playWinAnimation();

    resetGame();
  }
}

// =========================
// WIN ANIMATION
// =========================

void playWinAnimation() {

  for(int repeat = 0; repeat < 3; repeat++) {

    digitalWrite(BUZZER_PIN, HIGH);
    delay(150);
    digitalWrite(BUZZER_PIN, LOW);

    // RED

    for(int i = 20; i <= 255; i += 40) {

      fadeLED(i, 0, 0);

      blinkLaser();
    }

    for(int i = 255; i >= 20; i -= 40) {

      fadeLED(i, 0, 0);

      blinkLaser();
    }

    // GREEN

    for(int i = 20; i <= 255; i += 40) {

      fadeLED(0, i, 0);

      blinkLaser();
    }

    for(int i = 255; i >= 20; i -= 40) {

      fadeLED(0, i, 0);

      blinkLaser();
    }

    // BLUE

    for(int i = 20; i <= 255; i += 40) {

      fadeLED(0, 0, i);

      blinkLaser();
    }

    for(int i = 255; i >= 20; i -= 40) {

      fadeLED(0, 0, i);

      blinkLaser();
    }
  }

  fadeLED(0, 0, 0);
}

// =========================
// MAIN LOOP
// =========================

void loop() {

  // START BUTTON

  if(!digitalRead(START_BUTTON)) {

    startGame();

    delay(200);
  }

  updateTimer();

  handleInputs();

  checkWinCondition();
}
