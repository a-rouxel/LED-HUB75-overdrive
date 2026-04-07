#include "config_sequence.h"
#include "config_hardware.h"
#include "hub75.h"

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

static const uint32_t STEP_DELAY_MS = 500;

// ================= Setup / Loop =================
void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("==== Test mode: auto-step every 500ms (no trigger) ====");

  hub75_init();

  stepper.init(START_COL, START_ROW);
  showPixel(stepper.x, stepper.y, USE_RED, USE_GREEN, USE_BLUE);
  Serial.printf("[BOOT] Showing (x=%d,y=%d)\n", stepper.x, stepper.y);
}

void loop() {
  delay(STEP_DELAY_MS);

  stepper.next();
  showPixel(stepper.x, stepper.y, USE_RED, USE_GREEN, USE_BLUE);
  Serial.printf("  --> show (x=%d,y=%d)\n", stepper.x, stepper.y);
}
