#pragma once

#include <stdbool.h>
#include <stdint.h>

void board_set_leds(uint32_t mask);
bool board_get_wakeup_pin_state(void);
void board_power_down(void);
void board_init(void);

void _board_on_wakeup(void);
void _board_on_first_boot(void);
