// Blink app
//
// Blinks the LEDs on Buckler

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_error.h"
#include "app_timer.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_gpio.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"
#include "software_interrupt.h"

#include "buckler.h"

void SWI1_EGU1_IRQHandler(void) {
    NRF_EGU1->EVENTS_TRIGGERED[0] = 0;
    printf("Software\n");
    nrf_delay_ms(5000);
}

void GPIOTE_IRQHandler(void) {
    NRF_GPIOTE->EVENTS_IN[0] = 0;
    printf(" Button Interrupt!\n");
    //while(1){
      gpio_clear(25);
      nrf_delay_ms(5000);
      gpio_set(25);
      nrf_delay_ms(500);
    //}
}

int main(void) {
  ret_code_t error_code = NRF_SUCCESS;

  // initialize RTT library
  error_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(error_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  printf("Log initialized!\n");

  NRF_GPIOTE->CONFIG[0] = 0x21C01;
  NRF_GPIOTE->INTENSET = 0x1;
  NRF_GPIOTE->CONFIG[1]=0x21C01;
  NVIC_EnableIRQ(GPIOTE_IRQn);

  gpio_config(28, 0);       //BUTTON0 as input
  gpio_config(22, 0);       //SWITCH0 as input
  gpio_config(25, 1);       //LED0 as output
  gpio_set(25);             //Turn of the LED

  software_interrupt_init();

  NVIC_SetPriority(GPIOTE_IRQn,0);
  NVIC_SetPriority(SWI1_EGU1_IRQn,7);

  // loop forever
  while (1) {
    printf("Looping\n");
    //if(gpio_read(22)){
    //  __WFI();
    //}
    nrf_delay_ms(500);
    software_interrupt_generate();
  }
}
