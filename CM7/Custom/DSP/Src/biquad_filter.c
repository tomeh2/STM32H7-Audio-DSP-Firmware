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

const char* BIQUAD_TYPES_STRING[] = {
		"LOWPASS",
		"BANDPASS",
		"HIGHPASS",
		"ALLPASS",
		"NOTCH"
};

arm_biquad_casd_df1_inst_f32 test;

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
						uint8_t order,
						enum BiquadFilterType type)
{
	bf->type = type;
	bf->Fc = Fc;
	bf->Fs = Fs;
	bf->Q = Q;
	bf->order = order;
	if (order > MAX_ORDER)
	{
		bf->order = MAX_ORDER;
	}

	for (uint32_t i = 0; i < 2 * (MAX_ORDER + 1); i++)
		bf->history_buffer[i] = 0.f;


	__calculate_coefficients(bf->coeffs,
							 Fc,
							 Fs,
							 Q,
							 type);
}

void biquad_filter_process(struct BiquadFilter* bf,
						   float32_t* src,
						   float32_t* dst,
						   int32_t block_size)
{
	float32_t* curr_src = src;
	float32_t b0, b1, b2, a1, a2;
	b0 = bf->coeffs[0];
	b1 = bf->coeffs[1];
	b2 = bf->coeffs[2];
	a1 = bf->coeffs[3];
	a2 = bf->coeffs[4];
	float32_t Xn2, Xn1, Xn, Yn2, Yn1;
	float32_t* hist_buf_ptr = bf->history_buffer;
	for (int32_t i = 0; i < bf->order; i++)
	{
		Xn = curr_src[0];
		Xn1 = hist_buf_ptr[0];
		Xn2 = hist_buf_ptr[1];
		Yn1 = hist_buf_ptr[2];
		Yn2 = hist_buf_ptr[3];

		for (int32_t j = 0; j < block_size; j += 4)
		{
			Xn = curr_src[j];
			Yn2 = b0 * Xn +
				  b1 * Xn1 +
				  b2 * Xn2 -
				  a1 * Yn1 -
				  a2 * Yn2;
			dst[j] = Yn2;

			Xn2 = curr_src[j + 1];
			Yn1 = b0 * Xn2 +
				  b1 * Xn +
				  b2 * Xn1 -
				  a1 * Yn2 -
				  a2 * Yn1;
			dst[j + 1] = Yn1;

			Xn1 = curr_src[j + 2];
			Yn2 = b0 * Xn1 +
				  b1 * Xn2 +
				  b2 * Xn -
				  a1 * Yn1 -
				  a2 * Yn2;
			dst[j + 2] = Yn2;

			Xn = curr_src[j + 3];
			Yn1 = b0 * Xn +
				  b1 * Xn1 +
				  b2 * Xn2 -
				  a1 * Yn2 -
				  a2 * Yn1;
			dst[j + 3] = Yn1;

			Xn2 = Xn1;
			Xn1 = Xn;
		}
		curr_src = dst;

		*hist_buf_ptr++ = Xn1;
		*hist_buf_ptr++ = Xn2;
		*hist_buf_ptr++ = Yn1;
		*hist_buf_ptr++ = Yn2;
	}
}

int8_t biquad_filter_get_param_string(struct BiquadFilter* bf,
									uint8_t index,
							 	 	char* dst)
{
	if (index == 0)
	{
		sprintf(dst, "%u | Type = %s", index, BIQUAD_TYPES_STRING[bf->type]);
		return EOK;
	}
	else if (index == 1)
	{
		sprintf(dst, "%u | Fc = %.2f Hz", index, bf->Fc);
		return EOK;
	}
	else if (index == 2)
	{
		sprintf(dst, "%u | Q = %.2f", index, bf->Q);
		return EOK;
	}
	else if (index == 3)
	{
		sprintf(dst, "%u | Fs = %.2f Hz", index, bf->Fs);
		return EOK;
	}
	else if (index == 4)
	{
		sprintf(dst, "%u | Order = %u", index, bf->order);
		return EOK;
	}
	return -EOOB;
}

uint8_t biquad_filter_get_num_params(struct BiquadFilter* bf)
{
	return 5;
}
