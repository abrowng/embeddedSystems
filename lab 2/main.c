// Blink app
//
// Blinks the LEDs on Buckler

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_error.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"

#include "buckler.h"
#include "gpio.h"

//GPIO_Type* GPIO_Ptr = ((GPIO_Type*)GPIO_BASE);

int main(void) {
  ret_code_t error_code = NRF_SUCCESS;

  // initialize RTT library
  error_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(error_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  printf("Log initialized!\n");

  //printf("Address of GPIO_OUT: 0x%X\n", &(*GPIO_Ptr).OUT);
  //printf("Address of GPIO_DIR: 0x%X\n", &(*GPIO_Ptr).DIR);
  //printf("\n");

  gpio_config(22, INPUT);
  gpio_config(23, OUTPUT);
  gpio_config(24, OUTPUT);
  gpio_config(25, OUTPUT);
  gpio_config(28, INPUT);

  gpio_set(23);
  // loop forever
  while (1) {

    //printf("Value of BUTTON0: %d\n", gpio_read(28));
    //printf("Value of SWITCH0: %d\n", gpio_read(22));
    if(gpio_read(28)){
      gpio_set(25);
    }else{
      gpio_clear(25);
    }

    if(gpio_read(22)){
      gpio_clear(24);
    }else{
      gpio_set(24);
    }

//    printf("\n");

    //(*GPIO_Ptr).OUT = ~(*GPIO_Ptr).OUT & (LED1);
    //printf("Value of GPIO_OUT: 0x%X\n", (*GPIO_Ptr).OUT);
    //uint32_t BUTTON0_VALUE = ((*GPIO_Ptr).IN >> 28) & (0b1);
    //uint32_t SWITCH0_VALUE = ((*GPIO_Ptr).IN >> 22) & (0b1);
    //printf("Value of BUTTON0: %X\n", BUTTON0_VALUE);
    //printf("Value of SWITCH0: %X\n", SWITCH0_VALUE);
    nrf_delay_ms(1);
  }
}
