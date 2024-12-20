// Credits to Emre Bilgili for PS codes

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "GPIO.h"
#include "UART.h"
#include "defines.h"



typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	uint32_t reserved;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	uint32_t reserved1[3];
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
} TIMxBasicType;



#define TIM6 ((TIMxBasicType *) 0x40001000)

// Used for delay() function
void enable_TIM6(void) {
	RCC_APB1ENR1 |= 1 << 4;
	TIM6->PSC = 3999;
	TIM6->ARR = 999;
	TIM6->CR1 &= ~(1 << 1);
	TIM6->CR1 |= 1;
}
// Used for RGB LEDs
void GPIO_initialization(void) {
	RCC_AHB2ENR |= 0b1000;
	GPIOD->MODER &= ~(0b10 << (3 * 2));
	GPIOD->MODER |= 0b01 << (3 * 2);
	GPIOD->MODER &= ~(0b10 << (4 * 2));
	GPIOD->MODER |= 0b01 << (4 * 2);
	GPIOD->MODER &= ~(0b10 << (5 * 2));
	GPIOD->MODER |= 0b01 << (5 * 2);
}
void turn_on_LED_RED(void) {
	GPIOD->ODR |= 1 << 3;
	GPIOD->ODR &= ~(1 << 4);
	GPIOD->ODR &= ~(1 << 5);
}
void turn_on_LED_YELLOW(void) {
	GPIOD->ODR &= ~(1 << 3);
	GPIOD->ODR |= 1 << 4;
	GPIOD->ODR &= ~(1 << 5);
}
void turn_on_LED_GREEN(void) {
	GPIOD->ODR &= ~(1 << 3);
	GPIOD->ODR &= ~(1 << 4);
	GPIOD->ODR |= 1 << 5;
}

// Blocking delay, it will delay for given seconds
void delay(int second) {
	for (int i = 0; i < second; i++) {
		TIM6->CNT = 0;
		while ((TIM6->SR & 1) == 0)
			;
		TIM6->SR = 0;
	}
}
// Blocking send message function
void send_message(char *string) {
	int i = 0;
	while (string[i] != '\0') {
		LPUART1->TDR = string[i];
		while ((LPUART1->ISR & (1 << 6)) == 0)
			;
		i++;
	}
}
// Used for communicating with the micro-controller


int read_counter = 0; // State of the UI
int color = 0; // Chosen color
uint8_t traffic_delays[3] = { 2, 2, 2 }; // Duration for each light
void LPUART1_IRQHandler(void) {
	if (RXNFE) {
		char LPUART1_read_value = LPUART1->RDR;

	}
}

void __enable_irq(void) {
	__asm volatile(
			"mov r0, #0 \n\t"
			"msr primask, r0 \n\t"
	);
}

int main(void) {
	GPIO_initialization();
	LPUART1_initialization();
	enable_TIM6();
	__enable_irq();
	delay(10);
	send_message("\r\nPress any key to open the menu.\r\n");
	while (1) {
		// Lits the LEDs for their determined duration
		turn_on_LED_RED();
		delay(traffic_delays[0]);
		turn_on_LED_YELLOW();
		delay(traffic_delays[1]);
		turn_on_LED_GREEN();
		delay(traffic_delays[2]);
	}
}
