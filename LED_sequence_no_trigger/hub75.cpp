#include "hub75.h"

static inline void pulseCLK() {
  digitalWrite(PIN_CLK, HIGH);
  delayMicroseconds(1);
  digitalWrite(PIN_CLK, LOW);
  delayMicroseconds(1);
}

static inline void pulseLAT() {
  digitalWrite(PIN_LAT, HIGH);
  delayMicroseconds(1);
  digitalWrite(PIN_LAT, LOW);
  delayMicroseconds(1);
}

static inline void setRowAddress(uint8_t row /*0..31*/) {
  digitalWrite(PIN_A, (row >> 0) & 1);
  digitalWrite(PIN_B, (row >> 1) & 1);
  digitalWrite(PIN_C, (row >> 2) & 1);
  digitalWrite(PIN_D, (row >> 3) & 1);
  digitalWrite(PIN_E, (row >> 4) & 1);
}

static inline void setRGBTop(bool r, bool g, bool b) {
  digitalWrite(PIN_R1, r);
  digitalWrite(PIN_G1, g);
  digitalWrite(PIN_B1, b);
}

static inline void setRGBBottom(bool r, bool g, bool b) {
  digitalWrite(PIN_R2, r);
  digitalWrite(PIN_G2, g);
  digitalWrite(PIN_B2, b);
}

void hub75_init() {
  pinMode(PIN_R1, OUTPUT); pinMode(PIN_G1, OUTPUT); pinMode(PIN_B1, OUTPUT);
  pinMode(PIN_R2, OUTPUT); pinMode(PIN_G2, OUTPUT); pinMode(PIN_B2, OUTPUT);

  pinMode(PIN_A, OUTPUT);  pinMode(PIN_B, OUTPUT);  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);  pinMode(PIN_E, OUTPUT);

  pinMode(PIN_CLK, OUTPUT);
  pinMode(PIN_LAT, OUTPUT);
  pinMode(PIN_OE,  OUTPUT);

  digitalWrite(PIN_CLK, LOW);
  digitalWrite(PIN_LAT, LOW);
  digitalWrite(PIN_OE, HIGH); // start disabled
}

void showPixel(int x, int y, bool r, bool g, bool b) {
  if (x < 0) x = 0; if (x >= W) x = W - 1;
  if (y < 0) y = 0; if (y >= H) y = H - 1;

  const uint8_t rowPair = (uint8_t)(y & 31);
  const bool topHalf = (y < 32);

  digitalWrite(PIN_OE, HIGH); // disable while updating
  setRowAddress(rowPair);

  for (int col = 0; col < W; col++) {
    const bool hit = (col == x);

    bool r1=false,g1=false,b1=false;
    bool r2=false,g2=false,b2=false;

    if (hit && topHalf)  { r1=r; g1=g; b1=b; }
    if (hit && !topHalf) { r2=r; g2=g; b2=b; }

    setRGBTop(r1,g1,b1);
    setRGBBottom(r2,g2,b2);

    pulseCLK();
  }

  pulseLAT();
  setRowAddress(rowPair);
  digitalWrite(PIN_OE, LOW);  // enable continuously
}
