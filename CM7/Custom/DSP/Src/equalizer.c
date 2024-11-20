/*
 * equalizer.c
 *
 *  Created on: Nov 20, 2024
 *      Author: PC
 */

#include "equalizer.h"
#include "audio_defs.h"
#include "biquad_filter.h"

void equalizer_init(struct Equalizer* eq,
					uint32_t sample_rate)
{
	float32_t freq_temp = 31.f;
	for (uint8_t i = 0; i < NUM_BANDS; i++)
	{
		biquad_filter_init(&eq->filters[i],
						   freq_temp,
						   sample_rate,
						   1.4f,
						   2,
						   BANDPASS);
		eq->gain[i] = 1.f;
		eq->center_freq[i] = freq_temp;
		freq_temp *= 2.f;
	}
	eq->gain[5] = 3.f;
	eq->gain[7] = 0.f;
}

float32_t temp_accumulator[128];
void equalizer_process(struct Equalizer* eq,
					   float32_t* src,
					   float32_t* dst,
					   int32_t block_size)
{
	for (size_t j = 0; j < block_size; j++)
	{
		dst[j] = 0.f;
	}

	for (uint8_t i = 0; i < NUM_BANDS; i++)
	{
		biquad_filter_process(&eq->filters[i], src, temp_accumulator, block_size);

		for (size_t j = 0; j < block_size; j += 4)
		{
			dst[j] += temp_accumulator[j] * eq->gain[i];
			dst[j + 1] += temp_accumulator[j + 1] * eq->gain[i];
			dst[j + 2] += temp_accumulator[j + 2] * eq->gain[i];
			dst[j + 3] += temp_accumulator[j + 3] * eq->gain[i];
		}
	}
}

int8_t equalizer_get_param_string(struct Equalizer* eq,
								  uint8_t index,
							 	  char* dst)
{
	if (index >= 0 && index < NUM_BANDS)
	{
		sprintf(dst, "%u | Center Frequency = %.2f", index, eq->center_freq[index]);
		return EOK;
	}
	else if (index >= NUM_BANDS && index < NUM_BANDS * 2)
	{
		sprintf(dst, "%u | Gain = %.2f", index, eq->gain[index - NUM_BANDS]);
		return EOK;
	}
	return -EOOB;
}

uint8_t equalizer_get_num_params(struct Equalizer* eq)
{
	return 2 * NUM_BANDS;
}
