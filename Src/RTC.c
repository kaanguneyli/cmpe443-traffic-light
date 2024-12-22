/*
 * RTC.c
 *
 *  Created on: Dec 22, 2024
 *      Author: yigit
 */

#include <defines.h>
#include <RTC.h>

#define RTC ((volatile RTCType *) 0x40002800)

static uint8_t bin2bcd(uint8_t value){
	return (uint8_t) ((((value) / 10U) << 4U) | ((value) % 10U));
}

static uint8_t bcd2bin(uint8_t value){
	return (uint8_t) (((uint8_t)((value) & (uint8_t)0xF0U) >> (uint8_t)0x4U) * 10U + ((value) & (uint8_t)0x0FU));
}

static uint8_t RTC_Get_Sec(){ return (uint8_t) (RTC->TR & 0x007F); }
static uint8_t RTC_Get_Min(){ return (uint8_t) ((RTC->TR >> 8) & 0x007F); }
static uint8_t RTC_Get_Hour(){ return (uint8_t) ((RTC->TR >> 16) & 0x003F); }
static uint8_t RTC_Get_MDay(){ return (uint8_t) ((RTC->DR) & 0x003F); }
static uint8_t RTC_Get_Month(){ return (uint8_t) ((RTC->DR >> 8) & 0x001F); }
static uint8_t RTC_Get_WDay() { return (uint8_t) ((RTC->DR >> 13) & 0x7); }
static uint8_t RTC_Get_SYear() {return (uint8_t) ((RTC->DR >> 16) & 0x00FF); }

static void SetTR(uint8_t sec, uint8_t min, uint8_t hour){
	uint8_t secBcd = bin2bcd(sec);
	uint8_t minBcd = bin2bcd(min);
	uint8_t hourBcd = bin2bcd(hour);

//	secBcd &= ~(1 << 7);
//	RTC->TR &= ~(0b1111111);
//	RTC->TR |= secBcd;
//
//	minBcd &= ~(1 << 7);
//	RTC->TR &= ~(0b1111111 << 8);
//	RTC->TR |= minBcd << 8;
//
//	hourBcd &= ~(0b11 << 6);
//	RTC->TR &= ~(0b111111 << 16);
//	RTC->TR |= hourBcd << 16;

	uint32_t final = (hourBcd << 16) | (minBcd << 8) | (secBcd);
	RTC->TR = final;
}

static void SetDR(uint8_t wday, uint8_t mday, uint8_t mon, uint8_t year_s){
	uint8_t mdayBcd = bin2bcd(mday);
	uint8_t monBcd = bin2bcd(mon);
	uint8_t year_sBcd = bin2bcd(year_s);

//	mdayBcd &= ~(0b11 << 6);
//	RTC->DR &= ~(0b111111);
//	RTC->DR |= mdayBcd;
//
//	monBcd &= ~(0b111 << 5);
//	RTC->DR &= ~(0b11111 << 8);
//	RTC->DR |= monBcd;
//
//	RTC->DR &= ~(0b111 << 13);
//	RTC->DR |= wday << 13;
//
//	RTC->DR &= ~(0xFF << 16);
//	RTC->DR |= year_sBcd << 16;

	uint32_t final = (year_sBcd << 16) | (wday << 13) | (monBcd << 8) | (mdayBcd);
	RTC->DR = final;
}

void RTC_Update(Timestamp * timestamp){
	// disable backup domain write protection
	PWR_CR1 |= 1 << 8;
	// unlock write protection on RTC
	RTC->WPR = 0xCAU;
	RTC->WPR = 0x53U;
	// enter initialization mode
	RTC->ICSR |= 1 << 7;
	while ((RTC->ICSR & (1 << 6)) == 0);
	// PRER is configured out-of-reset to enable 1Hz for LSE (32768 Hz)
	// set TR and DR
	SetTR(timestamp->sec, timestamp->min, timestamp->hour);
	SetDR(timestamp->wday, timestamp->mday, timestamp->mon, timestamp->year_s);
	// exit initialization mode
	RTC->ICSR &= ~(1 << 7);
	// poll INITF not specified AN4759 Table 6 (page 11)

	// disable write protection on RTC
	RTC->WPR = 0xFF;
	PWR_CR1 &= ~(1 << 8);

}

void RTC_Get(Timestamp * timestamp){
	timestamp->sec = bcd2bin(RTC_Get_Sec());
	timestamp->min = bcd2bin(RTC_Get_Min());
	timestamp->hour = bcd2bin(RTC_Get_Hour());
	timestamp->mday = bcd2bin(RTC_Get_MDay());
	timestamp->mon = bcd2bin(RTC_Get_Month());
	timestamp->wday = bcd2bin(RTC_Get_WDay());
	timestamp->year_s = bcd2bin(RTC_Get_SYear());
}

void RTC_Init(){
	// disable backup domain write protection
	PWR_CR1 |= 1 << 8;
	// enable LSE and choose LSE for RTC Clock
	RCC_BDCR |= 1;
	while ((RCC_BDCR & (1 << 1)) == 0);
	RCC_BDCR |= 0b01 << 8;
	// enable RTC APB clock
	RCC_APB1ENR1 |= 1 << 10;
	// enable RTC
	RCC_BDCR |= 1 << 15;
	// unlock write protection on RTC
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;
	// enter initialization mode
	RTC->ICSR |= 1 << 7;
	while ((RTC->ICSR & (1 << 6)) == 0);
	// PRER is configured out-of-reset to enable 1Hz for LSE (32768 Hz)
	// exit initialization mode
	RTC->ICSR &= ~(1 << 7);
	// poll INITF not specified AN4759 Table 6 (page 11)

	// disable write protection on RTC
	RTC->WPR = 0xFF;
	PWR_CR1 &= ~(1 << 8);
}

