/*
 * buff.c
 *
 *  Created on: 18-Oct-2020
 *      Author: varun
 */
#include "stm32g0xx.h"
#include "hw.h"
uint8_t buff_data[MAX_DEVICES*8];

void build_buffer(void) {
	int k=0;
	   for(int j=0;j<8;j++) {
		   for(int i=0;i<MAX_DEVICES;i++) {
		   buff[k++]=((uint16_t)((j+1)<<8))|((uint16_t)buff_data[(8*i)+j]);
	   }
   }
}

void clear_buff(void) {
	for(int i=0;i<MAX_DEVICES*8;i++)
		buff[i]=0x0000;
}

