#include "defines.h"
#include "TIMBasic.h"

void initStateTimer(){
	// turn on TIM6 clk
	RCC_APB1ENR1 |= 1 << 4;
	// set prescaler to 1 khz
	TIM6->PSC = 3999;
	TIM6->ARR = 199;
	TIM6->CR1 &= ~(1<<1); // OVF will generate an event
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
