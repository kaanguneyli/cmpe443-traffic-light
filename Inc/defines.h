#pragma once

#define ISER1 *((volatile uint32_t *) 0xe000e104)
#define ISER2 *((volatile uint32_t *) 0xE000E108)

#define PWR_CR1 *((volatile uint32_t *) 0x40007000)
#define PWR_CR2 *((volatile uint32_t *) 0x40007004)

#define RCC_AHB2ENR *((volatile uint32_t *) 0x4002104C)
#define RCC_APB1ENR1 *((volatile uint32_t *) 0x40021058)
#define RCC_APB1ENR2 *((volatile uint32_t *) 0x4002105C)
#define RCC_APB2ENR *((volatile uint32_t *) 0x40021060)
#define RCC_CCIPR1 *((volatile uint32_t *) 0x40021088)
