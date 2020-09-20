#ifndef SHIFTER_H
#define SHIFTER_H

#include "configs.h"

void shiftout(uint16_t data[]);
void shiftoutBuffer(uint8_t data[MAX_DEVICES][8]);
void init_shifter(void);
void shiftout_r(uint16_t data[]);

#endif
