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
	void (*process)(void* dsp_struct_ptr, float* src, float* dst, size_t block_size);
	int8_t (*set_param)(void* dsp_struct_ptr, uint8_t, float);
	int8_t (*get_param)(void* dsp_struct_ptr, uint8_t, float*);
	int8_t (*get_param_string)(void* dsp_struct_ptr, uint8_t, char*);
	uint8_t (*get_num_params)(void* dsp_struct_ptr);
};

extern inline int8_t block_set_param(struct Block* block, uint8_t index, float value);
extern inline int8_t block_get_param(struct Block* block, uint8_t index, float* dst);
extern inline int8_t block_get_param_string(struct Block* block, uint8_t index, char* dst);
extern inline int8_t block_get_num_params(struct Block* block);

#endif /* AUDIO_INC_BLOCK_H_ */
