/*
 * block.c
 *
 *  Created on: Sep 10, 2024
 *      Author: PC
 */

#include "block.h"

int8_t block_set_param(struct Block* block, uint8_t index, float value)
{
	return block->set_param(block->dsp_struct_ptr, index, value);
}

char* block_get_param_str(struct Block* block, uint8_t index)
{
	return block->get_param_str(block->dsp_struct_ptr, index);
}

int8_t block_get_num_params(struct Block* block)
{
	return block->get_num_params(block->dsp_struct_ptr);
}
