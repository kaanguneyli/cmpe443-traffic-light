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




#endif /* TIMBASIC_H_ */
