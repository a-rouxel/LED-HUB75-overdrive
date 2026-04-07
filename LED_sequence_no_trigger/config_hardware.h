#pragma once

// ================= RGB data pins =================
static const int PIN_R1  = 25;
static const int PIN_G1  = 26;
static const int PIN_B1  = 27;
static const int PIN_R2  = 14;
static const int PIN_G2  = 12;
static const int PIN_B2  = 13;

// ================= Row address pins =================
static const int PIN_A   = 23;
static const int PIN_B   = 22;
static const int PIN_C   = 18;
static const int PIN_D   = 33;
static const int PIN_E   = 32;

// ================= Control pins =================
static const int PIN_CLK = 5;
static const int PIN_LAT = 4;
static const int PIN_OE  = 15;   // OE usually active-LOW

// ================= Trigger pin =================
static const int  TRIG_PIN       = 35;    // input-only; no internal pulls
static const bool TRIG_ON_RISING = true;

// ================= Trigger timing =================
static const uint32_t MIN_GAP_US    = 5000;  // ignore edges within 5ms of last accept
static const uint32_t LOW_REARM_US  = 3000;  // require LOW for 3ms to re-arm
static const uint32_t START_AT      = 1;     // first accepted trigger that advances
static const uint32_t TRIG_INTERVAL = 1;     // advance every N accepted triggers
