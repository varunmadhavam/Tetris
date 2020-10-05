
#include "main.h"
#include "stm32g071xx.h"
#define MAX_DEVICES 1

void SystemClock_Config(void);
uint16_t buff[MAX_DEVICES][8];
void spi_w16( SPI_TypeDef *SPIx, uint16_t dat[] ) {
  for(int i=0;i<MAX_DEVICES;i++){
	  while ( !( SPIx->SR & SPI_SR_TXE ) ) {};
	   *( uint16_t* )&( SPIx->DR ) = dat[i];
  }

}

void init_max(void) {
	uint16_t serialData[MAX_DEVICES];
	for(uint8_t i=0;i<15;i++){
		for(uint8_t j=0;j<MAX_DEVICES;j++) {
			serialData[j]=(uint16_t)(i<<8)|((uint16_t)0x0000);
		}
		spi_w16(SPI1,serialData);
	}

	for(uint8_t j=0;j<MAX_DEVICES;j++) {
				serialData[j]=0x0B07;
			}
	spi_w16(SPI1,serialData);

	for(uint8_t j=0;j<MAX_DEVICES;j++) {
				serialData[j]=0x0C01;
			}
	spi_w16(SPI1,serialData);
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  //GPIOA configs

  RCC->IOPENR    |= RCC_IOPENR_GPIOAEN;
  RCC->AHBENR    |= RCC_AHBENR_DMA1EN;
  RCC->APBENR2   |= RCC_APBENR2_SPI1EN;
  GPIOA->MODER   &= ~(0x3<<(1*2) | 0x3<<(2*2) | 0x3<<(4*2));
  GPIOA->MODER   |= (0x2<<(1*2) | 0x2<<(2*2) | 0x2<<(4*2));
  GPIOA->OTYPER  &= ~((0x1<<1) | (0x1<<2) | (0x1<<4));
  GPIOA->OSPEEDR &= ~(0x2<<(1*2) | 0x2<<(2*2) | 0x2<<(4*2));
  GPIOA->PUPDR   &= ~(0x2<<(1*2) | 0x2<<(2*2) | 0x2<<(4*2));
  GPIOA->AFR[0]  &= ~(0xff<<(1*4) | 0xff<<(2*4) | 0xff<<(4*4));

  //SPI configs
  SPI1->CR1 |=  ( SPI_CR1_MSTR | (1<<SPI_CR1_BIDIOE_Pos) );
  SPI1->CR2 &= ~( SPI_CR2_DS );
  SPI1->CR2 |=  ( 0xf << SPI_CR2_DS_Pos | SPI_CR2_TXDMAEN | 1<<SPI_CR2_NSSP_Pos | 1<<SPI_CR2_SSOE_Pos );

  SPI1->CR1 |=  ( SPI_CR1_SPE );

  init_max();
  //spi_w16(SPI1,0x0255);
  //spi_w16(SPI1,0x03AA);


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
  DMA1_Channel1->CPAR  = ( uint32_t )&( SPI1->DR );
  DMA1_Channel1->CNDTR = ( uint16_t )MAX_DEVICES*8;

  buff[0][0]=0x0100;
    buff[0][1]=0x0200;
    buff[0][2]=0x0300;
    buff[0][3]=0x0400;
    buff[0][4]=0x0500;
    buff[0][5]=0x0600;
    buff[0][6]=0x0700;
    buff[0][7]=0x0800;

    DMA1_Channel1->CCR |= ( DMA_CCR_EN );

  buff[0][0]=0x01ff;
  buff[0][1]=0x0200;
  buff[0][2]=0x0300;
  buff[0][3]=0x0400;
  buff[0][4]=0x0500;
  buff[0][5]=0x0600;
  buff[0][6]=0x0700;
  buff[0][7]=0x08ff;



}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}



void Error_Handler(void)
{

}
