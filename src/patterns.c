#include "patterns.h"

#include "board.h"

#include <stm32l0xx_hal.h>

#define ANIMATION_DELAY 60
#define NUM_STAGES 10;

static int skip = 0;

#define PLAY_STAGE(leds)                                                                           \
    do {                                                                                           \
        board_set_leds(leds);                                                                      \
        skip--;                                                                                    \
        HAL_Delay(ANIMATION_DELAY);                                                                \
    } while (0)

#define REVERSE_STAGE(leds)                                                                        \
    do {                                                                                           \
                                                                                                   \
        if (skip) {                                                                                \
            skip--;                                                                                \
        } else {                                                                                   \
            board_set_leds(leds);                                                                  \
            HAL_Delay(ANIMATION_DELAY);                                                            \
        }                                                                                          \
    } while (0)

void pattern_on(void) {
    skip = NUM_STAGES;
    PLAY_STAGE(0x80001);
    PLAY_STAGE(0xC0003);
    PLAY_STAGE(0xE0007);
    PLAY_STAGE(0xF000F);
    PLAY_STAGE(0xF801F);
    PLAY_STAGE(0xFC03F);
    PLAY_STAGE(0xFE07F);
    PLAY_STAGE(0xFF0FF);
    PLAY_STAGE(0xFF9FF);
    PLAY_STAGE(0xFFFFF);
}

void pattern_off(void) {
    REVERSE_STAGE(0xFF9FF);
    REVERSE_STAGE(0xFF0FF);
    REVERSE_STAGE(0xFE07F);
    REVERSE_STAGE(0xFC03F);
    REVERSE_STAGE(0xF801F);
    REVERSE_STAGE(0xF000F);
    REVERSE_STAGE(0xE0007);
    REVERSE_STAGE(0xC0003);
    REVERSE_STAGE(0x80001);
    REVERSE_STAGE(0x00000);
}
