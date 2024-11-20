/*
 * biquad_filter.h
 *
 *  Created on: Sep 23, 2024
 *      Author: PC
 */

#ifndef DSP_INC_BIQUAD_FILTER_H_
#define DSP_INC_BIQUAD_FILTER_H_

#include <stdint.h>
#include "arm_math.h"

#define MAX_ORDER 8

enum BiquadFilterType
{
	LOWPASS = 0,
	BANDPASS = 1,
	HIGHPASS = 2,
	ALLPASS = 3,
	NOTCH = 4
};

struct BiquadFilter
{
	enum BiquadFilterType type;
	float32_t coeffs[5];
	float32_t Fc;
	float32_t Fs;
	float32_t Q;
	uint8_t order;
	float32_t history_buffer[2 * (MAX_ORDER + 1)];
};

/*
 * Initialized the BiquadFilter struct with the coefficients
 * that will produce a filter with the given parameters
 * Fc - Corner frequency
 * Fs - Sampling frequency
 */
void biquad_filter_init(struct BiquadFilter* bf,
						float32_t Fc,
						float32_t Fs,
						float32_t Q,
						uint8_t order,
						enum BiquadFilterType type);

void biquad_filter_process(struct BiquadFilter* bf,
						   float32_t* src,
						   float32_t* dst,
						   int32_t block_size);

int8_t biquad_filter_get_param_string(struct BiquadFilter* bf,
									  uint8_t index,
							 	 	  char* dst);

uint8_t biquad_filter_get_num_params(struct BiquadFilter* bf);
#endif /* DSP_INC_BIQUAD_FILTER_H_ */
