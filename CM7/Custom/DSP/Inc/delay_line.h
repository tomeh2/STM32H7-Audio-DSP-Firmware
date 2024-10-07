/*
 * delay_line.h
 *
 *  Created on: Jul 30, 2024
 *      Author: PC
 */

#ifndef DSP_INC_DELAY_LINE_H_
#define DSP_INC_DELAY_LINE_H_

#define MAX_BUF_SIZE 524288		// 512 KSamples

#include "block.h"
#include "delay_line.h"
#include "arm_math.h"
#include "parameter.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct DelayLine
{
	struct Parameter* params;
	uint8_t num_taps;
	uint8_t num_params;
	uint8_t tap_delay_base;
	uint8_t tap_coeff_base;
	uint8_t fb_coeff_base;
	int32_t buf_size;
	int32_t max_delay;
	float32_t* buffer;
	int32_t head_index;
};

extern int8_t delayline_init(struct DelayLine* delay_line,
							 uint8_t num_taps,
							 int32_t max_delay,
							 int32_t block_size);
int8_t delayline_destroy(struct DelayLine* delay_line);
int8_t delayline_process(struct DelayLine* delay_line, float32_t* buf, int32_t block_size);
int8_t delayline_set_param(struct DelayLine* delay_line, uint32_t index, float32_t value);
char* delayline_get_param_str(struct DelayLine* delay_line, uint32_t index);
uint8_t delayline_get_num_params(struct DelayLine* delay_line);

#endif /* DSP_INC_DELAY_LINE_H_ */
