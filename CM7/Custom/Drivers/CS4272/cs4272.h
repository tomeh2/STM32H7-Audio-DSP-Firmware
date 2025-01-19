/*
 * cs4272.h
 *
 *  Created on: Aug 18, 2024
 *      Author: PC
 */

#ifndef DRIVERS_CS4272_CS4272_H_
#define DRIVERS_CS4272_CS4272_H_

#include "audio_driver.h"
#include "stm32h7xx_hal.h"

struct CS4272_PrivateData
{
	I2C_HandleTypeDef* i2c_hndl;
	I2S_HandleTypeDef* i2s_hndl;
};

extern struct AudioDriverOps cs4272_ops;

#endif /* DRIVERS_CS4272_CS4272_H_ */
