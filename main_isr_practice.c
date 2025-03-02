#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;

int volatile btn_flag;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    btn_flag = 1;
  }
}

int main() {
  stdio_init_all();
  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);

  int capture_flag = 0;
  int a;
  while (1) {
    if (btn_flag) {
      printf("btn pressed \n");
      while (!pio_get(BTN_PIN_R)) {
        sleep_ms(1);
      }
      capture_flag = 1;
      btn_flag = 0;
      printf("btn released \n");
    }

    if (capture_flag) {
    }
    
  }
}
