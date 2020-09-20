#include "stm32g0xx_hal.h"
#include "configs.h"
#include "shifter.h"
#include "max7219.h"


void max_init(void) {
	uint16_t serialData[MAX_DEVICES];
	init_shifter();
	for(uint8_t i=0;i<15;i++){
		for(uint8_t j=0;j<MAX_DEVICES;j++) {
			serialData[j]=(uint16_t)(i<<8)|((uint16_t)0x0000);
		}
		max_send_data(serialData);
	}

	for(uint8_t j=0;j<MAX_DEVICES;j++) {
				serialData[j]=0x0B07;
			}
	max_send_data(serialData);

	for(uint8_t j=0;j<MAX_DEVICES;j++) {
				serialData[j]=0x0C01;
			}
	max_send_data(serialData);
}

void max_load_low(void) {
	LOADR -> ODR &= ~LOADP;
}

void max_load_high(void) {
	LOADR -> ODR |=  LOADP;
}

void max_send_data(uint16_t data[]) {
	max_load_low();
	shiftout(data);
	max_load_high();
}

void max_send_data_r(uint16_t data[]) {
	max_load_low();
	shiftout_r(data);
	max_load_high();
}

void max_send_buffer(uint8_t data[MAX_DEVICES][8]) {
	max_load_low();
	shiftoutBuffer(data);
	max_load_high();
}
