/*
 * RTC.h
 *
 *  Created on: Dec 22, 2024
 *      Author: yigit
 */

#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>

typedef enum {
	MON = 0x01,
	TUE = 0x02,
	WED = 0x03,
	THU = 0x04,
	FRI = 0x04,
	SAT = 0x06,
	SUN = 0x07
} DaysOfWeek;

typedef struct {
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t mday;
	uint8_t mon;
	uint8_t year;
	uint8_t wday;
	uint8_t yday;
	uint8_t isdst;
	uint8_t year_s; // year in short notation
} Timestamp;

typedef struct {
	volatile uint32_t TR;
	volatile uint32_t DR;
	volatile uint32_t SSR;
	volatile uint32_t ICSR;
	volatile uint32_t PRER;
	volatile uint32_t WUTR;
	volatile uint32_t CR;
	volatile uint32_t PRIVCR;
	volatile uint32_t SMCR;
	volatile uint32_t WPR;
	volatile uint32_t CALR;
	volatile uint32_t SHIFTR;
	volatile uint32_t TSTR;
	volatile uint32_t TSDR;
	volatile uint32_t TSSSR;
	uint32_t reserved;
	volatile uint32_t ALRMAR;
	volatile uint32_t ALRMASSR;
	volatile uint32_t ALRMBR;
	volatile uint32_t ALRMBSSR;
	volatile uint32_t SR;
	volatile uint32_t MISR;
	volatile uint32_t SMISR;
	volatile uint32_t SCR;
} RTCType;

// call after LPUART1_Initialization
void RTC_Init(Timestamp * timestamp);
void RTC_Get(Timestamp * timestamp);



#endif /* RTC_H_ */
