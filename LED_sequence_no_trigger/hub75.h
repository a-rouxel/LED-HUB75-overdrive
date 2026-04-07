#pragma once
#include <Arduino.h>
#include "config_hardware.h"
#include "config_sequence.h"

void hub75_init();
void showPixel(int x, int y, bool r, bool g, bool b);
