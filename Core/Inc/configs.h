/*
 * configs.h
 *
 *  Created on: 20-Sep-2020
 *      Author: varun
 */

#ifndef INC_CONFIGS_H_
#define INC_CONFIGS_H_

#define MAX_DEVICES 4

#define DATAR GPIOB
#define CLKR GPIOB
#define LOADR GPIOB

#define DATAP GPIO_PIN_6
#define CLKP GPIO_PIN_15
#define LOADP GPIO_PIN_10

void Error_Handler(void);


#endif /* INC_CONFIGS_H_ */
