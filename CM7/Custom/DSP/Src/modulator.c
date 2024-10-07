/*
 * modulator.c
 *
 *  Created on: Aug 14, 2024
 *      Author: PC
 */

#include "modulator.h"
#include "audio_defs.h"

#include <stdlib.h>

int8_t modulator_init(struct Modulator* modulator)
{
	modulator->phase = 0.f;
	modulator->params = malloc(2 * sizeof(struct Parameter));
	parameter_init(&modulator->params[0], 0, "Frequency", PARAM_TYPE_FREQ, 0.f, 20000.f, 0.f);
	parameter_init(&modulator->params[1], 1, "Modulation Index", PARAM_TYPE_COEFF, 0.f, 1.f, 0.f);
	modulator->num_params = 2;

	return EOK;
}

int8_t modulator_destroy(struct Modulator* modulator)
{
	free(modulator->params);
	free(modulator);
	return EOK;
}

int8_t modulator_set_param(struct Modulator* modulator, uint32_t index, float32_t value)
{
	if (!modulator)
		return -EINVAL;

	if (index > modulator->num_params)
		return -EOOB;

	return parameter_set(&modulator->params[index], value);
}

char* modulator_get_param_str(struct Modulator* modulator, uint32_t index)
{
	if (!modulator)
		return -EINVAL;

	if (index > modulator->num_params)
		return -EOOB;

	return parameter_tostr(&modulator->params[index]);
}

uint8_t modulator_get_num_params(struct Modulator* modulator)
{
	return modulator->num_params;
}

int8_t modulator_process(struct Modulator* modulator, float32_t* buf, int32_t block_size)
{
	float32_t period_max = 6.2832;
	float32_t freq = modulator->params[0].value;
	float32_t mod_index = modulator->params[1].value;
	for (int32_t i = 0; i < block_size; i++)
	{
		buf[i] *= arm_sin_f32(modulator->phase) * mod_index;

		modulator->phase += 2.f * 3.1416f * freq / (float32_t) SAMPLE_RATE;
		if (modulator->phase >= period_max)
			modulator->phase -= period_max;
	}
	return EOK;
}
