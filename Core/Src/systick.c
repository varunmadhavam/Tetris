/*
 * systick.c
 *
 *  Created on: 14-Oct-2020
 *      Author: varun
 */

//Setup ISR for sysytick.


#include "stm32g0xx.h"
#include "core_cm0plus.h"
#include "system_stm32g0xx.h"

volatile uint32_t tick=0;

void systick_enable() {
	uint32_t ticks=(SystemCoreClock/1000UL)-1UL;
	SysTick_Config(ticks);
}
