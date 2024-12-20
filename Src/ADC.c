/*
 * ADC.c
 *
 *  Created on: Dec 20, 2024
 *      Author: Mert Cengiz
 */

#include "ADC.h"

uint16_t brightness;
uint8_t read_time = 1;
bool read_brightness_flag = false;

void init_ADC(void){
	RCC_AHB2ENR |= (1 << 13);
	ADC1->CR &= ~(1 << 29);
	ADC1->CR |= (1 << 28);
	RCC_CCIPR1 |= (0b11 << (14 * 2));
	ADC->CCR |= (0b11 << (8 * 2));
	ADC1->SMPR1 |= (0b111 << (3 * 3));
	ADC1->SQR1 &= ~(0b1111 << 0);
	ADC1->SQR1 |= (1 << 0);
	ADC1->SQR1 |= (0b11 << 6);
	ADC1->SQR1 |= (0b11 << 12);
	ADC1->CR |= (1 << 31);
	while((ADC1->CR & (1 << 31)) != 0){}
	ADC1->CR |= (1 << 0);
	while((ADC1->ISR & (1 << 0)) == 0) {}
	ADC1->CR |= (1 << 2);
	ADC1->IER |= (1 << 2);
	ISER1 |= (1 << 5);
}

void ADC1_2_IRQHandler(void){
	if((ADC1->ISR & (1 << 2)) != 0){
		if (read_time == 1){
			uint16_t dummy_light = ADC1->DR;
			read_time++;
		}
		else if (read_time == 2){
			brightness = ADC1->DR;
			brightness = brightness / 16;
			read_time--;
			read_brightness_flag = true;
		}
	}
}


void get_brightness(void){
	ADC1->CR |= (1 << 2);
}
