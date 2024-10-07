/*
 * delay_line.c
 *
 *  Created on: Jul 30, 2024
 *      Author: PC
 */

#include "delay_line.h"
#include "block.h"
#include "audio_defs.h"

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
	delay_line->tap_delay_base = 0;
	delay_line->tap_coeff_base = num_taps;
	delay_line->fb_coeff_base = 2 * num_taps;
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
	delay_line->params = malloc((delay_line->num_params) * sizeof(struct Parameter));
	for (uint8_t i = 0; i < num_taps; i++)
	{
		// Tap delays
		parameter_init(&delay_line->params[i], i, "Tap Delay", PARAM_TYPE_DELAY, 0.f, (float32_t) max_delay, 0.f);
		parameter_init(&delay_line->params[i + num_taps], i + num_taps, "Tap Coeff", PARAM_TYPE_COEFF, 0.f, 1.f, 0.f);
	}
	parameter_init(&delay_line->params[2 * num_taps], 2 * num_taps, "Fdb Coeff", PARAM_TYPE_COEFF, 0.f, 1.f, 0.f);

	memset(delay_line->buffer, 0, sizeof(float32_t) * delay_line->buf_size);

	return EOK;
}

int8_t delayline_destroy(struct DelayLine* delay_line)
{
	free(delay_line->params);
	free(delay_line->buffer);
	free(delay_line);
}

int8_t delayline_set_param(struct DelayLine* delay_line, uint32_t index, float32_t value)
{
	if (index >= delay_line->num_params)
		return -EOOB;

	return parameter_set(&delay_line->params[index], value);
}

char* delayline_get_param_str(struct DelayLine* delay_line, uint32_t index)
{
	if (index >= delay_line->num_params)
		return NULL;

	return parameter_tostr(&delay_line->params[index]);
}

uint8_t delayline_get_num_params(struct DelayLine* delay_line)
{
	return delay_line->num_params;
}

int8_t delayline_process(struct DelayLine* delay_line, float32_t* buf, int32_t block_size)
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

	float32_t fb_coeff = delay_line->params[delay_line->fb_coeff_base].value;
	for (int32_t i = 0; i < block_size; i++)
	{
		delay_line->buffer[delay_line->head_index++] = buf[i] + delay_line->buffer[fb_index++] * fb_coeff;
		buf[i] = 0.f;

		if (delay_line->head_index == delay_line->buf_size)
			delay_line->head_index = 0;
		if (fb_index == delay_line->buf_size)
			fb_index = 0;
	}

	for (uint8_t j = 0; j < delay_line->num_taps; j++)
	{
		int32_t tap_delay_value = (int32_t) delay_line->params[j].value;
		float32_t tap_delay_coeff = delay_line->params[delay_line->tap_coeff_base + j].value;
		int32_t tap_index = delay_line->head_index - block_size - tap_delay_value;
		if (tap_index < 0)
			tap_index += delay_line->buf_size;

		for (int32_t i = 0; i < block_size; i++)
		{
			buf[i] += delay_line->buffer[tap_index++] * tap_delay_coeff;

			if (tap_index == delay_line->buf_size)
				tap_index = 0;
		}
	}

	return EOK;
}
