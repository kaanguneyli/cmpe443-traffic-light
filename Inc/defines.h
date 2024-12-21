#pragma once
#include "TIMBasic.h"

#define ISER1 *((volatile uint32_t *) 0xE000E104)
#define ISER2 *((volatile uint32_t *) 0xE000E108)

#define PWR_CR1 *((volatile uint32_t *) 0x40007000)
#define PWR_CR2 *((volatile uint32_t *) 0x40007004)

#define RCC_AHB2ENR *((volatile uint32_t *) 0x4002104C)
#define RCC_APB1ENR1 *((volatile uint32_t *) 0x40021058)
#define RCC_APB1ENR2 *((volatile uint32_t *) 0x4002105C)
#define RCC_CCIPR1 *((volatile uint32_t *) 0x40021088)

#define TIM6 ((volatile TIMxBasicType *) 0x40001000)

typedef struct {
	volatile uint16_t green_duration;
	volatile uint16_t yellow_duration;
	volatile uint16_t red_duration;
	volatile uint16_t pedestrian_wait; // waiting duration between the start of red light to cars and green light to pedestrians
	volatile uint16_t animation_duration;
	volatile uint16_t car_wait; // waiting duration between the start of red light to pedestrians and green light to cars
} TrafficLight;
