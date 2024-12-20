#pragma once
#include <stdint.h>

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
	volatile uint32_t BRR;
	uint32_t reserved;
	volatile uint32_t SECCFGR;
} GPIOType;

#define GPIOA ((GPIOType *) 0x42020000)
#define GPIOB ((GPIOType *) 0x42020400)
#define GPIOC ((GPIOType *) 0x42020800)
#define GPIOD ((GPIOType *) 0x42020C00)
#define GPIOE ((GPIOType *) 0x42021000)
#define GPIOF ((GPIOType *) 0x42021400)
#define GPIOG ((GPIOType *) 0x42021800)

void init_LED_Matrix();
