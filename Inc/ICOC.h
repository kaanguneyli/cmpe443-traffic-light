/*
 * ICOC.h
 *
 *  Created on: Dec 20, 2024
 *      Author: yigit
 */

#ifndef ICOC_H_
#define ICOC_H_

// Our structs
typedef struct {
	 volatile uint32_t CR1; //0
	 volatile uint32_t CR2; //4
	 volatile uint32_t SMCR; //8
	 volatile uint32_t DIER; //C
	 volatile uint32_t SR; //10
	 volatile uint32_t EGR; //14
	 volatile uint32_t CCMR1; //18
	 uint32_t reserved1; //1C
	 volatile uint32_t CCER; //20
	 volatile uint32_t CNT; //24
	 volatile uint32_t PSC; //28
	 volatile uint32_t ARR; //2C
	 volatile uint32_t RCR; //30
	 volatile uint32_t CCR1; //34
	 volatile uint32_t CCR2; //38
	 uint32_t reserved2[2]; //3C 40
	 volatile uint32_t BDTR; //44
	 volatile uint32_t DCR; //48
	 volatile uint32_t DMAR; //4C
	 volatile uint32_t OR1; //50
	 uint32_t reserved3[3]; //54 58 5C
	 volatile uint32_t OR2; //60
} TIM15_General_Purpose_Type;

typedef struct {
	 volatile uint32_t CR1; //0
	 volatile uint32_t CR2; //4
	 uint32_t reserved1; //8
	 volatile uint32_t DIER; //C
	 volatile uint32_t SR; //10
	 volatile uint32_t EGR; //14
	 volatile uint32_t CCMR1; //18
	 uint32_t reserved2; //1C
	 volatile uint32_t CCER; //20
	 volatile uint32_t CNT; //24
	 volatile uint32_t PSC; //28
	 volatile uint32_t ARR; //2C
	 volatile uint32_t RCR; //30
	 volatile uint32_t CCR1; //34
	uint32_t reserved3[3]; //38 3C 40
	 volatile uint32_t BDTR; //44
	 volatile uint32_t DCR; //48
	 volatile uint32_t DMAR; //4C
	 volatile uint32_t OR1; //50
	 uint32_t reserved4[3]; //54 58 5C
	 volatile uint32_t OR2; //60
} TIM16_17_General_Purpose_Type;

 // Our required addresses for accessing buses, GPIOs, Timers, etc.
 #define TIM15 ((TIM15_General_Purpose_Type *) 0x40014000)
 #define TIM16 ((TIM16_17_General_Purpose_Type *) 0x40014400)
 #define TIM17 ((TIM16_17_General_Purpose_Type *) 0x40014800)

void init_GPIO_ICOC();

int isPedestrianInRange();
void getCrossingRequests();



#endif /* ICOC_H_ */
