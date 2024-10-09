/*
 * biquad_filter.c
 *
 *  Created on: Sep 23, 2024
 *      Author: PC
 */

#include "biquad_filter.h"
#include "math.h"
#include "audio_defs.h"

#include <stdio.h>

#define E 2.718281828f

const char TYPE_LOWPASS[] = "LOWPASS";
const char TYPE_BANDPASS[] = "BANDPASS";
const char TYPE_HIGHPASS[] = "HIGHPASS";
const char TYPE_ALLPASS[] = "ALLPASS";
const char TYPE_NOTCH[] = "NOTCH";

const char* TYPE_STRINGS[] = {TYPE_LOWPASS, TYPE_BANDPASS, TYPE_HIGHPASS, TYPE_ALLPASS, TYPE_NOTCH};

void __calculate_coefficients(float32_t* coeffs,
							  float32_t Fc,
							  float32_t Fs,
							  float32_t Q,
							  enum BiquadFilterType type)
{
	float32_t w0 = 2.f * PI * Fc / Fs;
	float32_t alpha = sin(w0) / (2.f * Q);

	float32_t a0, a1, a2, b0, b1, b2;
	switch (type)
	{
	case LOWPASS:
		a0 = 1.f + alpha;
		a1 = -2.f * cos(w0);
		a2 = 1.f - alpha;
		b0 = (1.f - cos(w0)) / 2.f;
		b1 = 1.f - cos(w0);
		b2 = (1.f - cos(w0)) / 2.f;
		break;
	case BANDPASS:
		a0 = 1.f + alpha;
		a1 = -2.f * cos(w0);
		a2 = 1.f - alpha;
		b0 = alpha;
		b1 = 0.f;
		b2 = -alpha;
		break;
	case HIGHPASS:
		a0 = 1.f + alpha;
		a1 = -2.f * cos(w0);
		a2 = 1.f - alpha;
		b0 = (1.f + cos(w0)) / 2.f;
		b1 = -(1.f + cos(w0));
		b2 = (1.f + cos(w0)) / 2.f;
		break;
	case ALLPASS:
		a0 = 1.f + alpha;
		a1 = -2.f * cos(w0);
		a2 = 1.f - alpha;
		b0 = 1.f - alpha;
		b1 = -2.f * cos(w0);
		b2 = 1.f + alpha;
		break;
	case NOTCH:
		a0 = 1.f + alpha;
		a1 = -2.f * cos(w0);
		a2 = 1.f - alpha;
		b0 = 1.f;
		b1 = -2.f * cos(w0);
		b2 = 1.f;
		break;
	}
	coeffs[0] = b0 / a0;
	coeffs[1] = b1 / a0;
	coeffs[2] = b2 / a0;
	coeffs[3] = a1 / a0;
	coeffs[4] = a2 / a0;
}

void biquad_filter_init(struct BiquadFilter* bf,
						float32_t Fc,
						float32_t Fs,
						float32_t Q,
						enum BiquadFilterType type)
{
	bf->type = type;
	bf->Fc = Fc;
	bf->Fs = Fs;
	bf->Q = Q;

	__calculate_coefficients(bf->coeffs,
							 Fc,
							 Fs,
							 Q,
							 type);

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

		next_output = bf->coeffs[0] * bf->input_history[0] +
			bf->coeffs[1] * bf->input_history[1] +
			bf->coeffs[2] * bf->input_history[2] -
			bf->coeffs[3] * bf->output_history[0] -
			bf->coeffs[4] * bf->output_history[1];
		buf[i] = next_output;

		bf->output_history[2] = bf->output_history[1];
		bf->output_history[1] = bf->output_history[0];
		bf->output_history[0] = next_output;
	}
}

int8_t biquad_filter_get_param_string(struct BiquadFilter* bf,
									uint8_t index,
							 	 	char* dst)
{
	if (index == 0)
	{
		sprintf(dst, "%u | Fc = %.2f Hz", index, bf->Fc);
		return EOK;
	}
	else if (index == 1)
	{
		sprintf(dst, "%u | Q = %.2f", index, bf->Q);
		return EOK;
	}
	else if (index == 2)
	{
		sprintf(dst, "%u | Fs = %.2f Hz", index, bf->Fs);
		return EOK;
	}
	return -EOOB;
}

void biquad_filter_to_string(struct BiquadFilter* bf,
		 	 	 	 	 	 char* dst)
{
	sprintf(dst, "0 | Type = %s\n\r1 | Fc = %.2f Hz\n\r2 | Q = %.2f\n\r3 | Fs = %.2f Hz", TYPE_STRINGS[bf->type], bf->Fc, bf->Q, bf->Fs);
}

uint8_t biquad_filter_get_num_params(struct BiquadFilter* bf)
{
	return 3;
}
