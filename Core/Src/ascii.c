/*
 * ascii.c
 *
 *  Created on: 19-Sep-2020
 *      Author: varun
 */
#include "stm32g0xx_hal.h"
#include "configs.h"
#include "max7219.h"
#include "ascii.h"
#include <string.h>

uint8_t max_7219_buffer[MAX_DEVICES][8];

void printBuffer(void) {
	uint16_t data[MAX_DEVICES];
	for(uint8_t i=1;i<=8;i++){
		for(uint8_t j=0;j<MAX_DEVICES;j++){
			data[j]=((uint16_t)(i<<8))|(max_7219_buffer[j][i-1]);
		}
		max_send_data_r(data);
	}
}

void updateBuffer(void) {
	static uint8_t i=0;
	initBuffer();
	max_7219_buffer[i][0]=0b11000000;
	max_7219_buffer[i][1]=0b11000000;
	max_7219_buffer[i][2]=0b11000000;
	max_7219_buffer[i][3]=0b11000000;
	max_7219_buffer[i][4]=0b11111100;
	max_7219_buffer[i][5]=0b11000010;
	max_7219_buffer[i][6]=0b11000010;
	max_7219_buffer[i][7]=0b11111100;
	i++;
	if(i==4)
		i=0;
}

void initBuffer(void) {
	for(uint8_t i=0;i<MAX_DEVICES;i++) {
		for(uint8_t j=0;j<8;j++){
			max_7219_buffer[i][j]=0b00000000;
		}
	}
	printBuffer();
}


