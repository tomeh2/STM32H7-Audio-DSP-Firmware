#ifndef __INTERNAL_PERIPHERAL_DRIVER_H_
#define __INTERNAL_PERIPHERAL_DRIVER_H_

#include "interface.h"
#include "stm32h7xx_hal.h"

struct IntPerDrvPrivateData
{
	DAC_HandleTypeDef* hdac;
	TIM_HandleTypeDef* htim;
};

extern struct InterfaceOperations int_per_drv_ops;

#endif
