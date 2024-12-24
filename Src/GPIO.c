#include "defines.h"
#include "GPIO.h"
#include "DMA.h"
#include "defines.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define frame_data_lenght (256 * 3 * 8 + 36 * 3 * 8 + 50)

uint32_t reset_matrix[8] = {0};

uint32_t stopping_man[8] = {
    0b00000000000000000000011111100000, // 1
    0b00001000000100000000101001010000, // 2
    0b00001000000100000000010110100000, // 3
    0b00011000000110000001000000001000, // 4
    0b00110000000011000100100000010010, // 5
    0b01001000000100100011100000011100, // 6
    0b00001001100100000000100110010000, // 7
    0b00000110011000000000000000000000, // 8
};

uint32_t walking_man_1[8] = {
    0b00000000000000000000001111000000, // 1
    0b00000100001000000000010000100000, // 2
    0b00000100001000000000001001000000, // 3
    0b00000100001000000000010000100000, // 4
    0b00001100001110000001001000101000, // 5
    0b00010010001010000000110001110000, // 6
    0b00001011100100000000100110010000, // 7
    0b00000110011000000000000000000000, // 8
};

uint32_t walking_man_2_4[8] = {
    0b00000000000000000000001111000000, // 1
    0b00000100001000000000011000100000, // 2
    0b00000100001000000000001001000000, // 3
    0b00000100001000000000010000100000, // 4
    0b00000101101000000000011001100000, // 5
    0b00000110011000000000001111000000, // 6
    0b00000010010000000000001001000000, // 7
    0b00000001100000000000000000000000, // 8
};

uint32_t walking_man_3[8] = {
    0b00000000000000000000001111000000, // 1
    0b00000100001000000000010100100000, // 2
    0b00000100011000000000001001000000, // 3
    0b00000100001000000000010000100000, // 4
    0b00001100011000000001010010010000, // 5
    0b00010100100100000000111000110000, // 6
    0b00001001100100000000100110010000, // 7
    0b00000110011000000000000000000000, // 8
};

// uses PE3
void init_GPIOE_P3(void) {
  RCC_AHB2ENR |= 1 << 4;
  GPIOE->MODER &= ~(0b11 << (3 * 2));
  GPIOE->MODER |= (0b01 << (3 * 2));
}

uint8_t animation_frame[frame_data_lenght];
void init_LED_Matrix() {
  for (int i = 256 * 3 * 8; i < 256 * 3 * 8 + 50; i++) {
    animation_frame[i] = 0;
  }
  RCC_AHB2ENR |= 0b1 << 4;
  GPIOE->MODER &= ~(0b11 << 18);
  GPIOE->MODER |= (0b10 << (18));
  GPIOE->AFRH &= ~(0b1111 << 4);
  GPIOE->AFRH |= 1 << 4;
  RCC_AHB1ENR |= 0b101;
  DMAMUX->C0CR = 42;
  DMA1->CCR1 |= 1 << 1;      // Transfer complete
  DMA1->CCR1 |= 1 << 3;      // Error int
  DMA1->CCR1 |= 1 << 4;      // mem2per
  DMA1->CCR1 |= 1 << 7;      // memory inc
  DMA1->CCR1 |= (0b01 << 8); // 16bits
  DMA1->CPAR1 = (uint32_t) & (TIM1->CCR1);
  DMA1->CMA0AR1 = (uint32_t)animation_frame;
  ISER0 |= 1 << 29;
  RCC_APB2ENR |= 1 << 11; // Enable timer
  TIM1->PSC = 0;          // Not important
  TIM1->ARR = 19;
  TIM1->CCMR1 &= ~(0b11);                 // Output compare
  TIM1->CCMR1 &= ~((1 << 16) | (1 << 4)); // PWM mode 1
  TIM1->CCMR1 |= 0b11 << 5;
  TIM1->BDTR |= 1 << 15;
  TIM1->CCER &= ~(1 << 1);
  TIM1->CCER |= 1 << 0;
  TIM1->DIER |= 1 << 9;
  TIM1->CR1 |= 1;
}

void DMA1_Channel1_IRQHandler(void) {
  if ((DMA1->ISR & (1 << 1)) != 0) {
    DMA1->IFCR |= 7;
    DMA1->CCR1 &= ~(1);
    GPIOA->ODR |= 1 << 9;
  }
  return;
}

// returns false if there is an ongoing animation
// color: 0 for black, 1 for red, 2 for green
void set_frame(uint32_t *frame, uint8_t color, uint8_t brightness) {
  int new_brightness = brightness & ~(1);
  int current_bit = 0;
  for (int frame_line = 0; frame_line < 8; frame_line++) {
    for (int frame_bit = 0; frame_bit < 32; frame_bit++) {
      for (int led_color = 0; led_color < 3; led_color++) {
        for (int bit = 7; bit >= 0; bit--) {
          if ((((led_color == 0) && (color == GREEN)) ||
               ((led_color == 1) && (color == RED))) &&
              ((new_brightness & (1 << bit)) != 0) &&
              ((frame[frame_line] & (1 << frame_bit)) != 0)) {
            animation_frame[current_bit] = 12;
          } else {
            animation_frame[current_bit] = 5;
          }
          current_bit++;
        }
      }
    }
  }
  for (int i = 256 * 3 * 8; i < frame_data_lenght; i++) {
    animation_frame[i] = 0;
  }
  send_LED();
}

bool send_LED() {
  DMA1->CNDTR1 = frame_data_lenght;
  DMA1->CCR1 |= 1;
  return true;
}

void changeLight(uint8_t color, uint8_t brightness) {
  int new_brightness = brightness & ~(1);
  int new_brightness_yellow = (brightness >> 1) & ~(1);
  int i = 256 * 3 * 8;
  for (int led = 0; led < 36; led++) {
    if (((led >= 0 && led < 3) || (led >= 15 && led < 21) ||
         (led >= 33 && led < 36)) &&
        (color == RED)) {
      for (int bit = 0; bit < 24; bit++) {
        if (bit >= 8 && bit < 16 &&
            ((new_brightness & (1 << (bit - 8))) != 0)) {
          animation_frame[i] = 12;
        } else {
          animation_frame[i] = 5;
        }
        i++;
      }
    } else if (((led >= 6 && led < 12) || (led >= 24 && led < 27)) &&
               (color == GREEN)) {
      for (int bit = 0; bit < 24; bit++) {
        if (bit < 8 && ((new_brightness & (1 << (bit))) != 0)) {
          animation_frame[i] = 12;
        } else {
          animation_frame[i] = 5;
        }
        i++;
      }
    } else if (((led >= 3 && led < 6) || (led >= 12 && led < 15) ||
                (led >= 21 && led < 24) || (led >= 30 && led < 33)) &&
               (color == YELLOW)) {
      for (int bit = 0; bit < 24; bit++) {
        if (bit < 16 && ((new_brightness_yellow & (1 << (bit % 8))) != 0)) {
          animation_frame[i] = 12;
        } else {
          animation_frame[i] = 5;
        }
        i++;
      }
    } else {
      for (int bit = 0; bit < 24; bit++) {
        animation_frame[i] = 5;
        i++;
      }
    }
  }
  send_LED();
}
