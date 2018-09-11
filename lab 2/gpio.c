#include "gpio.h"

GPIO_Type* GPIO_Ptr = ((GPIO_Type*)GPIO_BASE);
// Inputs:
//  gpio_num - gpio number 0-31
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
  if(dir){
    //printf("Value of shift: %d\n", gpio_num);
    uint32_t prev_dir = GPIO_Ptr->DIR;
    uint32_t value = dir << (gpio_num);
    //printf("Value: %x\n", value);
    uint32_t new_dir = value | prev_dir;
    //printf("Address DIR value: %X\n", GPIO_Ptr->DIR);
    //printf("New DIR value: %X\n", new_dir);
    GPIO_Ptr->DIR = new_dir;
  }else{
    uint32_t prev_dir = GPIO_Ptr->DIR;
    uint32_t value = ~(1 << (gpio_num));
    uint32_t new_dir = value & prev_dir;
    //printf("Address DIR value: %X\n", GPIO_Ptr->DIR);
    //printf("New DIR value: %X\n", new_dir);
    GPIO_Ptr->DIR = new_dir;
    GPIO_Ptr->PIN_CNF[gpio_num] = 0x0;
  }

}

// Set gpio_num high
// Inputs:
//  gpio_num - gpio number 0-31
void gpio_set(uint8_t gpio_num) {
    uint32_t prev_out = GPIO_Ptr->OUT;
    uint32_t value = 1 << (gpio_num);
    uint32_t new_out = value | prev_out;
    //printf("Address OUT value: %X\n", GPIO_Ptr->OUT);
    //printf("New OUT value: %X\n", new_out);
    GPIO_Ptr->OUT = new_out;
}

// Set gpio_num low
// Inputs:
//  gpio_num - gpio number 0-31
void gpio_clear(uint8_t gpio_num) {
    uint32_t prev_out = GPIO_Ptr->OUT;
    uint32_t value = ~(1 << (gpio_num));
    uint32_t new_out = value & prev_out;
    //printf("Address OUT value: %X\n", GPIO_Ptr->OUT);
    //printf("New OUT value: %X\n", new_out);
    GPIO_Ptr->OUT = new_out;
}

// Inputs:
//  gpio_num - gpio number 0-31
bool gpio_read(uint8_t gpio_num) {
    uint32_t input = GPIO_Ptr->IN;
    //printf("Address of IN: %X\n", &GPIO_Ptr->IN);
    //printf("Value of IN register: %X\n", input);
    uint32_t value = (input >> (gpio_num)) & (0b1);
    //printf("New IN value: %X\n", value);
    return value;
}
