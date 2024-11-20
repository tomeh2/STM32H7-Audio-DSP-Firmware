/*
 * delay_line.c
 *
 *  Created on: Jul 30, 2024
 *      Author: PC
 */

#include "delay_line.h"
#include "block.h"
#include "audio_defs.h"
#include "stdio.h"

#define PARAM_TYPE_MASK 0xFFFF0000
#define PARAM_INDEX_MASK 0x0000FFFF

#define PARAM_TYPE_TAP_VOLUME 0
#define PARAM_TYPE_TAP_DELAY 1
#define PARAM_TYPE_FDBK_VOL 2

int8_t delayline_init(struct DelayLine* delay_line,
					  uint8_t num_taps,
					  int32_t max_delay,
					  int32_t block_size)
{
	if (!delay_line)
		return -EINVAL;

	if (max_delay < 0 || max_delay > MAX_BUF_SIZE)
		return -EINVAL;

	if (block_size < 0 || block_size > MAX_BUF_SIZE)
		return -EINVAL;

	delay_line->num_taps = num_taps;
	delay_line->tap_delay_index_start = 0;
	delay_line->tap_delay_index_end = num_taps - 1;
	delay_line->tap_coeff_index_start = num_taps;
	delay_line->tap_coeff_index_end = 2 * num_taps - 1;
	delay_line->tap_fbcoeff_index_start = 2 * num_taps;
	delay_line->num_params = 2 * num_taps + 1;
	delay_line->max_delay = max_delay;
	delay_line->buf_size = max_delay > block_size ? max_delay : max_delay + block_size;
	delay_line->head_index = 0;
	delay_line->buffer = malloc(delay_line->buf_size * sizeof(float32_t));

	if (!delay_line->buffer)
	{
		return -ENOMEM;
	}

	// There are num_taps * 2 + 1 parameters since the first num_taps parameters
	// correspond to tap delay indexes, then after that there are num_taps parameters
	// which correspond to tap coeffs and finally the last parameter is the feedback volume
	// Feedback coefficient

	memset(delay_line->delay_times, 0, sizeof(float32_t) * delay_line->num_params);
	memset(delay_line->delay_coeffs, 0, sizeof(float32_t) * delay_line->num_params);
	memset(delay_line->buffer, 0, sizeof(float32_t) * delay_line->buf_size);
	delay_line->feedback_coeff = 0.f;

	return EOK;
}

int8_t delayline_destroy(struct DelayLine* delay_line)
{
	free(delay_line->buffer);
	free(delay_line);
}

int8_t delayline_set_param(struct DelayLine* delay_line, uint32_t index, float32_t value)
{
	if (index >= delay_line->tap_delay_index_start && index <= delay_line->tap_delay_index_end)
	{
		if (value >= 0.f && value <= (float32_t) delay_line->max_delay)
		{
			delay_line->delay_times[index] = value;
			return EOK;
		}
		return -EINVAL;
	}
	else if (index >= delay_line->tap_coeff_index_start && index <= delay_line->tap_coeff_index_end)
	{
		if (value >= 0.f && value <= 1.f)
		{
			delay_line->delay_coeffs[delay_line->tap_coeff_index_start - index] = value;
			return EOK;
		}
		return -EINVAL;
	}
	else if (index == delay_line->tap_fbcoeff_index_start)
	{
		if (value >= 0.f && value <= 1.f)
		{
			delay_line->feedback_coeff = value;
			return EOK;
		}
		return -EINVAL;
	}
	else
	{
		return -EOOB;
	}
}

int8_t delayline_get_param(struct DelayLine* delay_line, uint32_t index, float32_t* dst)
{
	if (index >= delay_line->tap_delay_index_start && index <= delay_line->tap_delay_index_end)
	{
		*dst = delay_line->delay_times[index];
		return EOK;
	}
	else if (index >= delay_line->tap_coeff_index_start && index <= delay_line->tap_coeff_index_end)
	{
		*dst = delay_line->delay_coeffs[delay_line->tap_coeff_index_start - index];
		return EOK;
	}
	else if (index == delay_line->tap_fbcoeff_index_start)
	{
		*dst = delay_line->feedback_coeff;
		return EOK;
	}
	else
	{
		return -EOOB;
	}
}

int8_t delayline_get_param_string(struct DelayLine* delay_line, uint32_t index, char* dst)
{
	if (index >= delay_line->tap_delay_index_start && index <= delay_line->tap_delay_index_end)
	{
		sprintf(dst, "%u | Tap Delay: %.2f Samples", index, delay_line->delay_times[index]);
		return EOK;
	}
	else if (index >= delay_line->tap_coeff_index_start && index <= delay_line->tap_coeff_index_end)
	{
		sprintf(dst, "%u | Tap Coeff: %.2f", index, delay_line->delay_coeffs[delay_line->tap_coeff_index_start - index]);
		return EOK;
	}
	else if (index == delay_line->tap_fbcoeff_index_start)
	{
		sprintf(dst, "%u | FB Coeff: %.2f", index, delay_line->feedback_coeff);
		return EOK;
	}
	else
	{
		return -EOOB;
	}
}

uint8_t delayline_get_num_params(struct DelayLine* delay_line)
{
	return delay_line->num_params;
}

int8_t delayline_process(struct DelayLine* delay_line, float32_t* src,
		 	 	 	 	 float32_t* dst, int32_t block_size)
{
	int32_t fb_index = -1;
	if (delay_line->max_delay < delay_line->buf_size)
	{
		fb_index = delay_line->head_index - delay_line->max_delay;
		if (fb_index < 0)
			fb_index += delay_line->buf_size;
	}
	else
		fb_index = delay_line->head_index;

	float32_t fb_coeff = delay_line->feedback_coeff;
	for (int32_t i = 0; i < block_size; i++)
	{
		delay_line->buffer[delay_line->head_index++] = src[i] + delay_line->buffer[fb_index++] * fb_coeff;
		dst[i] = 0.f;

		if (delay_line->head_index == delay_line->buf_size)
			delay_line->head_index = 0;
		if (fb_index == delay_line->buf_size)
			fb_index = 0;
	}

	for (uint8_t j = 0; j < delay_line->num_taps; j++)
	{
		int32_t tap_delay_value = (int32_t) delay_line->delay_times[j];
		float32_t tap_delay_coeff = delay_line->delay_coeffs[j];
		int32_t tap_index = delay_line->head_index - block_size - tap_delay_value;
		if (tap_index < 0)
			tap_index += delay_line->buf_size;

		for (int32_t i = 0; i < block_size; i++)
		{
			dst[i] += delay_line->buffer[tap_index++] * tap_delay_coeff;

			if (tap_index == delay_line->buf_size)
				tap_index = 0;
		}
	}
	return EOK;
}







