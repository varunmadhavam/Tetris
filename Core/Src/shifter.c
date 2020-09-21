#include "stm32g0xx_hal.h"
#include "configs.h"
#include "shifter.h"

SPI_HandleTypeDef hspi1;
uint8_t temp;

void init_shifter(void) {
	MX_GPIO_Init();
	DATAR -> ODR &= ~DATAP;
	CLKR  -> ODR &= ~CLKP;
	LOADR -> ODR &= ~LOADP;
	MX_SPI1_Init();
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

void shiftout_spi(uint16_t data[]) {
	for(int j=0;j<MAX_DEVICES;j++) {
		  temp=(uint8_t)(data[j]>>8);
		  HAL_SPI_Transmit(&hspi1,&temp, 1, 100);
		  temp=(uint8_t)(data[j]&0xFF);
		  HAL_SPI_Transmit(&hspi1,&temp, 1, 100);
	}
}

void shiftout_spi_r(uint16_t data[]) {
	for(int j=MAX_DEVICES-1;j>=0;j--) {
		  temp=(uint8_t)(data[j]>>8);
		  HAL_SPI_Transmit(&hspi1,&temp, 1, 100);
		  temp=(uint8_t)(data[j]&0xFF);
		  HAL_SPI_Transmit(&hspi1,&temp, 1, 100);
	}
}





void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_15|GPIO_PIN_6, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_15|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}


void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

