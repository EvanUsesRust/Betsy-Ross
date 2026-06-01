// Light Show — 3:29 duration

// Relay pins. LOW = ON for most relay modules.
#define RED_PIN   2
#define WHITE_PIN 3
#define BLUE_PIN  4

#define ON  LOW
#define OFF HIGH


// --- SETUP: pin modes and start dark ---
void setup() {
  pinMode(RED_PIN,   OUTPUT);
  pinMode(WHITE_PIN, OUTPUT);
  pinMode(BLUE_PIN,  OUTPUT);
  allOff();
}

// Turn everything off
void allOff() {
  digitalWrite(RED_PIN,   OFF);
  digitalWrite(WHITE_PIN, OFF);
  digitalWrite(BLUE_PIN,  OFF);
}

// Turn everything on
void allOn() {
  digitalWrite(RED_PIN,   ON);
  digitalWrite(WHITE_PIN, ON);
  digitalWrite(BLUE_PIN,  ON);
}


// --- PHASE 1: 0:00–0:20 — One light at a time, slow ---
void phase1() {
  unsigned long end = millis() + 20000UL;
  int pins[3] = {RED_PIN, WHITE_PIN, BLUE_PIN};
  while (millis() < end) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(pins[i], ON);
      delay(600);
      digitalWrite(pins[i], OFF);
      delay(200);
    }
  }
  allOff();
}

// --- PHASE 2: 0:20–0:45 — Red and blue taking turns ---
void phase2() {
  unsigned long end = millis() + 25000UL;
  while (millis() < end) {
    digitalWrite(RED_PIN,  ON);
    digitalWrite(BLUE_PIN, OFF);
    delay(400);
    digitalWrite(RED_PIN,  OFF);
    digitalWrite(BLUE_PIN, ON);
    delay(400);
  }
  allOff();
}

// --- PHASE 3: 0:45–1:05 — Chase pattern, one light hops to the next ---
void phase3() {
  unsigned long end = millis() + 20000UL;
  int pins[3] = {RED_PIN, WHITE_PIN, BLUE_PIN};
  while (millis() < end) {
    for (int i = 0; i < 3; i++) {
      allOff();
      digitalWrite(pins[i], ON);
      delay(250);
    }
  }
  allOff();
}

// --- PHASE 4: 1:05–1:30 — White strobe ---
void phase4() {
  unsigned long end = millis() + 25000UL;
  while (millis() < end) {
    digitalWrite(WHITE_PIN, ON);
    delay(80);
    digitalWrite(WHITE_PIN, OFF);
    delay(80);
  }
}

// --- PHASE 5: 1:30–1:55 — Red, white, blue rapid flash ---
void phase5() {
  unsigned long end = millis() + 25000UL;
  int pins[3] = {RED_PIN, WHITE_PIN, BLUE_PIN};
  while (millis() < end) {
    for (int i = 0; i < 3; i++) {
      allOff();
      digitalWrite(pins[i], ON);
      delay(180);
      digitalWrite(pins[i], OFF);
      delay(60);
    }
  }
  allOff();
}

// --- PHASE 6: 1:55–2:20 — All lights breathing on and off slowly ---
void phase6() {
  unsigned long end = millis() + 25000UL;
  while (millis() < end) {
    allOn();
    delay(800);
    allOff();
    delay(800);
  }
}

// --- PHASE 7: 2:20–2:50 — Red+blue vs white, alternating fast ---
void phase7() {
  unsigned long end = millis() + 30000UL;
  while (millis() < end) {
    digitalWrite(RED_PIN,   ON);
    digitalWrite(WHITE_PIN, OFF);
    digitalWrite(BLUE_PIN,  ON);
    delay(200);
    digitalWrite(RED_PIN,   OFF);
    digitalWrite(WHITE_PIN, ON);
    digitalWrite(BLUE_PIN,  OFF);
    delay(200);
  }
  allOff();
}

// --- PHASE 8: 2:50–3:29 — Grand finale, strobe speeds up to the end ---
void phase8() {
  unsigned long end = millis() + 39000UL;
  int step = 50;
  while (millis() < end) {
    // Flash rate gets faster as the song nears the end
    unsigned long remaining = end - millis();
    if      (remaining > 25000UL) step = 60;
    else if (remaining > 15000UL) step = 40;
    else if (remaining > 5000UL)  step = 25;
    else                          step = 12;

    allOn();
    delay(step);
    allOff();
    delay(step);
  }

  // Hold all lights on for one last second, then out
  allOn();
  delay(1000);
  allOff();
}


// --- LOOP: run the show once, then stay dark ---
void loop() {
  phase1();  // 0:00 – 0:20
  phase2();  // 0:20 – 0:45
  phase3();  // 0:45 – 1:05
  phase4();  // 1:05 – 1:30
  phase5();  // 1:30 – 1:55
  phase6();  // 1:55 – 2:20
  phase7();  // 2:20 – 2:50
  phase8();  // 2:50 – 3:29

  // Done — sit dark until next power cycle
  while (true) { allOff(); }
}
