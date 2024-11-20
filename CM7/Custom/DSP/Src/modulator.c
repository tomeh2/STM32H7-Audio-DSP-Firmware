/*
 * modulator.c
 *
 *  Created on: Aug 14, 2024
 *      Author: PC
 */

#include "modulator.h"
#include "audio_defs.h"
#include "stdio.h"

#include <stdlib.h>

int8_t modulator_init(struct Modulator* modulator)
{
	modulator->phase = 0.f;
	modulator->num_params = 2;
	modulator->frequency = 0.f;
	modulator->modulation_index = 0.f;

	return EOK;
}

int8_t modulator_destroy(struct Modulator* modulator)
{
	free(modulator);
	return EOK;
}

int8_t modulator_set_param(struct Modulator* modulator, uint32_t index, float32_t value)
{
	if (index == 0)
	{
		if (value >= 0.f && value <= 20000.f)
		{
			modulator->frequency = value;
			return EOK;
		}
		return -EINVAL;
	}
	else if (index == 1)
	{
		if (value >= 0.f && value <= 100.f)
		{
			modulator->modulation_index = value;
			return EOK;
		}
		return -EINVAL;
	}
	else
	{
		return -EOOB;
	}
}

int8_t modulator_get_param(struct Modulator* modulator, uint32_t index, float32_t* dst)
{
	if (index == 0)
	{
		*dst = modulator->frequency;
		return EOK;
	}
	else if (index == 1)
	{
		*dst = modulator->modulation_index;
		return EOK;
	}
	else
	{
		return -EOOB;
	}
}

int8_t modulator_get_param_string(struct Modulator* modulator, uint32_t index, char* dst)
{
	if (index == 0)
	{
		sprintf(dst, "%u | Frequency = %.2f Hz", index, modulator->frequency);
		return EOK;
	}
	else if (index == 1)
	{
		sprintf(dst, "%u | Modulation Index = %.2f", index, modulator->modulation_index);
		return EOK;
	}
	else
	{
		return -EOOB;
	}
}

uint8_t modulator_get_num_params(struct Modulator* modulator)
{
	return modulator->num_params;
}

int8_t modulator_process(struct Modulator* modulator, float32_t* src,
 	   	   	 	 	 	 float32_t* dst, int32_t block_size)
{
	float32_t period_max = 2.f * PI;
	for (int32_t i = 0; i < block_size; i++)
	{
		dst[i] = src[i] * arm_sin_f32(modulator->phase) * modulator->modulation_index;

		modulator->phase += 2.f * 3.1416f * modulator->frequency / (float32_t) SAMPLE_RATE;
		if (modulator->phase >= period_max)
			modulator->phase -= period_max;
	}
	return EOK;
}
