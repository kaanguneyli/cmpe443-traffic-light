/*
 * ADC.h
 *
 *  Created on: Dec 20, 2024
 *      Author: Mert Cengiz
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct{
 volatile uint32_t ISR; //0
 volatile uint32_t IER; //4
 volatile uint32_t CR; //8
 volatile uint32_t CFGR; //C
 volatile uint32_t CFG2; //10
 volatile uint32_t SMPR1; //14
 volatile uint32_t SMPR2; //18
 uint32_t reserved2; //1C
 volatile uint32_t TR1; //20
 volatile uint32_t TR2; //24
 volatile uint32_t TR3; //28
 uint32_t reserved3; //2C
 volatile uint32_t SQR1; //30
 volatile uint32_t SQR2; //34
 volatile uint32_t SQR3; //38
 volatile uint32_t SQR4; //3C
 volatile uint32_t DR; //40
 uint32_t reserved4[2]; //44 48
 volatile uint32_t JSQR; //4C
 uint32_t reserved5[4]; //50 54 58 5C
 volatile uint32_t OFR1; //60
 volatile uint32_t OFR2; //64
 volatile uint32_t OFR3; //68
 volatile uint32_t OFR4; //6C
 uint32_t reserved6[4]; //70 74 78 7C
 volatile uint32_t JDR1; //80
 volatile uint32_t JDR2; //84
 volatile uint32_t JDR3; //88
 volatile uint32_t JDR4; //8C
 uint32_t reserved7[4]; //90 94 98 9C
 volatile uint32_t AWD2CR; //A0
 volatile uint32_t AWD3CR; //A4
 uint32_t reserved8[2]; //A8 AC
 volatile uint32_t DIFSEL; //B0
 volatile uint32_t CALFACT; //B0
} ADCType;

typedef struct{
 volatile uint32_t CSR; //0
 uint32_t reserved1; //4
 volatile uint32_t CCR; //8
 volatile uint32_t CDR; //C
} ADCCommon;

#define ISER1 *((volatile uint32_t *) 0xE000E104)
#define RCC_AHB2ENR *((volatile uint32_t *) (0x40021000 + 0x04C))
#define RCC_CCIPR1 *((volatile uint32_t *) 0x40021088)
#define ADC1 ((ADCType *) 0x42028000)
#define ADC ((ADCCommon *) 0x42028300)


#endif /* ADC_H_ */
