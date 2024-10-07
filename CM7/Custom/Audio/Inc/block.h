/*
 * block.h
 *
 *  Created on: Aug 7, 2024
 *      Author: PC
 */

#ifndef AUDIO_INC_BLOCK_H_
#define AUDIO_INC_BLOCK_H_

#define BLOCK_NAME_SIZE 32

#include <stddef.h>
#include <stdint.h>

struct Block
{
	void* dsp_struct_ptr;
	char name[BLOCK_NAME_SIZE + 1];
	void (*process)(void* dsp_struct_ptr, float* buf, size_t block_size);
	int8_t (*set_param)(void* dsp_struct_ptr, uint8_t, float);
	char* (*get_param_str)(void* dsp_struct_ptr, uint8_t);
	uint8_t (*get_num_params)(void* dsp_struct_ptr);
};

inline int8_t block_set_param(struct Block* block, uint8_t index, float value);
inline char* block_get_param_str(struct Block* block, uint8_t index);
inline int8_t block_get_num_params(struct Block* block);

#endif /* AUDIO_INC_BLOCK_H_ */
