/*
 * delay.c
 *
 *  Created on: 14-Oct-2020
 *      Author: varun
 */
#include "stm32g0xx.h"
#include "systick.h"


void DelayMS(uint32_t Delay)
{
  uint32_t tickstart = tick;
  while ((tick - tickstart) < Delay)
  {
  }
}

