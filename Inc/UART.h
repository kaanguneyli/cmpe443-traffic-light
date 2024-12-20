#pragma once
#include <stdint.h>
typedef struct {
	volatile uint32_t CR1; //0
	volatile uint32_t CR2; //4
	volatile uint32_t CR3; //8
	volatile uint32_t BRR; //C
	uint32_t reserved1[2]; //10 14
	volatile uint32_t RQR; //18
	volatile uint32_t ISR; //1C
	volatile uint32_t ICR; //20
	volatile uint32_t RDR; //24
	volatile uint32_t TDR; //28
	volatile uint32_t PRESC; //2C
} LPUARTType;

#define RXNFE ((LPUART1->ISR & (1 << 5)) != 0)

#define LPUART1 ((LPUARTType *) 0x40008000)

void LPUART1_initialization();
