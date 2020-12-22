#include "board.h"

#include <stm32l0xx_hal.h>

void _board_on_first_boot(void) {
    board_power_down();
}

#define ANIMATION_DELAY 50
void play_pattern() {
    board_set_leds(0x80001);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x40002);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x20004);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x10008);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x08010);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x04020);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x02040);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x01080);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x00900);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x00600);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x00900);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x01080);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x02040);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x04020);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x08010);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x10008);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x20004);
    HAL_Delay(ANIMATION_DELAY);
    board_set_leds(0x40002);
    HAL_Delay(ANIMATION_DELAY);
}

int main(void) {
    HAL_Init();
    board_init();

    __enable_irq();

    while (1) {
        play_pattern();
    }
}
