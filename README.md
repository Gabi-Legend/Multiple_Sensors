# 🕹️ Arduino Sensor Labyrinth

This project is an interactive Arduino-based labyrinth using multiple sensors. The goal is to trigger all sensors in sequence within 60 seconds to complete the challenge.

## ⚡ Features

### Sensors & Inputs
- **Push Button** – The first step in the labyrinth
- **Touch Sensor (KY-036)** – Activate by touch
- **Light Sensor (LDR)** – Trigger by covering or blocking light (threshold: <400)
- **Rotary Encoder** – Two challenges:
  - Rotate to the right **three times** to progress
  - Press the switch **three times** to progress
- **Start/Reset Button** – Begin the game or reset progress

### Feedback System
- **RGB LED** – Progressive visual feedback with color-changing animation upon completion
- **Laser Module** – Flashes in sync with RGB LED animation
- **Active Buzzer** – Victory sound sequence when labyrinth is completed
- **Passive Buzzer** – Progressive audio feedback with increasing pitch (C → E → G → B → D) as you complete each sensor

### Timer System
- **60-second countdown** – Complete all challenges before time runs out
- **5-second warning** – Serial Monitor shows countdown in the last 5 seconds
- **Time's up alarm** – Buzzer sounds and game resets if timer expires

## 📝 How to Use

1. **Press the Start/Reset button** to begin the 60-second timer
2. **Press the push button** (hear first tone - C note)
3. **Touch the sensor** (hear second tone - E note)
4. **Cover the light sensor** (hear third tone - G note)
5. **Press the rotary encoder switch 3 times** (hear fourth tone - B note)
6. **Rotate the rotary encoder to the right 3 times** (hear fifth tone - D note)
7. Once all steps are completed:
   - Passive buzzer stops
   - Active buzzer plays victory sequence (3 beeps)
   - RGB LED and laser create an infinite color-cycling animation
   - Serial Monitor displays "FELICITARI! AI CASTIGAT!"

## 🛠️ Hardware Requirements

### Components
- Arduino Uno (or compatible)
- Push button
- KY-036 touch sensor
- LDR light sensor (with resistor for analog reading)
- Rotary encoder (with CLK, DT, and SW pins)
- RGB LED (common cathode)
- Active buzzer
- Passive buzzer
- Laser module
- Jumper wires and breadboard

### Pin Configuration
```
Push Button        → Pin 6 (INPUT_PULLUP)
Touch Sensor       → Pin 7 (INPUT)
Laser Module       → Pin 8 (OUTPUT)
Red LED            → Pin 9 (PWM)
Green LED          → Pin 10 (PWM)
Blue LED           → Pin 11 (PWM)
Active Buzzer      → Pin 12 (OUTPUT)
Passive Buzzer     → Pin A4 (OUTPUT)
Rotary SW          → Pin 5 (INPUT_PULLUP)
Rotary CLK         → Pin 3 (INPUT)
Rotary DT          → Pin 4 (INPUT)
Start/Reset Button → Pin 2 (INPUT_PULLUP)
Light Sensor (LDR) → Pin A5 (ANALOG INPUT)
```

## 💻 Software Features

- **Non-blocking timer** – Game runs in real-time without freezing
- **Debouncing** – Prevents accidental multiple triggers
- **State management** – Each sensor can only be triggered once per game
- **Serial debugging** – Real-time feedback in Serial Monitor (9600 baud)
- **Progressive audio feedback** – Musical notes increase in pitch with each completed step
- **Smooth LED animations** – PWM-controlled fading effects

## 💡 Notes

- The sequence of sensor activation **must be followed** in order
- Serial Monitor (9600 baud) shows progress and sensor activations
- All sensors reset when the Start/Reset button is pressed
- Game automatically resets if 60-second timer expires
- Passive buzzer provides audio progress tracking with increasing musical notes
- Victory animation runs indefinitely until manually reset

## 🎯 Learning Outcomes

This project demonstrates:
- Digital and analog input handling
- Rotary encoder reading and debouncing
- PWM control for LED brightness
- Timer and state management
- Audio feedback with tone generation
- Serial communication for debugging
- Multi-sensor integration in a single project

---

**Have fun solving the labyrinth! 🚀**
