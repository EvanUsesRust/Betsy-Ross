# Betsy-Ross

Arduino-based animatronic project with three independently controlled modules: a spool rig, an animated face, and a synchronized light show.

---

## Files

| File | What it does |
|---|---|
| `Spool_Code.ino` | Drives three servos in random wandering motion + fires a bubble machine relay |
| `Face_Code.ino` | Controls a mouth, two eyelids, and two eyeballs on an animatronic face |
| `Light_Show.ino` | Runs a timed 8-phase red/white/blue light show across three relay-controlled lights |

---

## Spool Code

Three servos move independently and randomly. Each one picks a new target angle at random intervals and slowly sweeps toward it one degree at a time, giving a natural wandering feel rather than snapping around. A relay on pin 10 turns on a bubble machine after **3 minutes and 25 seconds** and stays on for the rest of the session.

**Pin wiring:**

| Component | Pin |
|---|---|
| Servo 1 | 7 |
| Servo 2 | 6 |
| Servo 3 | 5 |
| Bubble machine relay | 10 |

To change the bubble delay, edit `BUBBLE_DELAY` at the top of the file (value is in milliseconds).

---

## Face Code

Runs three independent systems at the same time without blocking each other:

**Mouth** — plays back a pre-recorded sequence of open/closed positions stored in flash memory (`PROGMEM`). The sequence runs once and the mouth closes when it's done.

**Eyes** — the right eye wanders slowly around center using a smooth easing curve. The left eye mirrors it automatically. Most of the time the eyes stay near center (`CENTER_BIAS = 0.85`), occasionally drifting further out. If the left eye moves the wrong direction, swap `EYE_LEFT_MIN` and `EYE_LEFT_MAX` in the `mirrorEye()` function.

**Eyelids** — blink automatically every 4–6 seconds. The blink steps through close → hold → open using a simple state machine so nothing else gets paused while it happens.

**Pin wiring:**

| Component | Pin |
|---|---|
| Mouth servo | 7 |
| Left eyelid servo | 9 |
| Right eyelid servo | 11 |
| Left eyeball servo | 8 |
| Right eyeball servo | 10 |

**Tuning tips:**
- `CENTER_BIAS` — how often eyes return to center vs wander (0.0–1.0)
- `WANDER_RANGE` — max degrees of eye drift from center
- `BLINK_INTERVAL_MIN/MAX` — how often the eyes blink (milliseconds)

---

## Light Show

An 8-phase timed light show built around three relays (red, white, blue). Runs once through the full 3:29 sequence and then goes dark. The phases are:

| Phase | Time | Effect |
|---|---|---|
| 1 | 0:00–0:20 | Slow solo sequence, one light at a time |
| 2 | 0:20–0:45 | Red and blue alternating |
| 3 | 0:45–1:05 | Three-light chase |
| 4 | 1:05–1:30 | White strobe |
| 5 | 1:30–1:55 | Red, white, blue rapid flash |
| 6 | 1:55–2:20 | All lights breathing on/off slowly |
| 7 | 2:20–2:50 | Red+blue vs white alternating fast |
| 8 | 2:50–3:29 | Grand finale strobe that speeds up to the end |

**Pin wiring:**

| Component | Pin |
|---|---|
| Red relay | 2 |
| White relay | 3 |
| Blue relay | 4 |

> These are written for relay modules where **LOW = ON**. If your relays work the opposite way, swap the `ON` and `OFF` defines at the top of the file.

---

## Dependencies

- **Servo.h** — built into the Arduino IDE, no install needed.

All three sketches use only the standard Arduino library.

---

## Upload Instructions

1. Open the `.ino` file in the Arduino IDE.
2. Select your board under **Tools > Board** (e.g. Arduino Uno).
3. Select the correct port under **Tools > Port**.
4. Click **Upload**.

Each file is its own standalone sketch — upload them to separate boards or swap between them as needed.
