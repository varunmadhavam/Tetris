/*
 * rcc.c
 *
 *  Created on: 14-Oct-2020
 *      Author: varun
 */
#include "stm32g0xx.h"
#include "system_stm32g0xx.h"

void sysclock_config(void){
	//select voltage scaling range 1 for high frequency operation.
	PWR->CR1  |= 1<<9;

	//enable flash prefetch buffer.
	FLASH->ACR   |=  (1<<8);

	//enable 2 flash wait states for F <= 64Mhz
	FLASH->ACR &= ~( FLASH_ACR_LATENCY );
	FLASH->ACR |=  ( 2 << FLASH_ACR_LATENCY_Pos );

	//Set the prescalers for 64Mhz
	RCC->PLLCFGR &= ~( RCC_PLLCFGR_PLLR |
	                   RCC_PLLCFGR_PLLREN |
	                   RCC_PLLCFGR_PLLN |
	                   RCC_PLLCFGR_PLLM |
	                   RCC_PLLCFGR_PLLSRC );
	RCC->PLLCFGR |=  ( 1 << RCC_PLLCFGR_PLLR_Pos |
	                   8 << RCC_PLLCFGR_PLLN_Pos |
	                   RCC_PLLCFGR_PLLREN |
	                   2 << RCC_PLLCFGR_PLLSRC_Pos );
	RCC->CR   |= RCC_CR_PLLON;
	while ( !( RCC->CR & RCC_CR_PLLRDY ) ) {};
	RCC->CFGR &= ~( RCC_CFGR_SW );
	RCC->CFGR |=  ( 2 << RCC_CFGR_SW_Pos );
	while ( ( RCC->CFGR & RCC_CFGR_SWS ) >> RCC_CFGR_SWS_Pos != 2 ) {};

	//System clock is now 64Mhz
	SystemCoreClock = 64000000;
}

