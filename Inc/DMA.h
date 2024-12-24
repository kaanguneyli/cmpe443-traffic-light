#pragma once

#include <stdint.h>

typedef struct {
  volatile uint32_t C0CR;
  volatile uint32_t C1CR;
  volatile uint32_t C2CR;
  volatile uint32_t C3CR;
  volatile uint32_t C4CR;
  volatile uint32_t C5CR;
  volatile uint32_t C6CR;
  volatile uint32_t C7CR;
  volatile uint32_t C8CR;
  volatile uint32_t C9CR;
  volatile uint32_t C10CR;
  volatile uint32_t C11CR;
  volatile uint32_t C12CR;
  volatile uint32_t C13CR;
  volatile uint32_t C14CR;
  volatile uint32_t C15CR;
} DMAMUX_Type; // Double checked

typedef struct {
  volatile uint32_t ISR;
  volatile uint32_t IFCR;
  volatile uint32_t CCR1;
  volatile uint32_t CNDTR1;
  volatile uint32_t CPAR1;
  volatile uint32_t CMA0AR1;
  volatile uint32_t CMA1AR1;
  volatile uint32_t CCR2;
  volatile uint32_t CNDTR2;
  volatile uint32_t CPAR2;
  volatile uint32_t CMA0AR2;
  volatile uint32_t CMA1AR2;
} DMA_Type; // Double checked

#define DMAMUX ((DMAMUX_Type *)0x40020800) // Double checked
#define DMA1 ((DMA_Type *)0x40020000)      // Double checked