
#include "main.h"
#include "stm32g071xx.h"

void SystemClock_Config(void);

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



  //DMA configs
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
