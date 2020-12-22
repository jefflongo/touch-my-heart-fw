#include "board.h"
#include "patterns.h"

#include <stm32l0xx_hal.h>

void _board_on_first_boot(void) {
    board_power_down();
}

int main(void) {
    HAL_Init();
    board_init();

    __enable_irq();

    pattern_on();

    while (1) {
    }
}
