/*
 * buff.h
 *
 *  Created on: 18-Oct-2020
 *      Author: varun
 */

#ifndef INC_BUFF_H_
#define INC_BUFF_H_

extern uint8_t buff_data[MAX_DEVICES*8];
void build_buffer(void);
void clear_buff(void);

#endif /* INC_BUFF_H_ */
