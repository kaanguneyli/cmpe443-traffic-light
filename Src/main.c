#include <stdint.h>
#include <stdbool.h>
#include "defines.h"
#include "TIMBasic.h"
#include "ICOC.h"
#include "GPIO.h"
#include "ADC.h"
#include "RTC.h"
#include "UART.h"

enum {
	WAITING,
	REQUEST,
	CROSSING
};

uint32_t t;
uint32_t temp;
int currentState;

extern bool read_brightness_flag;
extern uint16_t brightness;

void __enable_irq(){
	__asm volatile(
			"mov r0, #0\t\n"
			"msr primask, r0\t\n"
	);
}

void init(){
	initStateTimer();
	init_GPIO_ICOC();
	init_ADC();
	LPUART1_initialization();
	RTC_Init();
	enableStateTimer();
	__enable_irq();
}

void redOn(){ GPIOA->ODR |= 1 << 9; }
void greenOn() { GPIOC->ODR |= 1 << 7; }
void blueOn() {GPIOB->ODR |= 1 << 7; }

void redOff(){ GPIOA->ODR &= ~(1 << 9); }
void greenOff() { GPIOC->ODR &= ~(1 << 7); }
void blueOff() {GPIOB->ODR &= ~(1 << 7); }

void buzzerOn() { GPIOB->ODR |= 1 << 10; }
void buzzerOff() { GPIOB->ODR &= ~(1 << 10); }

int blueon = 0;
Timestamp timestamp = {0};
void TIM6_IRQHandler(){
	if (temp == 4){
		temp = 0;
		t++;
		if (!blueon) {
			blueOn();
			blueon = 1;
		}
		else {
			blueOff();
			blueon = 0;
		}
		measure_brightness();
		RTC_Get(&timestamp);
	}
	else temp++;
	TIM6->SR = 0;
	getCrossingRequests();
}


int main(void)
{
	// initialization functions go here
	init();
	// state initialization
	currentState = WAITING;

	while(1){

		if (read_brightness_flag && (brightness > 100)) blueOn();
		else blueOff();

		switch(currentState){
		case WAITING: {
			// buzzer off
			// pedestrian light red
			// car light green
			t = 0;
			if (isPedestrianInRange() != 0) {
				currentState = REQUEST;
			}
			break;
		}
		case REQUEST: {
			if (t < 3){
				// buzzer on
				buzzerOn();
				// pedestrian light red
				redOn();
				blueOff();
				greenOff();
				// car light green
			}
			else if (t < 5){
				// buzzer off
				buzzerOff();
				// pedestrian light red
				// car light green
			}
			else if (t < 13){
				// buzzer off
				// pedestrian light red
				redOff();
				greenOn();
				// car light yellow

			}
			else if (t < 15) {
				// buzzer off
				// pedestrian light red
				redOn();
				greenOff();
				// car light red
			}
			// t = 15
			else {
				currentState = WAITING;
				redOff();
			}
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
			else currentState = WAITING;

			break;
		}
		default: break;
		}
		__asm volatile("wfi");
	}
}
