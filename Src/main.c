#include <stdint.h>
#include "defines.h"
#include "TIMBasic.h"

enum {
	WAITING,
	REQUEST,
	CROSSING
};

uint32_t t;
int state;

void initStateTimer(){
	// turn on TIM6 clk
	RCC_APB1ENR1 |= 1 << 4;
	// set prescaler to 1 khz
	TIM6->PSC = 3999;
	TIM6->ARR = 999;
	// enable interrupt
	TIM6->DIER |= 1;
	ISER1 |= 1 << 17;
}

void enableStateTimer(){
	TIM6->CR1 |= 1;
}

void disableStateTimer(){
	TIM6->CR1 &= ~(1);
}

void TIM6_IRQHandler(){
	t++;
}

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
