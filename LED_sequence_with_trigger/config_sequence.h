#pragma once

// ================= Panel dimensions =================
static const int W = 64;
static const int H = 64;

// ================= LED color =================
static const bool USE_RED   = false;
static const bool USE_GREEN = true;
static const bool USE_BLUE  = false;

// ================= Sequence bounds =================
static const int START_ROW = 0;   // y
static const int START_COL = 0;   // x
static const int END_ROW   = 63;   // y
static const int END_COL   = 63;   // x

static const int STEP_COL  = 4;    // dx per trigger
static const int STEP_ROW  = 4;    // dy when x wraps to next row

// ================= Behavior =================
static const bool LOOP_FOREVER = true; // false = stop and blank panel