#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "UART.h"
#include "defines.h"
#include "GPIO.h"

void LPUART1_initialization(void) {
	RCC_APB1ENR1 |= 1 << 28;
	PWR_CR1 |= 1 << 14;
	PWR_CR2 |= 1 << 9;
	RCC_CCIPR1 &= ~(1 << 11);
	RCC_CCIPR1 |= 1 << 10;
	RCC_AHB2ENR |= 1 << 6;
	GPIOG->MODER &= ~(0b0101 << (7 * 2));
	GPIOG->MODER |= 0b1010 << (7 * 2);
	GPIOG->AFRL &= ~(0b0111 << (7 * 4));
	GPIOG->AFRL |= 0b1000 << (7 * 4);
	GPIOG->AFRH &= ~0b0111;
	GPIOG->AFRH |= 0b1000;
	RCC_APB1ENR2 |= 1;
	LPUART1->BRR = 8888;
	LPUART1->CR1 |= 1 << 29;
	LPUART1->CR1 |= 0b11 << 2;
	LPUART1->CR1 |= 1 << 5;
	ISER2 |= 1 << 2;
	LPUART1->CR1 |= 1;
}
