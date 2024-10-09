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
	float32_t frequency;
	float32_t modulation_index;
	uint8_t num_params;
	float32_t phase;
};

int8_t modulator_init(struct Modulator* modulator);
int8_t modulator_destroy(struct Modulator* modulator);
int8_t modulator_set_param(struct Modulator* modulator, uint32_t index, float32_t value);
int8_t modulator_get_param(struct Modulator* modulator, uint32_t index, float32_t* dst);
int8_t modulator_get_param_string(struct Modulator* modulator, uint32_t index, char* dst);
uint8_t modulator_get_num_params(struct Modulator* modulator);
int8_t modulator_to_string(struct Modulator* modulator, char* dst);
int8_t modulator_process(struct Modulator* modulator, float32_t* buf, int32_t block_size);

#endif /* DSP_INC_MODULATOR_H_ */
