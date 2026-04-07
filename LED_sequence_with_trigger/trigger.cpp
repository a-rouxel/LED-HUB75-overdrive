#include "trigger.h"

volatile bool     trigFlag     = false;
volatile uint32_t trigCount    = 0;
volatile uint32_t lastAcceptUs = 0;
volatile uint32_t lastEdgeUs   = 0;
volatile bool     armed        = true;

void IRAM_ATTR onTrigISR() {
  uint32_t now = micros();
  if (!armed) return;
  if (now - lastAcceptUs < MIN_GAP_US) return;

  lastEdgeUs   = now;
  lastAcceptUs = now;
  trigCount++;
  trigFlag = true;
  armed = false;
}

bool tryRearm() {
  static uint32_t lowSince = 0;
  uint32_t now = micros();
  int level = digitalRead(TRIG_PIN);

  if (level == LOW) {
    if (lowSince == 0) lowSince = now;
    if ((now - lowSince) >= LOW_REARM_US) {
      armed = true;
      lowSince = 0;
      return true;
    }
  } else {
    lowSince = 0;
  }
  return false;
}

void trigger_init() {
  pinMode(TRIG_PIN, INPUT);
  attachInterrupt(
    digitalPinToInterrupt(TRIG_PIN),
    onTrigISR,
    TRIG_ON_RISING ? RISING : FALLING
  );
}
