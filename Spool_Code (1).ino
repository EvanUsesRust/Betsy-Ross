#include <Servo.h>

// The three servos on the spool rig
Servo servo1;
Servo servo2;
Servo servo3;

// Where each servo currently is and where it's trying to get to
int pos1 = 90, pos2 = 90, pos3 = 90;
int target1 = 90, target2 = 90, target3 = 90;

// Tracks the last time each servo moved and how long to wait before moving again
unsigned long lastMove1 = 0, lastMove2 = 0, lastMove3 = 0;
unsigned long interval1 = 0, interval2 = 0, interval3 = 0;

// Relay is wired to pin 10 and controls the bubble machine
#define RELAY_PIN 10

// 3 minutes 25 seconds in milliseconds — that's when the bubbles kick on
#define BUBBLE_DELAY 205000

bool bubbleOn = false;


// --- SETUP: runs once when the board powers on ---
void setup() {
  servo1.attach(7);
  servo2.attach(6);
  servo3.attach(5);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // bubbles off to start

  randomSeed(analogRead(0)); // seed randomness from noise on pin A0

  // Start all servos centered
  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);

  // Pick random starting wait times for each servo
  interval1 = random(300, 2000);
  interval2 = random(300, 2000);
  interval3 = random(300, 2000);
}


// --- LOOP: runs over and over forever ---
void loop() {
  unsigned long now = millis();

  // Turn the bubble machine on after the delay has passed
  if (!bubbleOn && now >= BUBBLE_DELAY) {
    digitalWrite(RELAY_PIN, HIGH);
    bubbleOn = true;
  }

  // Servo 1 — pick a new target angle when the wait time is up, then nudge toward it
  if (now - lastMove1 >= interval1) {
    target1 = random(0, 181);
    interval1 = random(300, 2000);
    lastMove1 = now;
  }
  if (pos1 < target1) pos1++;
  else if (pos1 > target1) pos1--;
  servo1.write(pos1);

  // Servo 2 — same deal as servo 1
  if (now - lastMove2 >= interval2) {
    target2 = random(0, 181);
    interval2 = random(300, 2000);
    lastMove2 = now;
  }
  if (pos2 < target2) pos2++;
  else if (pos2 > target2) pos2--;
  servo2.write(pos2);

  // Servo 3 — same deal as the others
  if (now - lastMove3 >= interval3) {
    target3 = random(0, 181);
    interval3 = random(300, 2000);
    lastMove3 = now;
  }
  if (pos3 < target3) pos3++;
  else if (pos3 > target3) pos3--;
  servo3.write(pos3);

  delay(10); // tiny pause so the servos don't get flooded with commands
}
