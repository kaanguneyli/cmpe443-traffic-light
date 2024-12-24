// #include "GPIO.h"
// #include "TIMBasic.h"
// #include "defines.h"
// #include <stdbool.h>
// #include <stdint.h>

// void __enable_irq() {
//   __asm volatile("mov r0, #0\t\n"
//                  "msr primask, r0\t\n");
// }

// void init() {
//   initStateTimer();
//   __enable_irq();
// }

// extern uint32_t stopping_man[8];

// int main(void) {

//   init();
//   init_LED_Matrix();
//   send_Animation(stopping_man, RED, 255);
// }
#include "defines.h"
#include <stdint.h>
#include "GPIO.h"


//int i = 0;
//void TIM2_IRQHandler(void) {
//  if ((TIM2->SR & (1 << 0)) != 0) {
//    if (i < 1024) {
//    	TIM2->CCR2 = 3;
//    	TIM2->CCR1 = 3;
//    	TIM2->CNT = 0;
//    	TIM2->SR &= ~(1 << 0);
//
//      GPIOA->ODR |= (1 << 9);
//      i++;
//    }
//  }
//}
int bruh ;
extern uint32_t stopping_man[8];
extern uint32_t walking_man_1[8];
extern uint32_t walking_man_2_4[8];
extern uint32_t walking_man_3[8];
extern uint32_t walking_man_4[8];
int main(void) {

	while((RCC_CR & (1<<1)) == 0);
	RCC_CR &= ~(0b1111<<4);
	RCC_CR |= (0b1001<<4);
	while((RCC_CR & (1<<1)) == 0);
	RCC_CR |= (0b1<<3);
	while((RCC_CR & (1<<1)) == 0);
	init_LED_Matrix();
	set_frame(stopping_man, RED, 16);
	changeLight(GREEN, 255);
	send_LED();
  __asm volatile( // NEW! enable all interrupts that are configured
      "mov r0, #0 \n\t"
      "msr primask, r0 \n\t");
  for(int i=0;i<1000000;i++){
	  bruh = 0;
  }
  set_frame(walking_man_1, GREEN, 16);
  send_LED();
	  for(int i=0;i<1000000;i++){
		  bruh = 0;
	  }
	  set_frame(walking_man_2_4, GREEN, 16);
	  send_LED();
		  for(int i=0;i<1000000;i++){
			  bruh = 0;
		  }
		  set_frame(walking_man_3, GREEN, 16);
		  send_LED();
  while (1) {
  }
  return 0;
}
