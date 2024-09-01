/*
 * modulator.c
 *
 *  Created on: Aug 14, 2024
 *      Author: PC
 */

#include "modulator.h"
#include "audio_defs.h"

int8_t modulator_init(struct Modulator* modulator)
{
	modulator->phase = 0.f;
	modulator->frequency = 500.f;
	modulator->modulation_strength = 0.5f;

	return EOK;
}

int8_t modulator_destroy(struct Modulator* modulator)
{
	free(modulator);
	return EOK;
}

int8_t modulator_process(struct Modulator* modulator, float32_t* buf, int32_t block_size)
{
	float32_t period_max = 6.2832;
	for (int32_t i = 0; i < block_size; i++)
	{
		buf[i] *= arm_sin_f32(modulator->phase) * modulator->modulation_strength;

		modulator->phase += 2.f * 3.1416f * modulator->frequency / (float32_t) SAMPLE_RATE;
		if (modulator->phase >= period_max)
			modulator->phase -= period_max;
	}
	return EOK;
}
