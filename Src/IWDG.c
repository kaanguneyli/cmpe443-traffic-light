#include "IWDG.h"
#include <stdint.h>

// void init_IWDG() {
//   IWDG->KR = 0x5555;
//   IWDG->PR = 0x6;
//   IWDG->RLR = 0x0FFF;
//   IWDG->KR = 0xCCCC;
// }

void init_IWDG() {
  IWDG->KR = 0xCCCC;
  IWDG->KR = 0x5555;
  IWDG->PR = 0x6;
  IWDG->RLR = 0x0FFF;
  while (IWDG->SR != 0)
    ;
  IWDG->KR = 0xAAAA;
}

void reset_IWDG() { IWDG->KR = 0xAAAA; }