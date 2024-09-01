/*
 * delay_line.h
 *
 *  Created on: Jul 30, 2024
 *      Author: PC
 */

#ifndef DSP_INC_DELAY_LINE_H_
#define DSP_INC_DELAY_LINE_H_

#define MAX_TAPS 8
#define MAX_BUF_SIZE 524288		// 512 KSamples

#include "delay_line.h"
#include "arm_math.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct DelayLine
{
	uint8_t num_taps;
	int32_t taps[MAX_TAPS];
	float32_t coeffs[MAX_TAPS];
	float32_t fb_coeff;
	int32_t buf_size;
	int32_t max_delay;
	float32_t* buffer;
	int32_t head_index;
};

extern int8_t delayline_init(struct DelayLine* delay_line,
							 uint8_t num_taps,
							 int32_t max_delay,
							 int32_t block_size);
extern int8_t delayline_destroy(struct DelayLine* delay_line);
extern int8_t delayline_process(struct DelayLine* delay_line, float32_t* buf, int32_t block_size);
extern int8_t delayline_set_tap_delay(struct DelayLine* delay_line, uint8_t tap_index, int32_t tap_delay);
extern int8_t delayline_set_tap_volume(struct DelayLine* delay_line, uint8_t tap_index, float32_t tap_volume);
extern int8_t delayline_set_fb_volume(struct DelayLine* delay_line, float32_t fb_coeff);

#endif /* DSP_INC_DELAY_LINE_H_ */
