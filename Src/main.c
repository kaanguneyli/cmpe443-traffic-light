#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
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
extern TrafficLight GeneralTraficLight;

int blueon = 0;
Timestamp timestamp = {
		.sec = 0,
		.min = 0,
		.hour = 0,
		.wday = 3,
		.mon = 12,
		.mday = 25,
		.year_s = 24
};

void redOn(){ GPIOA->ODR |= 1 << 9; }
void greenOn() { GPIOC->ODR |= 1 << 7; }
void blueOn() {GPIOB->ODR |= 1 << 7; }

void redOff(){ GPIOA->ODR &= ~(1 << 9); }
void greenOff() { GPIOC->ODR &= ~(1 << 7); }
void blueOff() {GPIOB->ODR &= ~(1 << 7); }

void buzzerOn() { GPIOB->ODR |= 1 << 10; }
void buzzerOff() { GPIOB->ODR &= ~(1 << 10); }

uint16_t getGreenToYellowTimestamp(){ return GeneralTraficLight.green_duration; }
uint16_t getYellowToRedTimestamp() { return GeneralTraficLight.green_duration + GeneralTraficLight.yellow_duration; }
uint16_t getRedToGreenTimestamp() { return GeneralTraficLight.green_duration + GeneralTraficLight.yellow_duration + GeneralTraficLight.red_duration; }
uint16_t getPedestrianCrossingTimestamp() {return GeneralTraficLight.green_duration + GeneralTraficLight.yellow_duration + GeneralTraficLight.pedestrian_wait; }
uint16_t getAnimationEndingTimestamp() {return GeneralTraficLight.green_duration + GeneralTraficLight.yellow_duration + GeneralTraficLight.pedestrian_wait + GeneralTraficLight.animation_duration; }
uint16_t getCarWaitTimestamp() {return GeneralTraficLight.green_duration + GeneralTraficLight.yellow_duration + GeneralTraficLight.pedestrian_wait + GeneralTraficLight.animation_duration + GeneralTraficLight.car_wait; }

void __enable_irq(){
	__asm volatile(
			"mov r0, #0\t\n"
			"msr primask, r0\t\n"
	);
}

void constructLog(char string[512], Timestamp * timestamp, int type){
	if (!timestamp || !string) return;

    const char *weekday_names[] = {"forbidden", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    //const char *month_names[] = {"forbidden", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    const char *weekday = weekday_names[timestamp->wday];
    //const char *month = month_names[timestamp->mon];
    char * logType = "\0";
    switch(type) {
    case 0:
    	logType = "REQUEST";
    	break;
    case 1:
    	logType = "VEHICLE STOP, PEDESTRIAN CROSS";
		break;
    case 2:
    	logType = "VEHICLE CROSS, PEDESTRIAN STOP";
		break;
    }

    // Format the string
    snprintf(string, 512,
             "\r\nDate: %s, %02d %02d 20%02d Time: %02d:%02d:%02d %s",
             weekday,
			 timestamp->mday,
             timestamp->mon,
             timestamp->year_s,
             timestamp->hour,
             timestamp->min,
             timestamp->sec,
			 logType
             );

}

void init(){
	initStateTimer();
	init_GPIO_ICOC();
	init_ADC();
	LPUART1_initialization();
	RTC_Init();
	RTC_Update(&timestamp);
	enableStateTimer();
	__enable_irq();
}

void TIM6_IRQHandler(){
	if (temp == 4){
		temp = 0;
		t++;
//		if (!blueon) {
//			blueOn();
//			blueon = 1;
//		}
//		else {
//			blueOff();
//			blueon = 0;
//		}
		measure_brightness();
//		RTC_Get(&timestamp);
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
				RTC_Get(&timestamp);
				// convert into date string
				char log[512] = {0};
				// send with uart
				constructLog(log, &timestamp, 0);
				send_message_NB(log);
			}
			break;
		}
		case REQUEST: {
			if (t < getGreenToYellowTimestamp()) {
				// car light green
				// buzzer on for 3 seconds
				redOn();
				if (t < 3) buzzerOn();
				else buzzerOff();
			}
			else if (t < getYellowToRedTimestamp()) {
				// pedestrian light red
				redOn();
				greenOn();
				// car light yellow
			}
			else if (t < getRedToGreenTimestamp()) {
				redOff();
				greenOn();
				if (t < getPedestrianCrossingTimestamp()) {
					// pedestrian light red
				}
				else if (t < getAnimationEndingTimestamp()) {
					// play animation
				}
				else if (t < getCarWaitTimestamp()) {
					// no animation, car light red
				}
				// car light red
			}
			// t = 15
			else {
				currentState = WAITING;
				redOff();
				greenOff();
			}
			break;
		}

		default: break;
		}
		__asm volatile("wfi");
	}
}
