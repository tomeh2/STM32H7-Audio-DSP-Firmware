/*
 * block.c
 *
 *  Created on: Sep 10, 2024
 *      Author: PC
 */

#include "block.h"
#include "audio_defs.h"

int8_t block_set_param(struct Block* block, uint8_t index, float value)
{
	return block->set_param(block->dsp_struct_ptr, index, value);
}

int8_t block_get_param(struct Block* block, uint8_t index, float* dst)
{
	block->get_param(block->dsp_struct_ptr, index, dst);
}

int8_t block_get_num_params(struct Block* block)
{
	return block->get_num_params(block->dsp_struct_ptr);
}

extern inline int8_t block_get_param_string(struct Block* block, uint8_t index, char* dst)
{
	return block->get_param_string(block->dsp_struct_ptr, index, dst);
}
