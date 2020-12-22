#include "board.h"

#include <assert.h>
#include <stm32l0xx.h>
#include <stm32l0xx_hal_cortex.h>
#include <stm32l0xx_hal_rcc.h>
#include <stm32l0xx_ll_bus.h>
#include <stm32l0xx_ll_cortex.h>
#include <stm32l0xx_ll_crs.h>
#include <stm32l0xx_ll_dma.h>
#include <stm32l0xx_ll_exti.h>
#include <stm32l0xx_ll_gpio.h>
#include <stm32l0xx_ll_pwr.h>
#include <stm32l0xx_ll_rcc.h>
#include <stm32l0xx_ll_system.h>
#include <stm32l0xx_ll_utils.h>

#define WAKEUP_pin LL_GPIO_PIN_0
#define WAKEUP_port GPIOA
#define LED20_pin LL_GPIO_PIN_1
#define LED20_port GPIOA
#define LED19_pin LL_GPIO_PIN_2
#define LED19_port GPIOA
#define LED18_pin LL_GPIO_PIN_3
#define LED18_port GPIOA
#define LED17_pin LL_GPIO_PIN_4
#define LED17_port GPIOA
#define LED16_pin LL_GPIO_PIN_5
#define LED16_port GPIOA
#define LED15_pin LL_GPIO_PIN_6
#define LED15_port GPIOA
#define LED14_pin LL_GPIO_PIN_7
#define LED14_port GPIOA
#define LED13_pin LL_GPIO_PIN_0
#define LED13_port GPIOB
#define LED12_pin LL_GPIO_PIN_1
#define LED12_port GPIOB
#define LED11_pin LL_GPIO_PIN_8
#define LED11_port GPIOA
#define LED10_pin LL_GPIO_PIN_9
#define LED10_port GPIOA
#define LED9_pin LL_GPIO_PIN_10
#define LED9_port GPIOA
#define LED8_pin LL_GPIO_PIN_11
#define LED8_port GPIOA
#define LED7_pin LL_GPIO_PIN_12
#define LED7_port GPIOA
#define LED6_pin LL_GPIO_PIN_15
#define LED6_port GPIOA
#define LED5_pin LL_GPIO_PIN_3
#define LED5_port GPIOB
#define LED4_pin LL_GPIO_PIN_4
#define LED4_port GPIOB
#define LED3_pin LL_GPIO_PIN_5
#define LED3_port GPIOB
#define LED2_pin LL_GPIO_PIN_6
#define LED2_port GPIOB
#define LED1_pin LL_GPIO_PIN_7
#define LED1_port GPIOB

#define BOARD_NUM_LEDS 20

typedef struct {
    GPIO_TypeDef* port;
    uint32_t pin;
} gpio_t;

static gpio_t board_leds[BOARD_NUM_LEDS] = {
    { LED1_port, LED1_pin },   { LED2_port, LED2_pin },   { LED3_port, LED3_pin },
    { LED4_port, LED4_pin },   { LED5_port, LED5_pin },   { LED6_port, LED6_pin },
    { LED7_port, LED7_pin },   { LED8_port, LED8_pin },   { LED9_port, LED9_pin },
    { LED10_port, LED10_pin }, { LED11_port, LED11_pin }, { LED12_port, LED12_pin },
    { LED13_port, LED13_pin }, { LED14_port, LED14_pin }, { LED15_port, LED15_pin },
    { LED16_port, LED16_pin }, { LED17_port, LED17_pin }, { LED18_port, LED18_pin },
    { LED19_port, LED19_pin }, { LED20_port, LED20_pin }
};

static void clocks_init(void) {
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
    LL_RCC_MSI_Enable();

    while (LL_RCC_MSI_IsReady() != 1) {
    }
    LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_5);
    LL_RCC_MSI_SetCalibTrimming(0);
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_MSI);

    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_MSI) {
    }

    LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
    LL_SetSystemCoreClock(2097000);

    assert(HAL_InitTick(TICK_INT_PRIORITY) == HAL_OK);
}

static void gpio_init(void) {
    LL_GPIO_InitTypeDef init = { 0 };

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);

    LL_GPIO_ResetOutputPin(LED1_port, LED1_pin);
    LL_GPIO_ResetOutputPin(LED2_port, LED2_pin);
    LL_GPIO_ResetOutputPin(LED3_port, LED3_pin);
    LL_GPIO_ResetOutputPin(LED4_port, LED4_pin);
    LL_GPIO_ResetOutputPin(LED5_port, LED5_pin);
    LL_GPIO_ResetOutputPin(LED6_port, LED6_pin);
    LL_GPIO_ResetOutputPin(LED7_port, LED7_pin);
    LL_GPIO_ResetOutputPin(LED8_port, LED8_pin);
    LL_GPIO_ResetOutputPin(LED9_port, LED9_pin);
    LL_GPIO_ResetOutputPin(LED10_port, LED10_pin);
    LL_GPIO_ResetOutputPin(LED11_port, LED11_pin);
    LL_GPIO_ResetOutputPin(LED12_port, LED12_pin);
    LL_GPIO_ResetOutputPin(LED13_port, LED13_pin);
    LL_GPIO_ResetOutputPin(LED14_port, LED14_pin);
    LL_GPIO_ResetOutputPin(LED15_port, LED15_pin);
    LL_GPIO_ResetOutputPin(LED16_port, LED16_pin);
    LL_GPIO_ResetOutputPin(LED17_port, LED17_pin);
    LL_GPIO_ResetOutputPin(LED18_port, LED18_pin);
    LL_GPIO_ResetOutputPin(LED19_port, LED19_pin);
    LL_GPIO_ResetOutputPin(LED20_port, LED20_pin);

    init.Mode = LL_GPIO_MODE_ANALOG;
    init.Pull = LL_GPIO_PULL_NO;

    init.Pin = LL_GPIO_PIN_14;
    LL_GPIO_Init(GPIOC, &init);
    init.Pin = LL_GPIO_PIN_15;
    LL_GPIO_Init(GPIOC, &init);

    init.Mode = LL_GPIO_MODE_INPUT;
    init.Pin = WAKEUP_pin;
    LL_GPIO_Init(WAKEUP_port, &init);

    init.Mode = LL_GPIO_MODE_OUTPUT;
    init.Speed = LL_GPIO_SPEED_FREQ_LOW;
    init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;

    init.Pin = LED1_pin;
    LL_GPIO_Init(LED1_port, &init);

    init.Pin = LED2_pin;
    LL_GPIO_Init(LED2_port, &init);

    init.Pin = LED3_pin;
    LL_GPIO_Init(LED3_port, &init);

    init.Pin = LED4_pin;
    LL_GPIO_Init(LED4_port, &init);

    init.Pin = LED5_pin;
    LL_GPIO_Init(LED5_port, &init);

    init.Pin = LED6_pin;
    LL_GPIO_Init(LED6_port, &init);

    init.Pin = LED7_pin;
    LL_GPIO_Init(LED7_port, &init);

    init.Pin = LED8_pin;
    LL_GPIO_Init(LED8_port, &init);

    init.Pin = LED9_pin;
    LL_GPIO_Init(LED9_port, &init);

    init.Pin = LED10_pin;
    LL_GPIO_Init(LED10_port, &init);

    init.Pin = LED11_pin;
    LL_GPIO_Init(LED11_port, &init);

    init.Pin = LED12_pin;
    LL_GPIO_Init(LED12_port, &init);

    init.Pin = LED13_pin;
    LL_GPIO_Init(LED13_port, &init);

    init.Pin = LED14_pin;
    LL_GPIO_Init(LED14_port, &init);

    init.Pin = LED15_pin;
    LL_GPIO_Init(LED15_port, &init);

    init.Pin = LED16_pin;
    LL_GPIO_Init(LED16_port, &init);

    init.Pin = LED17_pin;
    LL_GPIO_Init(LED17_port, &init);

    init.Pin = LED18_pin;
    LL_GPIO_Init(LED18_port, &init);

    init.Pin = LED19_pin;
    LL_GPIO_Init(LED19_port, &init);

    init.Pin = LED20_pin;
    LL_GPIO_Init(LED20_port, &init);
}

static void nvic_init(void) {
    LL_EXTI_InitTypeDef init = { 0 };

    __HAL_RCC_SYSCFG_CLK_ENABLE();

    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE0);
    LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_ALL_0_31);
    init.Line_0_31 = LL_EXTI_LINE_0;
    init.LineCommand = ENABLE;
    init.Mode = LL_EXTI_MODE_IT;
    init.Trigger = LL_EXTI_TRIGGER_FALLING;
    LL_EXTI_Init(&init);
    HAL_NVIC_SetPriority(EXTI0_1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
}

void board_set_leds(uint32_t mask) {
    for (int i = 0; i < BOARD_NUM_LEDS; i++) {
        if (mask & 1) {
            LL_GPIO_SetOutputPin(board_leds[i].port, board_leds[i].pin);
        } else {
            LL_GPIO_ResetOutputPin(board_leds[i].port, board_leds[i].pin);
        }
        mask >>= 1;
    }
}

bool board_get_wakeup_pin_state(void) {
    return LL_GPIO_IsInputPinSet(WAKEUP_port, WAKEUP_pin);
}

void board_power_down(void) {
    LL_PWR_DisableWakeUpPin(LL_PWR_WAKEUP_PIN1);
    LL_PWR_ClearFlag_WU();
    LL_PWR_EnableWakeUpPin(LL_PWR_WAKEUP_PIN1);
    LL_PWR_SetPowerMode(LL_PWR_MODE_STANDBY);

    // time for sleep
    LL_LPM_EnableDeepSleep();
    __WFI();
}

void board_init(void) {
    clocks_init();
    gpio_init();
    nvic_init();

    // handle wakeup
    if (LL_PWR_IsActiveFlag_SB()) {
        LL_PWR_ClearFlag_SB();
        LL_PWR_DisableWakeUpPin(LL_PWR_WAKEUP_PIN1);

        _board_on_wakeup();
    } else {
        _board_on_first_boot();
    }
}

__attribute__((weak)) void _board_on_wakeup(void) {
}

__attribute__((weak)) void _board_on_first_boot(void) {
}
