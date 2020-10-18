#include "stm32g0xx.h"
#include "configs.h"
#include "rcc.h"
#include "systick.h"
#include "delay.h"
#include "hw.h"
#include "buff.h"


int main(void)
{
  sysclock_config();//call the system clock configuration function. Clock should be set to 64Mhz now.
  systick_enable();//set the systick timer to interrupt every 1ms.
  hw_setup();

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
    DelayMS(ANIMDELAY);
    buff_data[0]=0b00100000;buff_data[8] =0b00010000;buff_data[16]=0b00000010;buff_data[24]=0b00000000;
    buff_data[1]=0b10000000;buff_data[9] =0b00010000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00000000;buff_data[10]=0b00010000;buff_data[18]=0b00000000;buff_data[26]=0b00000000;
    buff_data[3]=0b00000000;buff_data[11]=0b00010000;buff_data[19]=0b00010000;buff_data[27]=0b00011000;
    buff_data[4]=0b00000000;buff_data[12]=0b00010000;buff_data[20]=0b00010000;buff_data[28]=0b00011000;
    buff_data[5]=0b00000000;buff_data[13]=0b00010000;buff_data[21]=0b00000000;buff_data[29]=0b00000000;
    buff_data[6]=0b00001100;buff_data[14]=0b00010000;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b00000000;buff_data[15]=0b00010000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    DelayMS(ANIMDELAY);
    buff_data[0]=0b00100000;buff_data[8] =0b00010000;buff_data[16]=0b00000100;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00010000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00000000;buff_data[10]=0b00010000;buff_data[18]=0b00000000;buff_data[26]=0b00000000;
    buff_data[3]=0b00000010;buff_data[11]=0b00010000;buff_data[19]=0b00100000;buff_data[27]=0b00011000;
    buff_data[4]=0b00000000;buff_data[12]=0b00010000;buff_data[20]=0b00100000;buff_data[28]=0b00011000;
    buff_data[5]=0b00001000;buff_data[13]=0b00010000;buff_data[21]=0b00000000;buff_data[29]=0b00000000;
    buff_data[6]=0b00001100;buff_data[14]=0b00010000;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b00000000;buff_data[15]=0b00010000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    DelayMS(ANIMDELAY);
    buff_data[0]=0b00000000;buff_data[8] =0b00010000;buff_data[16]=0b00001000;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00010000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00100000;buff_data[10]=0b00010000;buff_data[18]=0b00000000;buff_data[26]=0b00000000;
    buff_data[3]=0b00000000;buff_data[11]=0b00010000;buff_data[19]=0b00100001;buff_data[27]=0b00011000;
    buff_data[4]=0b00000000;buff_data[12]=0b00010000;buff_data[20]=0b00100001;buff_data[28]=0b00011000;
    buff_data[5]=0b00001100;buff_data[13]=0b00010000;buff_data[21]=0b00000000;buff_data[29]=0b00000000;
    buff_data[6]=0b00001100;buff_data[14]=0b00010000;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b00000000;buff_data[15]=0b00010000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    DelayMS(ANIMDELAY);

    buff_data[0]=0b00000000;buff_data[8] =0b10000000;buff_data[16]=0b00100000;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b01000000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00000000;buff_data[10]=0b00100000;buff_data[18]=0b00000000;buff_data[26]=0b00111100;
    buff_data[3]=0b00000000;buff_data[11]=0b00010000;buff_data[19]=0b00100010;buff_data[27]=0b00100100;
    buff_data[4]=0b00000000;buff_data[12]=0b00001000;buff_data[20]=0b00100010;buff_data[28]=0b00100100;
    buff_data[5]=0b00000000;buff_data[13]=0b00000100;buff_data[21]=0b00000000;buff_data[29]=0b00111100;
    buff_data[6]=0b00000000;buff_data[14]=0b00000010;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b10000000;buff_data[15]=0b00000001;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    DelayMS(ANIMDELAY);
    buff_data[0]=0b00000000;buff_data[8] =0b10000000;buff_data[16]=0b01000001;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b01000000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00000000;buff_data[10]=0b00100000;buff_data[18]=0b00000000;buff_data[26]=0b00111100;
    buff_data[3]=0b00000000;buff_data[11]=0b00010000;buff_data[19]=0b00100100;buff_data[27]=0b00100100;
    buff_data[4]=0b00100000;buff_data[12]=0b00001000;buff_data[20]=0b00100100;buff_data[28]=0b00100100;
    buff_data[5]=0b00000000;buff_data[13]=0b00000100;buff_data[21]=0b00000000;buff_data[29]=0b00111100;
    buff_data[6]=0b00001100;buff_data[14]=0b00000010;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b10000000;buff_data[15]=0b00000001;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    DelayMS(ANIMDELAY);
    buff_data[0]=0b00100000;buff_data[8] =0b10000000;buff_data[16]=0b01000010;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b01000000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00000000;buff_data[10]=0b00100000;buff_data[18]=0b00000000;buff_data[26]=0b00111100;
    buff_data[3]=0b00000010;buff_data[11]=0b00010000;buff_data[19]=0b00101000;buff_data[27]=0b00100100;
    buff_data[4]=0b00000000;buff_data[12]=0b00001000;buff_data[20]=0b00101000;buff_data[28]=0b00100100;
    buff_data[5]=0b00000000;buff_data[13]=0b00000100;buff_data[21]=0b00000000;buff_data[29]=0b00111100;
    buff_data[6]=0b00000100;buff_data[14]=0b00000010;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b00000000;buff_data[15]=0b00000001;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    DelayMS(ANIMDELAY);
    buff_data[0]=0b00000000;buff_data[8] =0b10000000;buff_data[16]=0b01000100;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b01000000;buff_data[17]=0b00000000;buff_data[25]=0b00000000;
    buff_data[2]=0b00100000;buff_data[10]=0b00100000;buff_data[18]=0b00000000;buff_data[26]=0b00111100;
    buff_data[3]=0b00000000;buff_data[11]=0b00010000;buff_data[19]=0b00110000;buff_data[27]=0b00100100;
    buff_data[4]=0b00000000;buff_data[12]=0b00001000;buff_data[20]=0b00110000;buff_data[28]=0b00100100;
    buff_data[5]=0b00000000;buff_data[13]=0b00000100;buff_data[21]=0b00000000;buff_data[29]=0b00111100;
    buff_data[6]=0b00001100;buff_data[14]=0b00000010;buff_data[22]=0b00000000;buff_data[30]=0b00000000;
    buff_data[7]=0b00000000;buff_data[15]=0b00000001;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    DelayMS(ANIMDELAY);


    buff_data[0]=0b00000000;buff_data[8] =0b00000000;buff_data[16]=0b01001000;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00000000;buff_data[17]=0b00000000;buff_data[25]=0b01111110;
    buff_data[2]=0b00000000;buff_data[10]=0b00000000;buff_data[18]=0b00000000;buff_data[26]=0b01000010;
    buff_data[3]=0b00000000;buff_data[11]=0b11111111;buff_data[19]=0b00010000;buff_data[27]=0b01000010;
    buff_data[4]=0b00000000;buff_data[12]=0b00000000;buff_data[20]=0b00100000;buff_data[28]=0b01000010;
    buff_data[5]=0b00000000;buff_data[13]=0b00000000;buff_data[21]=0b00000000;buff_data[29]=0b01000010;
    buff_data[6]=0b00000000;buff_data[14]=0b00000000;buff_data[22]=0b00000000;buff_data[30]=0b01111110;
    buff_data[7]=0b00000001;buff_data[15]=0b00000000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    DelayMS(ANIMDELAY);
    buff_data[0]=0b00000000;buff_data[8] =0b00000000;buff_data[16]=0b01010000;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00000000;buff_data[17]=0b00000000;buff_data[25]=0b01111110;
    buff_data[2]=0b00000000;buff_data[10]=0b00000000;buff_data[18]=0b00000000;buff_data[26]=0b01000010;
    buff_data[3]=0b00000000;buff_data[11]=0b11111111;buff_data[19]=0b00100000;buff_data[27]=0b01000010;
    buff_data[4]=0b00100000;buff_data[12]=0b00000000;buff_data[20]=0b00010000;buff_data[28]=0b01000010;
    buff_data[5]=0b00000000;buff_data[13]=0b00000000;buff_data[21]=0b00000000;buff_data[29]=0b01000010;
    buff_data[6]=0b00000000;buff_data[14]=0b00000000;buff_data[22]=0b00000000;buff_data[30]=0b01111110;
    buff_data[7]=0b10000000;buff_data[15]=0b00000000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    DelayMS(ANIMDELAY);
    buff_data[0]=0b00110000;buff_data[8] =0b00000000;buff_data[16]=0b01100000;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00000000;buff_data[17]=0b00000000;buff_data[25]=0b01111110;
    buff_data[2]=0b00000000;buff_data[10]=0b00000000;buff_data[18]=0b00000000;buff_data[26]=0b01000010;
    buff_data[3]=0b00000010;buff_data[11]=0b11111111;buff_data[19]=0b01100000;buff_data[27]=0b01000010;
    buff_data[4]=0b00000000;buff_data[12]=0b00000000;buff_data[20]=0b00011000;buff_data[28]=0b01000010;
    buff_data[5]=0b00000000;buff_data[13]=0b00000000;buff_data[21]=0b00000000;buff_data[29]=0b01000010;
    buff_data[6]=0b00000100;buff_data[14]=0b00000000;buff_data[22]=0b00000000;buff_data[30]=0b01111110;
    buff_data[7]=0b00000000;buff_data[15]=0b00000000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    DelayMS(ANIMDELAY);
    buff_data[0]=0b00010000;buff_data[8] =0b00000000;buff_data[16]=0b01100001;buff_data[24]=0b00000000;
    buff_data[1]=0b00000000;buff_data[9] =0b00000000;buff_data[17]=0b00000000;buff_data[25]=0b01111110;
    buff_data[2]=0b00000000;buff_data[10]=0b00000000;buff_data[18]=0b00000000;buff_data[26]=0b01000010;
    buff_data[3]=0b00000000;buff_data[11]=0b11111111;buff_data[19]=0b11100000;buff_data[27]=0b01000010;
    buff_data[4]=0b00000000;buff_data[12]=0b00000000;buff_data[20]=0b00011100;buff_data[28]=0b01000010;
    buff_data[5]=0b00000000;buff_data[13]=0b00000000;buff_data[21]=0b00000000;buff_data[29]=0b01000010;
    buff_data[6]=0b00000000;buff_data[14]=0b00000000;buff_data[22]=0b00000000;buff_data[30]=0b01111110;
    buff_data[7]=0b00010000;buff_data[15]=0b00000000;buff_data[23]=0b00000000;buff_data[31]=0b00000000;
    build_buffer();
    DelayMS(ANIMDELAY);


    buff_data[0]=0b00000000;buff_data[8] =0b00000001;buff_data[16]=0b01100010;buff_data[24]=0b11111111;
    buff_data[1]=0b00000000;buff_data[9] =0b00000010;buff_data[17]=0b00000000;buff_data[25]=0b10000001;
    buff_data[2]=0b00010000;buff_data[10]=0b00000100;buff_data[18]=0b00000000;buff_data[26]=0b10000001;
    buff_data[3]=0b00000000;buff_data[11]=0b00001000;buff_data[19]=0b11100000;buff_data[27]=0b10000001;
    buff_data[4]=0b00000000;buff_data[12]=0b00010000;buff_data[20]=0b00011110;buff_data[28]=0b10000001;
    buff_data[5]=0b00000000;buff_data[13]=0b00100000;buff_data[21]=0b00000000;buff_data[29]=0b10000001;
    buff_data[6]=0b00000000;buff_data[14]=0b01000000;buff_data[22]=0b00000000;buff_data[30]=0b10000001;
    buff_data[7]=0b00000001;buff_data[15]=0b10000000;buff_data[23]=0b00000000;buff_data[31]=0b11111111;
    build_buffer();
    DelayMS(ANIMDELAY);
    buff_data[0]=0b00000000;buff_data[8] =0b00000001;buff_data[16]=0b01100100;buff_data[24]=0b11111111;
    buff_data[1]=0b00000000;buff_data[9] =0b00000010;buff_data[17]=0b00000000;buff_data[25]=0b10000001;
    buff_data[2]=0b00000000;buff_data[10]=0b00000100;buff_data[18]=0b00000000;buff_data[26]=0b10000001;
    buff_data[3]=0b00000000;buff_data[11]=0b00001000;buff_data[19]=0b11100000;buff_data[27]=0b10000001;
    buff_data[4]=0b00111000;buff_data[12]=0b00010000;buff_data[20]=0b00011111;buff_data[28]=0b10000001;
    buff_data[5]=0b00000000;buff_data[13]=0b00100000;buff_data[21]=0b00000000;buff_data[29]=0b10000001;
    buff_data[6]=0b00000000;buff_data[14]=0b01000000;buff_data[22]=0b00000000;buff_data[30]=0b10000001;
    buff_data[7]=0b10000000;buff_data[15]=0b10000000;buff_data[23]=0b00000000;buff_data[31]=0b11111111;
    build_buffer();
    DelayMS(ANIMDELAY);
    buff_data[0]=0b00110000;buff_data[8] =0b00000001;buff_data[16]=0b01101000;buff_data[24]=0b11111111;
    buff_data[1]=0b00000000;buff_data[9] =0b00000010;buff_data[17]=0b00000000;buff_data[25]=0b10000001;
    buff_data[2]=0b00000000;buff_data[10]=0b00000100;buff_data[18]=0b00000000;buff_data[26]=0b10000001;
    buff_data[3]=0b00000000;buff_data[11]=0b00001000;buff_data[19]=0b01100000;buff_data[27]=0b10000001;
    buff_data[4]=0b00110000;buff_data[12]=0b00010000;buff_data[20]=0b00011110;buff_data[28]=0b10000001;
    buff_data[5]=0b00000000;buff_data[13]=0b00100000;buff_data[21]=0b00000000;buff_data[29]=0b10000001;
    buff_data[6]=0b00000100;buff_data[14]=0b01000000;buff_data[22]=0b00000000;buff_data[30]=0b10000001;
    buff_data[7]=0b00000000;buff_data[15]=0b10000000;buff_data[23]=0b00000000;buff_data[31]=0b11111111;
    build_buffer();
    DelayMS(ANIMDELAY);
    buff_data[0]=0b00111000;buff_data[8] =0b00000001;buff_data[16]=0b01110000;buff_data[24]=0b11111111;
    buff_data[1]=0b00001000;buff_data[9] =0b00000010;buff_data[17]=0b00000000;buff_data[25]=0b10000001;
    buff_data[2]=0b00000000;buff_data[10]=0b00000100;buff_data[18]=0b00000000;buff_data[26]=0b10000001;
    buff_data[3]=0b00000000;buff_data[11]=0b00001000;buff_data[19]=0b00100000;buff_data[27]=0b10000001;
    buff_data[4]=0b00011000;buff_data[12]=0b00010000;buff_data[20]=0b00011100;buff_data[28]=0b10000001;
    buff_data[5]=0b00001000;buff_data[13]=0b00100000;buff_data[21]=0b00000000;buff_data[29]=0b10000001;
    buff_data[6]=0b00000000;buff_data[14]=0b01000000;buff_data[22]=0b00000000;buff_data[30]=0b10000001;
    buff_data[7]=0b00010000;buff_data[15]=0b10000000;buff_data[23]=0b00000000;buff_data[31]=0b11111111;
    build_buffer();
    DelayMS(ANIMDELAY);
}

}

