/*
 * TIMBasic.h
 *
 *  Created on: Dec 20, 2024
 *      Author: yigit
 */

#ifndef TIMBASIC_H_
#define TIMBASIC_H_

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

typedef struct {
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMCR;
  volatile uint32_t DIER;
  volatile uint32_t SR;
  volatile uint32_t EGR;
  volatile uint32_t CCMR1;
  volatile uint32_t CCMR2;
  volatile uint32_t CCER;
  volatile uint32_t CNT;
  volatile uint32_t PSC;
  volatile uint32_t ARR;
  volatile uint32_t RCR;
  volatile uint32_t CCR1;
  volatile uint32_t CCR2;
  volatile uint32_t CCR3;
  volatile uint32_t CCR4;
  volatile uint32_t BDTR;
  volatile uint32_t DCR;
  volatile uint32_t DMAR;
  volatile uint32_t OR1;
  volatile uint32_t CCMR3;
  volatile uint32_t CCR5;
  volatile uint32_t CCR6;
  volatile uint32_t OR2;
  volatile uint32_t OR3;
} TIM1_Advanced_Type;

#define TIM1 ((volatile TIM1_Advanced_Type *)0x40012C00)

void initStateTimer();
void enableStateTimer();
void disableStateTimer();

#endif /* TIMBASIC_H_ */
