/*
 * biquad_filter.c
 *
 *  Created on: Sep 23, 2024
 *      Author: PC
 */

#include "biquad_filter.h"
#include "math.h"

#define E 2.718281828f

void biquad_filter_init(struct BiquadFilter* bf,
						float32_t Fc,
						float32_t Fs,
						float32_t bw)
{
	float32_t w0 = 2.f * PI * Fc / Fs;
	float32_t alpha = sin(w0) * \
		sinh(log(2.f) / 2.f * bw * w0 / sin(w0));

	bf->a[0] = 1.f + alpha;
	bf->a[1] = -2.f * cos(w0);
	bf->a[2] = 1.f - alpha;

	bf->b[0] = (1.f - cos(w0)) / 2.f;
	bf->b[1] = 1.f - cos(w0);
	bf->b[2] = (1.f - cos(w0)) / 2.f;

	bf->input_history[0] = 0.f;
	bf->input_history[1] = 0.f;
	bf->input_history[2] = 0.f;

	bf->output_history[0] = 0.f;
	bf->output_history[1] = 0.f;
	bf->output_history[2] = 0.f;
}

void biquad_filter_process(struct BiquadFilter* bf,
						   float32_t* buf,
						   int32_t block_size)
{
	float32_t next_output = 0.f;
	for (int32_t i = 0; i < block_size; i++)
	{
		bf->input_history[2] = bf->input_history[1];
		bf->input_history[1] = bf->input_history[0];
		bf->input_history[0] = buf[i];

		next_output = (bf->b[0] / bf->a[0]) * bf->input_history[0] + \
			(bf->b[1] / bf->a[0]) * bf->input_history[1] + \
			(bf->b[2] / bf->a[0]) * bf->input_history[2] - \
			(bf->a[1] / bf->a[0]) * bf->output_history[0] - \
			(bf->a[2] / bf->a[0]) * bf->output_history[1];
		buf[i] = next_output;

		bf->output_history[2] = bf->output_history[1];
		bf->output_history[1] = bf->output_history[0];
		bf->output_history[0] = next_output;
	}
}
