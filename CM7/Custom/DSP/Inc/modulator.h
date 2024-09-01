/*
 * modulator.h
 *
 *  Created on: Aug 14, 2024
 *      Author: PC
 */

#ifndef DSP_INC_MODULATOR_H_
#define DSP_INC_MODULATOR_H_

#include "arm_math.h"

struct Modulator
{
	float32_t phase;
	float32_t frequency;
	float32_t modulation_strength;
};

int8_t modulator_init(struct Modulator* modulator);
int8_t modulator_destroy(struct Modulator* modulator);
int8_t modulator_process(struct Modulator* modulator, float32_t* buf, int32_t block_size);

#endif /* DSP_INC_MODULATOR_H_ */
