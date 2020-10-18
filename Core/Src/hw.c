/*
 * hw.c
 *
 *  Created on: 18-Oct-2020
 *      Author: varun
 */
#include "stm32g0xx.h"
#include "configs.h"
#include "delay.h"

uint16_t buff[MAX_DEVICES*8];

static void spi_w16( SPI_TypeDef *SPIx, uint16_t dat[] ) {
  for(int i=0;i<MAX_DEVICES;i++){
	  while ( !( SPIx->SR & SPI_SR_TXE ) ) {};
	   *( uint16_t* )&( SPIx->DR ) = dat[i];
  }

}

static void init_max(void) {
	GPIOA->ODR |= (1<<5);
	DelayMS(1);
	GPIOA->ODR &= ~(1<<5);
	uint16_t serialData[MAX_DEVICES];
	for(uint8_t i=0;i<15;i++) {
		for(uint8_t j=0;j<MAX_DEVICES;j++) {
			serialData[j]=(uint16_t)(i<<8)|((uint16_t)0x00);
		}
		spi_w16(SPI1,serialData);
	}

	for(uint8_t j=0;j<MAX_DEVICES;j++) {
		serialData[j]=(0x0B07);
	}
	spi_w16(SPI1,serialData);

	for(uint8_t j=0;j<MAX_DEVICES;j++) {
		serialData[j]=(0x0C01);
	}
	spi_w16(SPI1,serialData);

	for(uint8_t i=1;i<=8;i++){
		for(uint8_t j=0;j<MAX_DEVICES;j++) {
			serialData[j]=(uint16_t)(i<<8)|((uint16_t)0x00);
		}
	spi_w16(SPI1,serialData);
	}
}

void hw_setup(void) {

	//GPIOA configs

	RCC->IOPENR    |= RCC_IOPENR_GPIOAEN;
	RCC->AHBENR    |= RCC_AHBENR_DMA1EN;
	RCC->APBENR2   |= RCC_APBENR2_SPI1EN;
	GPIOA->MODER   &= ~(0x3<<(1*2) | 0x3<<(2*2) | 0x3<<(4*2) | 0x3<<(5*2));
	GPIOA->MODER   |= (0x2<<(1*2) | 0x2<<(2*2) | 0x2<<(4*2) | 0x1<<(5*2));
	GPIOA->PUPDR   |= ~(0x2<<(5*2));
	GPIOA->AFR[0]  &= ~(0xff<<(1*4) | 0xff<<(2*4) | 0xff<<(4*4));

	GPIOA->ODR     &= ~(1<<5);

	//DMA configs
	DMA1_Channel1->CCR &= ~( DMA_CCR_MEM2MEM |
	                         DMA_CCR_PL |
	                         DMA_CCR_MSIZE |
	                         DMA_CCR_PSIZE |
	                         DMA_CCR_PINC |
	                         DMA_CCR_EN );
	DMA1_Channel1->CCR |=  ( ( 0x2 << DMA_CCR_PL_Pos ) |
	                         ( 0x1 << DMA_CCR_MSIZE_Pos ) |
	                         ( 0x1 << DMA_CCR_PSIZE_Pos ) |
	                         DMA_CCR_MINC |
	                         DMA_CCR_CIRC |
	                         DMA_CCR_DIR );


	DMAMUX1_Channel0->CCR &= ~( DMAMUX_CxCR_DMAREQ_ID );
	DMAMUX1_Channel0->CCR |=  ( 17 << DMAMUX_CxCR_DMAREQ_ID_Pos );

	DMA1_Channel1->CMAR  = ( uint32_t )&buff;
	DMA1_Channel1->CPAR  = ( uint32_t )&(SPI1->DR);
	DMA1_Channel1->CNDTR = ( uint16_t )(MAX_DEVICES*8);

	//SPI configs
	SPI1->CR1 |=  ( SPI_CR1_MSTR | (1<<SPI_CR1_BIDIOE_Pos) | (1<<4) );
	SPI1->CR2 &= ~( SPI_CR2_DS );
	SPI1->CR2 |=  ( 0xf << SPI_CR2_DS_Pos | SPI_CR2_TXDMAEN | 1<<SPI_CR2_NSSP_Pos | 1<<SPI_CR2_SSOE_Pos );
	SPI1->CR1 |=  ( SPI_CR1_SPE );

	init_max();

	DMA1_Channel1->CCR |= ( DMA_CCR_EN );
}

