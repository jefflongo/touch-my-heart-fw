#include "board.h"

#include <stm32l0xx_hal.h>
#include <stm32l0xx_ll_exti.h>
#include <stm32l0xx_ll_gpio.h>

#define HANDLER(thing, action)                                                                     \
    void thing##_Handler(void);                                                                    \
    void thing##_Handler(void) {                                                                   \
        action;                                                                                    \
    }

HANDLER(HardFault, while (1));
HANDLER(MemManage, while (1));
HANDLER(BusFault, while (1));
HANDLER(UsageFault, while (1));

HANDLER(DebugMon, );

HANDLER(SysTick, HAL_IncTick());

#define DEBOUNCE_TIME 200
static uint32_t last_tick = 0;

void EXTI0_1_IRQHandler(void) {
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0)) {
        if (board_get_wakeup_pin_state() == 0) {
            uint32_t now = HAL_GetTick();
            if (now - last_tick > DEBOUNCE_TIME) {
                board_set_leds(0x00000000);
                LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
                board_power_down();
            }
            last_tick = now;
        }
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
    }
}