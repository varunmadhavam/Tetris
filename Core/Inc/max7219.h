#ifndef MAX7219_H
#define MAX7219_H

#include "configs.h"

void max_init(void);
void max_load_low(void);
void max_load_high(void);
void max_send_data(uint16_t data[]);
void max_send_buffer(uint8_t data[MAX_DEVICES][8]);
void max_send_data_r(uint16_t data[]);

#endif
