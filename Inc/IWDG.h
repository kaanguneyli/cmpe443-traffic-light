#pragma once

#include <stdint.h>

typedef struct {
  volatile uint32_t KR;
  volatile uint32_t PR;
  volatile uint32_t RLR;
  volatile uint32_t SR;
  volatile uint32_t WINR;
} IWDG_Type;

#define IWDG ((IWDG_Type *)0x40003000)

void init_IWDG();
void reset_IWDG();