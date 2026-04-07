#include "config_sequence.h"
#include "config_hardware.h"
#include "hub75.h"
#include "trigger.h"

// ================= Simple stepper derived from bounds =================
struct BoundStepper {
  int x, y;

  void init(int startX, int startY) {
    x = startX;
    y = startY;
  }

  void next() {
    x += STEP_COL;

    if (x < 0 || x >= END_COL) {
      x = START_COL;
      y += STEP_ROW;

      if (y < 0 || y >= END_ROW) {
        y = START_ROW;
        x = START_COL;
      }
    }
  }
};

BoundStepper stepper;

// ================= Setup / Loop =================
void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("==== Triggered single-LED stepper (bounds-derived) ====");

  hub75_init();
  trigger_init();

  stepper.init(START_COL, START_ROW);
  showPixel(stepper.x, stepper.y, USE_RED, USE_GREEN, USE_BLUE);
  Serial.printf("[BOOT] Showing (x=%d,y=%d)\n", stepper.x, stepper.y);
}

void loop() {
  if (trigFlag) {
    noInterrupts();
    trigFlag = false;
    uint32_t count = trigCount;
    uint32_t tEdge = lastEdgeUs;
    interrupts();

    Serial.printf("[TRIG] #%u at %lu us\n", (unsigned)count, (unsigned long)tEdge);

    if (count >= START_AT && ((count - START_AT) % TRIG_INTERVAL == 0)) {
      stepper.next();
      showPixel(stepper.x, stepper.y, USE_RED, USE_GREEN, USE_BLUE);
      Serial.printf("  --> show (x=%d,y=%d)\n", stepper.x, stepper.y);
    }
  }

  if (!armed) {
    if (tryRearm()) {
      Serial.println("[REARM] LOW stable; armed=true");
    }
  }

  delay(1);
}
