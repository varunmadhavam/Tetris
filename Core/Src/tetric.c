#include "stm32g0xx_hal.h"
#include "tetris.h"
#include "max7219.h"

void tetris(void) {
	max_init();
	uint16_t data[4]={0,0,0,0};
	while(1) {
        data[0]=0x0108;
        max_send_data(data);
        data[0]=0x0208;
        max_send_data(data);
        data[0]=0x0308;
        max_send_data(data);
        data[0]=0x0408;
        max_send_data(data);
        data[0]=0x0508;
        max_send_data(data);
        data[0]=0x0608;
        max_send_data(data);
        data[0]=0x0700;
        max_send_data(data);
        data[0]=0x0808;
        max_send_data(data);

	}
}


