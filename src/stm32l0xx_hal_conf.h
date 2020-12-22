#pragma once

#define USE_FULL_ASSERT 1

#define HAL_MODULE_ENABLED 1
#define HAL_CORTEX_MODULE_ENABLED 1

#include "stm32_assert.h"

#include <stm32l0xx_hal_cortex.h>
#include <stm32l0xx_hal_def.h>
#include <stm32l0xx_hal_dma.h>
#include <stm32l0xx_hal_flash.h>
#include <stm32l0xx_hal_rcc.h>

#define TICK_INT_PRIORITY 0
