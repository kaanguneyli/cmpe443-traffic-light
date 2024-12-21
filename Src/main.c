#include <stdint.h>
#include <stdbool.h>
#include "defines.h"
#include "TIMBasic.h"

enum {
	WAITING,
	REQUEST,
	CROSSING
};

extern uint32_t t;
extern bool isHandInRange;
int state;



void __enable_irq(){
	__asm volatile(
			"mov r0, #0\t\n"
			"msr primask, r0\t\n"
	);
}

void init(){
	initStateTimer();
	__enable_irq();
}

int main(void)
{
	// initialization functions go here
	init();
	// state initialization
	state = WAITING;
	while(1){
		switch(state){
		case WAITING: {
			// buzzer off
			// pedestrian light red
			// car light green
			t = 0;
			if (isHandInRange == 1) {
				state = REQUEST;
				enableStateTimer();
			}
			else {
				disableStateTimer();
			}
			break;
		}
		case REQUEST: {
			if (t < 3){
				// buzzer on
				// pedestrian light red
				// car light green
			}
			else if (t < 10){
				// buzzer off
				// pedestrian light red
				// car light green
			}
			else if (t < 12){
				// buzzer off
				// pedestrian light red
				// car light yellow

			}
			else if (t < 14) {
				// buzzer off
				// pedestrian light red
				// car light red
			}
			// t = 15
			else state = CROSSING;
			break;

		}
		case CROSSING: {
			if (t < 30){
				// buzzer off
				// pedestrian light green
				// car light red
			}
			else if (t < 32) {
				// buzzer off
				// pedestrian light red
				// car light red
			}
			else if (t < 34) {
				// pedestrian light red
				// car light green + yellow
			}
			else state = WAITING;
			break;
		}
		default: break;
		}

		__asm volatile("wfi");
	}
}
