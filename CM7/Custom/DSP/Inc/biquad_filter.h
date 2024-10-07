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

struct BiquadFilter
{
	// a0 and b0 are implied to be 1
	float32_t a[3];
	float32_t b[3];
	float32_t input_history[3];
	float32_t output_history[3];
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
						float32_t bw);

void biquad_filter_process(struct BiquadFilter* bf,
						   float32_t* buf,
						   int32_t block_size);

#endif /* DSP_INC_BIQUAD_FILTER_H_ */
