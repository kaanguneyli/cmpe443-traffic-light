/*
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
*/

/*
#define wait_millisecond 1000
uint32_t wait_counter=0;
 int main(void)
 {
 //TurnontheGPIOports.
 *((uint32_t*)(0x40021000+0x4C))|=0x07;
 //ToaccesstheRedLight.
 *((uint32_t*)(0x42020000+0x00))&=~(0x03<<(9*2));
 *((uint32_t*)(0x42020000+0x00))|=(0x01<<(9*2));
 //ToaccesstheBlueLight.
 *((uint32_t*)(0x42020400+0x00))&=~(0x03<<(7*2));
 *((uint32_t*)(0x42020400+0x00))|=(0x01<<(7*2));
 //ToaccesstheYellowLight.
 *((uint32_t*)(0x42020800+0x00))&=~(0x03<<(7*2));
 *((uint32_t*)(0x42020800+0x00))|=(0x01<<(7*2));
 while(1){
 int index;
 //TurnontheRedLight.
 *((uint32_t*)(0x42020000+0x14))|=(0x01<<9);
 //TurnontheBlueLight.
 *((uint32_t*)(0x42020400+0x14))|=(0x01<<7);
 //TurnontheYellowLight.
 *((uint32_t*)(0x42020800+0x14))|=(0x01<<7);
 //Uselesslooptomaketimeforthehumaneye.
 for(index=0;index<wait_millisecond*333;index++){
 wait_counter=wait_counter+1;
 }
  // Turn off the Red Light.
  *((uint32_t *) (0x42020000 + 0x14)) &= ~(0x01 << 9);
  // Turn off the Blue Light.
  *((uint32_t *) (0x42020400 + 0x14)) &= ~(0x01 << 7);
  // Turn off the Yellow Light.
  *((uint32_t *) (0x42020800 + 0x14)) &= ~(0x01 << 7);
  // Useless loop to make time for the human eye.
  for (index = 0; index < wait_millisecond * 333; index ++) {
  wait_counter = wait_counter + 1;
  }
  }
  }
*/



#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/*
#define wait_millisecond 1000
uint32_t wait_counter=0;
 int main(void)
 {
 //TurnontheGPIOports.
 ((uint32_t)(0x40021000+0x4C))|=0x07;
 //ToaccesstheRedLight.
 ((uint32_t)(0x42020000+0x00))&=~(0x03<<(9*2));
 ((uint32_t)(0x42020000+0x00))|=(0x01<<(9*2));
 //ToaccesstheBlueLight.
 ((uint32_t)(0x42020400+0x00))&=~(0x03<<(7*2));
 ((uint32_t)(0x42020400+0x00))|=(0x01<<(7*2));
 //ToaccesstheYellowLight.
 ((uint32_t)(0x42020800+0x00))&=~(0x03<<(7*2));
 ((uint32_t)(0x42020800+0x00))|=(0x01<<(7*2));
 while(1){
 int index;
 //TurnontheRedLight.
 ((uint32_t)(0x42020000+0x14))|=(0x01<<9);
 //TurnontheBlueLight.
 ((uint32_t)(0x42020400+0x14))|=(0x01<<7);
 //TurnontheYellowLight.
 ((uint32_t)(0x42020800+0x14))|=(0x01<<7);
 //Uselesslooptomaketimeforthehumaneye.
 for(index=0;index<wait_millisecond*333;index++){
 wait_counter=wait_counter+1;
 }
  // Turn off the Red Light.
  *((uint32_t *) (0x42020000 + 0x14)) &= ~(0x01 << 9);
  // Turn off the Blue Light.
  *((uint32_t *) (0x42020400 + 0x14)) &= ~(0x01 << 7);
  // Turn off the Yellow Light.
  *((uint32_t *) (0x42020800 + 0x14)) &= ~(0x01 << 7);
  // Useless loop to make time for the human eye.
  for (index = 0; index < wait_millisecond * 333; index ++) {
  wait_counter = wait_counter + 1;
  }
  }
  }
*/




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

 typedef struct {
	 volatile uint32_t MODER;
	 volatile uint32_t OTYPER;
	 volatile uint32_t OSPEEDR;
	 volatile uint32_t PUPDR;
	 volatile uint32_t IDR;
	 volatile uint32_t ODR;
	 volatile uint32_t BSRR;
	 volatile uint32_t LCKR;
	 volatile uint32_t AFRL;
	 volatile uint32_t AFRH;
	 volatile uint32_t BRR;
	 uint32_t reserved;
	 volatile uint32_t SECCFGR;
} GPIO;

 // Our required addresses for accessing buses, GPIOs, Timers, etc.
 #define RCC_AHB2ENR *((volatile uint32_t *) 0x4002104C)
 #define RCC_APB1ENR1 *((volatile uint32_t *) 0x40021058)
 #define RCC_APB2ENR *((volatile uint32_t *) 0x40021060)
 #define ISER2 *((volatile uint32_t *) 0xE000E108) //read from cortex-m33 dgug
 #define GPIOA ((GPIO *) 0x42020000)
 #define GPIOB ((GPIO *) 0x42020400)
 #define GPIOC ((GPIO *) 0x42020800)
 #define GPIOD ((GPIO *) 0x42020C00)
 #define GPIOE ((GPIO *) 0x42021000)
 #define TIM15 ((TIM15_General_Purpose_Type *) 0x40014000)
 #define TIM16 ((TIM16_17_General_Purpose_Type *) 0x40014400)
 #define TIM17 ((TIM16_17_General_Purpose_Type *) 0x40014800)

 // Variables used during our calculations
 uint8_t state = 0;
 uint32_t time_start = 0;
 uint32_t time_end = 0;
 // end PS 9@Cmpe443
 uint32_t number_of_overflows_in_between = 0;
 uint32_t number_of_pulses_in_between = 0;
 uint32_t distance_in_centimeters = 0;

 uint32_t min_distance = 1000;
 uint32_t max_distance = 2000;
 uint8_t measuring = 0;
//uint8_t isHandInRange = 0;
//uint8_t isHandInRange_Read = 0;

 //float min_number_of_pulses = min_distance / (0.017); // Used "distance = (0.017) * (elapsed_time)" where distance is in cm, 0.017 is the
  //float max_number_of_pulses = min_distance / (0.017); // speed of sound in cm/microseconds, elapsed_time is in microseconds. (continued below)
  // As our PSC will be set as 3, each clock cycle will correspond to 1 microsecond. In this case, elapsed time is equal to the number of pulses.

 // start PS 9@Cmpe443
 // Our interrupt handling function
 void TIM15_IRQHandler(void) {
	 // We enter here in case of an input channel interrupt (input capture)
	 if ((TIM15->SR & (1 << 1)) != 0) {
		 // Reading capture/compare register in input mode reset status bit.
		 //TIM15->SR &= ~(1 << 1);

		 // We enter here when ECHO pin has a rising edge
		 if (state == 0) {
			 //GPIOB->ODR |= (1 << 10);
			 state = 1;
			 time_start = TIM15->CCR1;
			 // end PS 9@Cmpe443
			 // Initializations of our variables
			 number_of_overflows_in_between = 0;
			 number_of_pulses_in_between = -1;
			 distance_in_centimeters = -1;
		 }
		 // start PS 9@Cmpe443
		 // We enter here when ECHO pin has a falling edge
		 else {
			 state = 0;
			 time_end = TIM15->CCR1;
			 // end PS 9@Cmpe443
			 // Distance calculation (in pulses)
			 number_of_pulses_in_between = (number_of_overflows_in_between * ((TIM15->ARR) + 1)) - time_start + time_end;
			 distance_in_centimeters = number_of_pulses_in_between * 17 / 1000;
			 measuring = 0;
		 }
	 }

	 // start PS 9@Cmpe443
	 // We enter here in case of an overflow in our timer
	 if ((TIM15->SR & (1 << 0)) != 0) {
		 TIM15->SR &= ~(1 << 0); // Fix state register
		 // end PS 9@Cmpe443
		 number_of_overflows_in_between += 1; // Incerementing the number of overflows (between the rising and falling edges of our ECHO pin)
		 //GPIOB->ODR |= (1 << 11); // Opening up trigger (TRIG pin)
		 GPIOB->ODR &= ~(1 << 10); // Closing our buzzer
		 // start PS 9@Cmpe443
		 //GPIOA->ODR &= ~(1 << 9); // Closing our output light (for debugging purposes)
	 }

	 // We enter here in case of an output channel interrupt
	 if ((TIM15->SR & (1 << 2)) != 0) {
		 //GPIOB->ODR |= (1 << 10);

		 TIM15->SR &= ~(1 << 2);  // Fix state register
		 // end PS 9@Cmpe443

		 GPIOB->ODR &= ~(1 << 11); // Closing our trigger
	 }

	 // start PS 9@Cmpe443
	 // Overcapture check (in case of overcaptures, PC7 (yellow board light) is activated)
	 if ((TIM15->SR & (1 << 9)) != 0) {
		 TIM15->SR &= ~(1 << 9);
		 if ((GPIOC->ODR & (1 << 7)) == 0) {
			 GPIOC->ODR |= (1 << 7);
		 }
		 else {
			 GPIOC->ODR &= ~(1 << 7);
		 }
	 }
	 // end PS 9@Cmpe443
}

 void init_GPIO(void) {
	 ////////////////////////////////////////
	 // --Part 1: Setting the GPIO--
	 ////////////////////////////////////////

	 // Open GPIO A-B-C using the corresponding bus
	 RCC_AHB2ENR |= 0b111;

	 // Set modes of PA9, PB10, PB11, PC7 to output
	 GPIOA->MODER &= ~(0b10 << (9 * 2));
	 GPIOA->MODER |= 0b01 << (9 * 2);
	 // end PS 9@Cmpe443
	 GPIOB->MODER &= ~(0b10 << (10 * 2));
	 GPIOB->MODER |= 0b01 << (10 * 2);
	 GPIOB->MODER &= ~(0b10 << (11 * 2));
	 GPIOB->MODER |= 0b01 << (11 * 2);
	 // start PS 9@Cmpe443
	 GPIOC->MODER &= ~(0b10 << (7 * 2));
	 GPIOC->MODER |= 0b01 << (7 * 2);

	 // Setting modes of PA2 and PA3 to "alternate function"
	 GPIOA->MODER &= ~(0b0101 << (2 * 2));
	 GPIOA->MODER |= (0b1010 << (2 * 2));

	 // Set PA2 to TIM15_CH1, set PA3 to TIM15_CH2
	 GPIOA->AFRL &= ~(0b00010001 << (2 * 4));
	 GPIOA->AFRL |= 0b11101110 << (2 * 4);

	 ////////////////////////////////////////
	 // --Part 2: Setting the Timer--
	 ////////////////////////////////////////

	 // Open TIM15 from the corresponding bus
	 RCC_APB2ENR |= 1 << 16;

	 // end PS 9@Cmpe443
	 // Prescale clock speed from 4MHz to 1MHz (now every pulse takes 1 microsecond)
	 TIM15->PSC = 3;

	 // Set ARR to 50 milliseconds (50000 microseconds)
	 TIM15->ARR = 49999;
	 // start PS 9@Cmpe443

	 // Enable OC and OCN
	 TIM15->BDTR |= 1 << 15;

	 ///////////////////////////////////////////////////////
	 // ----Part 2.1: Setting Channel 2----
	 // ----This channel will be the Output Compare/OC channel----
	 ///////////////////////////////////////////////////////

	 // Setting CC2 to output mode
	 TIM15->CCMR1 &= ~(0b11 << 8);

	 // Set PWM 1 mode for Channel 2
	 TIM15->CCMR1 &= ~((1 << 24) | (1 << 12));
	 TIM15->CCMR1 |= 0b11 << 13;

	 // Setting polarity to active high
	 TIM15->CCER &= ~(1 << 5);

	 // CC2 output enable
	 TIM15->CCER |= (1 << 4);

	 // end PS 9@Cmpe443
	 // Setting output event time to 10 microseconds (TRIG pin pulse time)
	 TIM15->CCR2 = 9;
	 // start PS 9@Cmpe443

	 ///////////////////////////////////////////////////////
	 // ----Part 2.2: Setting Channel 1----
	 // ----This channel will be the Input Capture/IC channel---
	 ///////////////////////////////////////////////////////

	 // Setting CC1 to input mode (IC2->TI2)
	 TIM15->CCMR1 &= ~(0b10);
	 TIM15->CCMR1 |= 0b01;

	 // Set input capture enable on both rising and falling edges
	 TIM15->CCER |= 0b1011;

	 ////////////////////////////////////////
	 // --Part 3: Setting Interrupts + Starting The Timer--
	 ////////////////////////////////////////

	 // Activate all CC1+CC2+Update interrupts
	 TIM15->DIER |= 0b111;

	 // Reset SR
	 TIM15->SR = 0;

	 // Enable TIM15 interrupt global signal
	 ISER2 |= 1 << 5;

	 // Start the timer
	 TIM15->CR1 |= 1;
 }

 void __enable_interrupts(void) {
	 ////////////////////////////////////////
	 // --Part 4: Enable interrupts with inline Assembly + wait--
	 ////////////////////////////////////////

	 // Enable all interrupts that are configured
	 __asm volatile(
			 "mov r0, #0 \n\t"
			 "msr primask, r0 \n\t"
	 );
 }

 void distance_check(void) {
	 // Calculating if the object is in desired range (in terms of clock cycles, conversions are done at the beginning of our code)
	 // Our object is inside the desired range

	 //if ((min_distance <= number_of_pulses_in_between) && (number_of_pulses_in_between <= max_distance)) {
	 //	  //GPIOA->ODR |= (1 << 9); // Open the output light (for debugging purposes)
	 //	  GPIOB->ODR |= (1 << 10); // Open the buzzer
	 //}
	 if ((17 <= distance_in_centimeters) && (distance_in_centimeters <= 34)) {
		 //isHandInRange = 1;
		 GPIOB->ODR |= (1 << 10); // Open the buzzer
	 }


	 // Our object is outside the desired range
	 else {
		 //GPIOA->ODR &= (1 << 9); // Close the output light (for debugging purposes)
		 //isHandInRange = 0;
		 GPIOB->ODR &= ~(1 << 10); // Close the buzzer
	 }
	 // start PS 9@Cmpe443
 }

 void get_distance(void) {
	 GPIOB->ODR |= (1 << 11); // Opening up trigger (TRIG pin)
	 TIM15->CCR1 = 0;
	 measuring = 1;
 }

 // start PS 9@Cmpe443
 // Our main code
 int main(void) {
	 init_GPIO();
	 __enable_interrupts();


	 // end PS 9@Cmpe443
	 //GPIOB->ODR |= (1 << 11); // Opening up trigger (TRIG pin)
	 // start PS 9@Cmpe443
	 //get_distance();

	 // Infinite loop
	 while(1)
	 {
		 if (measuring == 0) {
			 get_distance();
		 }

		 // end PS 9@Cmpe443
		 //for (int i=0;i<1000000;i++){}


		 // Wait for any interrputs
		 __asm volatile("wfi");
		 distance_check();
	 }
	 return 0;
	 // end PS 9@Cmpe443
}




/*
// PSUEDOCODE
 handle_interrupt() {
	 if (input_interrupt()) {
		 if (high_edge()) {
			 start_measuring_time();
		 }
		 else {
			 stop_measuring_time();
		 }
	 }
	 if (output_interrupt()) {
		 stop_trigger();
	 }
	 if (overflow()) {
		 deactivate_buzzer();
		 start_trigger();
		 increment_overflow_counter();
	 }
	 if (overcapture()) {
		 show_overcapture();
	 }
 }

 main(){
	 init_GPIO();
	 init_TIMER();
	 activate_interrupts();
	 start_trigger();
	 while(1) {
		 convert_to_distance();
		 if (distance_in_range()) {
			 activate_buzzer();
		 }
		 else {
			 deactivate_buzzer();
		 }
		 wait_for_interrupt();
	 }
 }
*/
