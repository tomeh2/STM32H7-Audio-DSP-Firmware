/*
 * equalizer.h
 *
 *  Created on: Nov 20, 2024
 *      Author: PC
 */

#ifndef DSP_INC_EQUALIZER_H_
#define DSP_INC_EQUALIZER_H_

#include "biquad_filter.h"

#define NUM_BANDS 10

struct Equalizer
{
	struct BiquadFilter filters[NUM_BANDS];
	float32_t center_freq[NUM_BANDS];
	float32_t q[NUM_BANDS];
	float32_t gain[NUM_BANDS];
};

void equalizer_init(struct Equalizer* eq,
					uint32_t sample_rate);

void equalizer_process(struct Equalizer* eq,
					   float32_t* src,
				   	   float32_t* dst,
					   int32_t block_size);

int8_t equalizer_get_param_string(struct Equalizer* eq,
								  uint8_t index,
							 	  char* dst);

uint8_t equalizer_get_num_params(struct Equalizer* eq);

#endif /* DSP_INC_EQUALIZER_H_ */
