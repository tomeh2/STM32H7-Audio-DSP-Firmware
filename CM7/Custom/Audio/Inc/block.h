/*
 * block.h
 *
 *  Created on: Aug 7, 2024
 *      Author: PC
 */

#ifndef AUDIO_INC_BLOCK_H_
#define AUDIO_INC_BLOCK_H_

#define BLOCK_TYPE_DELAYLINE 0
#define BLOCK_TYPE_MODULATOR 1
#define BLOCK_TYPE_UNKNOWN 255
#define BLOCK_NAME_SIZE 32

#include <stddef.h>

struct Block
{
	uint8_t type;
	char name[BLOCK_NAME_SIZE + 1];
	void (*process)(void* private_data, float* buf, size_t block_size);
	void* dsp_struct_ptr;
	struct Block* next;
};

#endif /* AUDIO_INC_BLOCK_H_ */
