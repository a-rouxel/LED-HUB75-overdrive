#pragma once
#include <Arduino.h>
#include "config_hardware.h"

extern volatile bool     trigFlag;
extern volatile uint32_t trigCount;
extern volatile uint32_t lastAcceptUs;
extern volatile uint32_t lastEdgeUs;
extern volatile bool     armed;

void IRAM_ATTR onTrigISR();
bool tryRearm();
void trigger_init();
