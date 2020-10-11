
#include "main.h"
#include "stm32g071xx.h"
#define MAX_DEVICES 4
#define ANIMDELAY 110

void SystemClock_Config(void);

uint16_t buff[MAX_DEVICES*8];
uint8_t buff_data[MAX_DEVICES*8];

void build_buffer(void) {
	int k=0;
	   for(int j=0;j<8;j++) {
		   for(int i=0;i<MAX_DEVICES;i++) {
		   buff[k++]=((uint16_t)((j+1)<<8))|((uint16_t)buff_data[(8*i)+j]);
	   }
   }
}

void delay_cycles( uint32_t cyc ) {
  for ( uint32_t d_i = 1000; d_i < cyc; d_i++ )
  {
	  asm( "NOP" );
  }
}

void clear_buff(void) {
	for(int i=0;i<MAX_DEVICES*8;i++)
		buff[i]=0x0000;
}

void spi_w16( SPI_TypeDef *SPIx, uint16_t dat[] ) {
  for(int i=0;i<MAX_DEVICES;i++){
	  while ( !( SPIx->SR & SPI_SR_TXE ) ) {};
	   *( uint16_t* )&( SPIx->DR ) = dat[i];
  }

}

void init_max(void) {
	GPIOA->ODR |= (1<<5);
	GPIOA->ODR &= ~(1<<5);
	uint16_t serialData[MAX_DEVICES];
	for(uint8_t i=0;i<15;i++){
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

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  //GPIOA configs

  RCC->IOPENR    |= RCC_IOPENR_GPIOAEN;
  RCC->AHBENR    |= RCC_AHBENR_DMA1EN;
  RCC->APBENR2   |= RCC_APBENR2_SPI1EN;
  GPIOA->MODER   &= ~(0x3<<(1*2) | 0x3<<(2*2) | 0x3<<(4*2) | 0x3<<(5*2));
  GPIOA->MODER   |= (0x2<<(1*2) | 0x2<<(2*2) | 0x2<<(4*2) | 0x1<<(5*2));
  //GPIOA->OTYPER  &= ~((0x1<<1) | (0x1<<2) | (0x1<<4));
  //GPIOA->OSPEEDR &= ~(0x2<<(1*2) | 0x2<<(2*2) | 0x2<<(4*2) | 0x2<<(5*2));
  //GPIOA->PUPDR   &= ~(0x2<<(1*2) | 0x2<<(2*2) | 0x2<<(4*2));
  GPIOA->PUPDR   |= ~(0x2<<(5*2));
  GPIOA->AFR[0]  &= ~(0xff<<(1*4) | 0xff<<(2*4) | 0xff<<(4*4));

  GPIOA->ODR &= ~(1<<5);
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
  SPI1->CR1 |=  ( SPI_CR1_MSTR | (1<<SPI_CR1_BIDIOE_Pos) );
  SPI1->CR2 &= ~( SPI_CR2_DS );
  SPI1->CR2 |=  ( 0xf << SPI_CR2_DS_Pos | SPI_CR2_TXDMAEN | 1<<SPI_CR2_NSSP_Pos | 1<<SPI_CR2_SSOE_Pos );

  SPI1->CR1 |=  ( SPI_CR1_SPE );
  init_max();

  //HAL_Delay(500);
  clear_buff();

  DMA1_Channel1->CCR |= ( DMA_CCR_EN );

while(1) {

    buff_data[0]=0b00100000;buff_data[8] =0b00010000;buff_data[16]=0b00000001;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00010000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00000000;buff_data[10]=0b00010000;buff_data[18]=0b00000000;buff_data[26]=0b00000000;
    buff_data[3]=0b00000000;buff_data[11]=0b00010000;buff_data[19]=0b00001000;buff_data[27]=0b00011000;
    buff_data[4]=0b00000000;buff_data[12]=0b00010000;buff_data[20]=0b00001000;buff_data[28]=0b00011000;
    buff_data[5]=0b00000000;buff_data[13]=0b00010000;buff_data[21]=0b00000000;buff_data[29]=0b00000000;
    buff_data[6]=0b00001000;buff_data[14]=0b00010000;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b00000000;buff_data[15]=0b00010000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    HAL_Delay(ANIMDELAY);
    buff_data[0]=0b00100000;buff_data[8] =0b00010000;buff_data[16]=0b00000010;buff_data[24]=0b00000000;
    buff_data[1]=0b10000000;buff_data[9] =0b00010000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00000000;buff_data[10]=0b00010000;buff_data[18]=0b00000000;buff_data[26]=0b00000000;
    buff_data[3]=0b00000000;buff_data[11]=0b00010000;buff_data[19]=0b00010000;buff_data[27]=0b00011000;
    buff_data[4]=0b00000000;buff_data[12]=0b00010000;buff_data[20]=0b00010000;buff_data[28]=0b00011000;
    buff_data[5]=0b00000000;buff_data[13]=0b00010000;buff_data[21]=0b00000000;buff_data[29]=0b00000000;
    buff_data[6]=0b00001100;buff_data[14]=0b00010000;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b00000000;buff_data[15]=0b00010000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    HAL_Delay(ANIMDELAY);
    buff_data[0]=0b00100000;buff_data[8] =0b00010000;buff_data[16]=0b00000100;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00010000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00000000;buff_data[10]=0b00010000;buff_data[18]=0b00000000;buff_data[26]=0b00000000;
    buff_data[3]=0b00000010;buff_data[11]=0b00010000;buff_data[19]=0b00100000;buff_data[27]=0b00011000;
    buff_data[4]=0b00000000;buff_data[12]=0b00010000;buff_data[20]=0b00100000;buff_data[28]=0b00011000;
    buff_data[5]=0b00001000;buff_data[13]=0b00010000;buff_data[21]=0b00000000;buff_data[29]=0b00000000;
    buff_data[6]=0b00001100;buff_data[14]=0b00010000;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b00000000;buff_data[15]=0b00010000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    HAL_Delay(ANIMDELAY);
    buff_data[0]=0b00000000;buff_data[8] =0b00010000;buff_data[16]=0b00001000;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00010000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00100000;buff_data[10]=0b00010000;buff_data[18]=0b00000000;buff_data[26]=0b00000000;
    buff_data[3]=0b00000000;buff_data[11]=0b00010000;buff_data[19]=0b00100001;buff_data[27]=0b00011000;
    buff_data[4]=0b00000000;buff_data[12]=0b00010000;buff_data[20]=0b00100001;buff_data[28]=0b00011000;
    buff_data[5]=0b00001100;buff_data[13]=0b00010000;buff_data[21]=0b00000000;buff_data[29]=0b00000000;
    buff_data[6]=0b00001100;buff_data[14]=0b00010000;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b00000000;buff_data[15]=0b00010000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    HAL_Delay(ANIMDELAY);

    buff_data[0]=0b00000000;buff_data[8] =0b10000000;buff_data[16]=0b00100000;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b01000000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00000000;buff_data[10]=0b00100000;buff_data[18]=0b00000000;buff_data[26]=0b00111100;
    buff_data[3]=0b00000000;buff_data[11]=0b00010000;buff_data[19]=0b00100010;buff_data[27]=0b00100100;
    buff_data[4]=0b00000000;buff_data[12]=0b00001000;buff_data[20]=0b00100010;buff_data[28]=0b00100100;
    buff_data[5]=0b00000000;buff_data[13]=0b00000100;buff_data[21]=0b00000000;buff_data[29]=0b00111100;
    buff_data[6]=0b00000000;buff_data[14]=0b00000010;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b10000000;buff_data[15]=0b00000001;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    HAL_Delay(ANIMDELAY);
    buff_data[0]=0b00000000;buff_data[8] =0b10000000;buff_data[16]=0b01000001;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b01000000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00000000;buff_data[10]=0b00100000;buff_data[18]=0b00000000;buff_data[26]=0b00111100;
    buff_data[3]=0b00000000;buff_data[11]=0b00010000;buff_data[19]=0b00100100;buff_data[27]=0b00100100;
    buff_data[4]=0b00100000;buff_data[12]=0b00001000;buff_data[20]=0b00100100;buff_data[28]=0b00100100;
    buff_data[5]=0b00000000;buff_data[13]=0b00000100;buff_data[21]=0b00000000;buff_data[29]=0b00111100;
    buff_data[6]=0b00001100;buff_data[14]=0b00000010;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b10000000;buff_data[15]=0b00000001;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    HAL_Delay(ANIMDELAY);
    buff_data[0]=0b00100000;buff_data[8] =0b10000000;buff_data[16]=0b01000010;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b01000000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00000000;buff_data[10]=0b00100000;buff_data[18]=0b00000000;buff_data[26]=0b00111100;
    buff_data[3]=0b00000010;buff_data[11]=0b00010000;buff_data[19]=0b00101000;buff_data[27]=0b00100100;
    buff_data[4]=0b00000000;buff_data[12]=0b00001000;buff_data[20]=0b00101000;buff_data[28]=0b00100100;
    buff_data[5]=0b00000000;buff_data[13]=0b00000100;buff_data[21]=0b00000000;buff_data[29]=0b00111100;
    buff_data[6]=0b00000100;buff_data[14]=0b00000010;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b00000000;buff_data[15]=0b00000001;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    HAL_Delay(ANIMDELAY);
    buff_data[0]=0b00000000;buff_data[8] =0b10000000;buff_data[16]=0b01000100;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b01000000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00100000;buff_data[10]=0b00100000;buff_data[18]=0b00000000;buff_data[26]=0b00111100;
    buff_data[3]=0b00000000;buff_data[11]=0b00010000;buff_data[19]=0b00110000;buff_data[27]=0b00100100;
    buff_data[4]=0b00000000;buff_data[12]=0b00001000;buff_data[20]=0b00110000;buff_data[28]=0b00100100;
    buff_data[5]=0b00000000;buff_data[13]=0b00000100;buff_data[21]=0b00000000;buff_data[29]=0b00111100;
    buff_data[6]=0b00001100;buff_data[14]=0b00000010;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b00000000;buff_data[15]=0b00000001;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    HAL_Delay(ANIMDELAY);


    buff_data[0]=0b00000000;buff_data[8] =0b00000000;buff_data[16]=0b01001000;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00000000;buff_data[17]=0b00000000;buff_data[25]=0b01111110;
    buff_data[2]=0b00000000;buff_data[10]=0b00000000;buff_data[18]=0b00000000;buff_data[26]=0b01000010;
    buff_data[3]=0b00000000;buff_data[11]=0b11111111;buff_data[19]=0b00010000;buff_data[27]=0b01000010;
    buff_data[4]=0b00000000;buff_data[12]=0b00000000;buff_data[20]=0b00100000;buff_data[28]=0b01000010;
    buff_data[5]=0b00000000;buff_data[13]=0b00000000;buff_data[21]=0b00000000;buff_data[29]=0b01000010;
    buff_data[6]=0b00000000;buff_data[14]=0b00000000;buff_data[22]=0b00000000;buff_data[30]=0b01111110;
    buff_data[7]=0b00000001;buff_data[15]=0b00000000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    HAL_Delay(ANIMDELAY);
    buff_data[0]=0b00000000;buff_data[8] =0b00000000;buff_data[16]=0b01010000;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00000000;buff_data[17]=0b00000000;buff_data[25]=0b01111110;
    buff_data[2]=0b00000000;buff_data[10]=0b00000000;buff_data[18]=0b00000000;buff_data[26]=0b01000010;
    buff_data[3]=0b00000000;buff_data[11]=0b11111111;buff_data[19]=0b00100000;buff_data[27]=0b01000010;
    buff_data[4]=0b00100000;buff_data[12]=0b00000000;buff_data[20]=0b00010000;buff_data[28]=0b01000010;
    buff_data[5]=0b00000000;buff_data[13]=0b00000000;buff_data[21]=0b00000000;buff_data[29]=0b01000010;
    buff_data[6]=0b00000000;buff_data[14]=0b00000000;buff_data[22]=0b00000000;buff_data[30]=0b01111110;
    buff_data[7]=0b10000000;buff_data[15]=0b00000000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    HAL_Delay(ANIMDELAY);
    buff_data[0]=0b00110000;buff_data[8] =0b00000000;buff_data[16]=0b01100000;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00000000;buff_data[17]=0b00000000;buff_data[25]=0b01111110;
    buff_data[2]=0b00000000;buff_data[10]=0b00000000;buff_data[18]=0b00000000;buff_data[26]=0b01000010;
    buff_data[3]=0b00000010;buff_data[11]=0b11111111;buff_data[19]=0b01100000;buff_data[27]=0b01000010;
    buff_data[4]=0b00000000;buff_data[12]=0b00000000;buff_data[20]=0b00011000;buff_data[28]=0b01000010;
    buff_data[5]=0b00000000;buff_data[13]=0b00000000;buff_data[21]=0b00000000;buff_data[29]=0b01000010;
    buff_data[6]=0b00000100;buff_data[14]=0b00000000;buff_data[22]=0b00000000;buff_data[30]=0b01111110;
    buff_data[7]=0b00000000;buff_data[15]=0b00000000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    HAL_Delay(ANIMDELAY);
    buff_data[0]=0b00010000;buff_data[8] =0b00000000;buff_data[16]=0b01100001;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00000000;buff_data[17]=0b00000000;buff_data[25]=0b01111110;
    buff_data[2]=0b00000000;buff_data[10]=0b00000000;buff_data[18]=0b00000000;buff_data[26]=0b01000010;
    buff_data[3]=0b00000000;buff_data[11]=0b11111111;buff_data[19]=0b11100000;buff_data[27]=0b01000010;
    buff_data[4]=0b00000000;buff_data[12]=0b00000000;buff_data[20]=0b00011100;buff_data[28]=0b01000010;
    buff_data[5]=0b00000000;buff_data[13]=0b00000000;buff_data[21]=0b00000000;buff_data[29]=0b01000010;
    buff_data[6]=0b00000000;buff_data[14]=0b00000000;buff_data[22]=0b00000000;buff_data[30]=0b01111110;
    buff_data[7]=0b00010000;buff_data[15]=0b00000000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    HAL_Delay(ANIMDELAY);


    buff_data[0]=0b00000000;buff_data[8] =0b00000001;buff_data[16]=0b01100010;buff_data[24]=0b11111111;
    buff_data[1]=0b00000000;buff_data[9] =0b00000010;buff_data[17]=0b00000000;buff_data[25]=0b10000001;
    buff_data[2]=0b00010000;buff_data[10]=0b00000100;buff_data[18]=0b00000000;buff_data[26]=0b10000001;
    buff_data[3]=0b00000000;buff_data[11]=0b00001000;buff_data[19]=0b11100000;buff_data[27]=0b10000001;
    buff_data[4]=0b00000000;buff_data[12]=0b00010000;buff_data[20]=0b00011110;buff_data[28]=0b10000001;
    buff_data[5]=0b00000000;buff_data[13]=0b00100000;buff_data[21]=0b00000000;buff_data[29]=0b10000001;
    buff_data[6]=0b00000000;buff_data[14]=0b01000000;buff_data[22]=0b00000000;buff_data[30]=0b10000001;
    buff_data[7]=0b00000001;buff_data[15]=0b10000000;buff_data[23]=0b00000000;buff_data[31]=0b11111111;
    build_buffer();
    HAL_Delay(ANIMDELAY);
    buff_data[0]=0b00000000;buff_data[8] =0b00000001;buff_data[16]=0b01100100;buff_data[24]=0b11111111;
    buff_data[1]=0b00000000;buff_data[9] =0b00000010;buff_data[17]=0b00000000;buff_data[25]=0b10000001;
    buff_data[2]=0b00000000;buff_data[10]=0b00000100;buff_data[18]=0b00000000;buff_data[26]=0b10000001;
    buff_data[3]=0b00000000;buff_data[11]=0b00001000;buff_data[19]=0b11100000;buff_data[27]=0b10000001;
    buff_data[4]=0b00111000;buff_data[12]=0b00010000;buff_data[20]=0b00011111;buff_data[28]=0b10000001;
    buff_data[5]=0b00000000;buff_data[13]=0b00100000;buff_data[21]=0b00000000;buff_data[29]=0b10000001;
    buff_data[6]=0b00000000;buff_data[14]=0b01000000;buff_data[22]=0b00000000;buff_data[30]=0b10000001;
    buff_data[7]=0b10000000;buff_data[15]=0b10000000;buff_data[23]=0b00000000;buff_data[31]=0b11111111;
    build_buffer();
    HAL_Delay(ANIMDELAY);
    buff_data[0]=0b00110000;buff_data[8] =0b00000001;buff_data[16]=0b01101000;buff_data[24]=0b11111111;
    buff_data[1]=0b00000000;buff_data[9] =0b00000010;buff_data[17]=0b00000000;buff_data[25]=0b10000001;
    buff_data[2]=0b00000000;buff_data[10]=0b00000100;buff_data[18]=0b00000000;buff_data[26]=0b10000001;
    buff_data[3]=0b00000000;buff_data[11]=0b00001000;buff_data[19]=0b01100000;buff_data[27]=0b10000001;
    buff_data[4]=0b00110000;buff_data[12]=0b00010000;buff_data[20]=0b00011110;buff_data[28]=0b10000001;
    buff_data[5]=0b00000000;buff_data[13]=0b00100000;buff_data[21]=0b00000000;buff_data[29]=0b10000001;
    buff_data[6]=0b00000100;buff_data[14]=0b01000000;buff_data[22]=0b00000000;buff_data[30]=0b10000001;
    buff_data[7]=0b00000000;buff_data[15]=0b10000000;buff_data[23]=0b00000000;buff_data[31]=0b11111111;
    build_buffer();
    HAL_Delay(ANIMDELAY);
    buff_data[0]=0b00111000;buff_data[8] =0b00000001;buff_data[16]=0b01110000;buff_data[24]=0b11111111;
    buff_data[1]=0b00001000;buff_data[9] =0b00000010;buff_data[17]=0b00000000;buff_data[25]=0b10000001;
    buff_data[2]=0b00000000;buff_data[10]=0b00000100;buff_data[18]=0b00000000;buff_data[26]=0b10000001;
    buff_data[3]=0b00000000;buff_data[11]=0b00001000;buff_data[19]=0b00100000;buff_data[27]=0b10000001;
    buff_data[4]=0b00011000;buff_data[12]=0b00010000;buff_data[20]=0b00011100;buff_data[28]=0b10000001;
    buff_data[5]=0b00001000;buff_data[13]=0b00100000;buff_data[21]=0b00000000;buff_data[29]=0b10000001;
    buff_data[6]=0b00000000;buff_data[14]=0b01000000;buff_data[22]=0b00000000;buff_data[30]=0b10000001;
    buff_data[7]=0b00010000;buff_data[15]=0b10000000;buff_data[23]=0b00000000;buff_data[31]=0b11111111;
    build_buffer();
    HAL_Delay(ANIMDELAY);
}

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
