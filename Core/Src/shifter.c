#include "stm32g0xx_hal.h"
#include "configs.h"
#include "shifter.h"

void init_shifter(void) {
	DATAR -> ODR &= ~DATAP;
	CLKR  -> ODR &= ~CLKP;
	LOADR -> ODR &= ~LOADP;
}

void shiftout(uint16_t data[]) {
	for(int j=0;j<MAX_DEVICES;j++) {
		for(int i=15;i>=0;i--) {
			if((data[j]>>i)&1) {
				DATAR -> ODR |=  DATAP;
			}
			else {
				DATAR -> ODR &= ~DATAP;
			}
			CLKR -> ODR |=  CLKP;
			CLKR -> ODR &= ~CLKP;
		}
	}
}

void shiftout_r(uint16_t data[]) {
	for(int j=MAX_DEVICES-1;j>=0;j--) {
		for(int i=15;i>=0;i--) {
			if((data[j]>>i)&1) {
				DATAR -> ODR |=  DATAP;
			}
			else {
				DATAR -> ODR &= ~DATAP;
			}
			CLKR -> ODR |=  CLKP;
			CLKR -> ODR &= ~CLKP;
		}
	}
}

void shiftoutBuffer(uint8_t data[MAX_DEVICES][8]) {
    for(uint8_t k=0;k<8;k++) {
    	for(uint8_t j=0;j<MAX_DEVICES;j++) {
    		for(uint8_t i=7;i>=0;i--) {
    			if((data[j][k]>>i)&1) {
    				DATAR -> ODR |=  DATAP;
    			}
    			else {
    				DATAR -> ODR &= ~DATAP;
    			}
    			CLKR -> ODR |=  CLKP;
    			CLKR -> ODR &= ~CLKP;
    		}
        }
   }
}


