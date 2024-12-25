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
uint32_t brightness_timer = 0;
uint32_t temp;
int currentState;

extern bool read_brightness_flag;
extern uint16_t brightness;
uint16_t brightness_measurement = 16;
extern TrafficLight GeneralTraficLight;

extern uint32_t red_man[8];
extern uint32_t green_man_1[8];
extern uint32_t green_man_2[8];
extern uint32_t green_man_3[8];
extern uint32_t green_man_4[8];
extern uint32_t green_man_5[8];
extern uint32_t reset_matrix[8];

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

Timestamp * ts_ptr = &timestamp;

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

	static int lastType;

	if (!timestamp || !string) return;

	if ((type == lastType) && (lastType != 0)) return;

    const char *weekday_names[] = {"forbidden", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    //const char *month_names[] = {"forbidden", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    const char *weekday = weekday_names[timestamp->wday];
    //const char *month = month_names[timestamp->mon];
    char * logType = "\0";
    switch(type) {
    case 0:
    	logType = "REQUEST";
    	break;
    case 1:
    	logType = "VEHICLE STOP";
		break;
    case 2:
    	logType = "PEDESTRIAN STOP";
    	break;
    case 3:
    	logType = "VEHICLE CROSS";
    	break;
    case 4:
    	logType = "PEDESTRIAN CROSS";
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

    lastType = type;
}

void init(){
	while((RCC_CR & (1<<1)) == 0);
	RCC_CR &= ~(0b1111<<4);
	RCC_CR |= (0b1001<<4);
	while((RCC_CR & (1<<1)) == 0);
	RCC_CR |= (0b1<<3);
	while((RCC_CR & (1<<1)) == 0);
	initStateTimer();
	init_GPIO_ICOC();
	init_ADC();
	LPUART1_initialization();
	RTC_Init();
	RTC_Update(&timestamp);
	enableStateTimer();
	init_LED_Matrix();
	__enable_irq();
}

uint32_t *frames[10] = {
		green_man_1,
		green_man_2,
		green_man_3,
		green_man_2,
		green_man_1,
		green_man_1,
		green_man_4,
		green_man_5,
		green_man_4,
		green_man_1
};

void TIM6_IRQHandler(){
	if (temp == 9){
		temp = 0;
		brightness_timer++;
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
//		RTC_Get(&timestamp);
	}
	else temp++;
	if (brightness_timer == 5) {
		brightness_measurement = ((brightness << 3) >> 3) + 1;
		brightness_timer = 0;
	}
	TIM6->SR = 0;
	getCrossingRequests();
}

void log(int type){
	RTC_Get(&timestamp);
	// convert into date string
	char log[512] = {0};
	// send with uart
	constructLog(log, &timestamp, type);
	send_message_NB(log);
}

int main(void)
{
	// initialization functions go here
	init();
	// state initialization
	currentState = WAITING;

	while(1){
		switch(currentState){
		case WAITING: {
			// pedestrian light red
			// car light green
			t = 0;
			if (isPedestrianInRange() != 0) {
				currentState = REQUEST;
				log(0);
			}
			set_frame(red_man, RED, brightness_measurement);
			changeLight(GREEN, brightness_measurement);
			send_LED();
			break;
		}
		case REQUEST: {
			if (t < getGreenToYellowTimestamp()) {
				// car light green
				// buzzer on for 3 seconds
				if (t < 3) buzzerOn();
				else buzzerOff();
				set_frame(red_man, RED, brightness_measurement);
				changeLight(GREEN, brightness_measurement);
			}
			else if (t < getYellowToRedTimestamp()) {
				// pedestrian light red
				set_frame(red_man, RED, brightness_measurement);
				// car light yellow
				changeLight(YELLOW, brightness_measurement);
			}
			else if (t < getRedToGreenTimestamp()) {
				// car light red
				changeLight(RED, brightness_measurement);
				if (t == getYellowToRedTimestamp()) log(1);
				if (t < getPedestrianCrossingTimestamp()) {
					// pedestrian light red
					set_frame(red_man, RED, brightness_measurement);
				}
				else if (t < getAnimationEndingTimestamp()) {
					if (t == getPedestrianCrossingTimestamp()) log(4);
					// play animation
					set_frame(frames[temp], GREEN, brightness_measurement);
				}
				else if (t < getCarWaitTimestamp()) {
					if (t == getAnimationEndingTimestamp()) log(2);
					// no animation, car light red
					set_frame(red_man, RED, brightness_measurement);
				}
			}
			// t = 15
			else {
				currentState = WAITING;
				log(3);
			}
			send_LED();
			break;
		}

		default: break;
		}
		__asm volatile("wfi");
	}
}


/*
int main(void) {
	init();
	while((RCC_CR & (1<<1)) == 0);
	RCC_CR &= ~(0b1111<<4);
	RCC_CR |= (0b1001<<4);
	while((RCC_CR & (1<<1)) == 0);
	RCC_CR |= (0b1<<3);
	while((RCC_CR & (1<<1)) == 0);
	init_LED_Matrix();
	set_frame(red_man, RED, 16);
	changeLight(RED, 255);
	send_LED();
  __asm volatile( // NEW! enable all interrupts that are configured
      "mov r0, #0 \n\t"
      "msr primask, r0 \n\t");
  for(int i=0;i<1000000;i++){
	  bruh = 0;
  }
  set_frame(red_man, RED, 16);
  send_LED();
	  for(int i=0;i<1000000;i++){
		  bruh = 0;
	  }
	  set_frame(red_man, RED, 16);
	  send_LED();
		  for(int i=0;i<1000000;i++){
			  bruh = 0;
		  }
		  set_frame(red_man, RED, 16);
		  send_LED();
  while (1) {
  }
  return 0;
}

*/
