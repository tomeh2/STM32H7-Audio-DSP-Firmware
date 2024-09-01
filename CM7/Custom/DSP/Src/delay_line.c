/*
 * delay_line.c
 *
 *  Created on: Jul 30, 2024
 *      Author: PC
 */

#include "delay_line.h"
#include "block.h"
#include "audio_defs.h"

inline void __cbuf_write(float32_t* src, float32_t* cbuf, int32_t cbuf_head, int32_t cbuf_size, int32_t block_size)
{

}

inline void __cbuf_read(float32_t* dst, float32_t* cbuf, int32_t cbuf_head, int32_t cbuf_size, int32_t block_size)
{

}

int8_t delayline_init(struct DelayLine* delay_line,
					  uint8_t num_taps,
					  int32_t max_delay,
					  int32_t block_size)
{
	if (!delay_line)
		return -EINVAL;

	if (num_taps > MAX_TAPS)
		return -EINVAL;

	if (max_delay < 0 || max_delay > MAX_BUF_SIZE)
		return -EINVAL;

	if (block_size < 0 || block_size > MAX_BUF_SIZE)
		return -EINVAL;

	delay_line->num_taps = num_taps;
	delay_line->max_delay = max_delay;
	delay_line->buf_size = max_delay > block_size ? max_delay : max_delay + block_size;
	delay_line->head_index = 0;
	delay_line->fb_coeff = 0.f;
	delay_line->buffer = malloc(delay_line->buf_size * sizeof(float32_t));

	if (!delay_line->buffer)
	{
		return -ENOMEM;
	}

	memset(delay_line->buffer, 0, sizeof(float32_t) * delay_line->buf_size);
	memset(delay_line->coeffs, 0, sizeof(float32_t) * MAX_TAPS);
	memset(delay_line->taps, 0, sizeof(int32_t) * MAX_TAPS);

	return EOK;
}

int8_t delayline_destroy(struct DelayLine* delay_line)
{
	free(delay_line->buffer);
	free(delay_line);
}

int8_t delayline_set_tap_delay(struct DelayLine* delay_line, uint8_t tap_index, int32_t tap_delay)
{
	if (tap_delay > delay_line->max_delay || tap_delay < 0)
		return -EINVAL;

	if (tap_index >= delay_line->num_taps)
		return -EINVAL;

	delay_line->taps[tap_index] = tap_delay;
	return EOK;
}

int8_t delayline_set_tap_volume(struct DelayLine* delay_line, uint8_t tap_index, float tap_volume)
{
	if (tap_index >= delay_line->num_taps)
		return -EINVAL;

	if (tap_volume > 1.f || tap_volume < 0.f)
		return -EINVAL;

	delay_line->coeffs[tap_index] = tap_volume;
	return EOK;
}

int8_t delayline_set_fb_volume(struct DelayLine* delay_line, float32_t fb_coeff)
{
	if (fb_coeff > 1.f || fb_coeff < 0.f)
		return -EINVAL;

	delay_line->fb_coeff = fb_coeff;
	return EOK;
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


	for (int32_t i = 0; i < block_size; i++)
	{
		delay_line->buffer[delay_line->head_index++] = buf[i] + delay_line->buffer[fb_index++] * delay_line->fb_coeff;
		buf[i] = 0.f;

		if (delay_line->head_index == delay_line->buf_size)
			delay_line->head_index = 0;
		if (fb_index == delay_line->buf_size)
			fb_index = 0;
	}

	for (uint8_t j = 0; j < delay_line->num_taps; j++)
	{
		int32_t tap_index = delay_line->head_index - block_size - delay_line->taps[j];
		if (tap_index < 0)
			tap_index += delay_line->buf_size;

		for (int32_t i = 0; i < block_size; i++)
		{
			buf[i] += delay_line->buffer[tap_index++] * delay_line->coeffs[j];

			if (tap_index == delay_line->buf_size)
				tap_index = 0;
		}
	}

	return EOK;
}
