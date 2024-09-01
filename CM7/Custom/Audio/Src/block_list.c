/*
 * block_list.c
 *
 *  Created on: Aug 9, 2024
 *      Author: PC
 */

#include "block_list.h"
#include "audio_defs.h"

#include <stdlib.h>

#define STATUS_BITMAP_SIZE (MAX_DSP_BLOCKS / 8 + (MAX_DSP_BLOCKS % 8 > 0))

uint8_t blocklist_initialized = 0;
uint8_t block_status_bitmap[STATUS_BITMAP_SIZE];
struct Block block_list[MAX_DSP_BLOCKS];

int8_t blocklist_init()
{
	if (blocklist_initialized)
		return -EINVAL;

	for (uint8_t i = 0; i < STATUS_BITMAP_SIZE; i++)
	{
		block_status_bitmap[i >> 3] = 0xFF;
	}

	for (uint8_t i = 0; i < MAX_DSP_BLOCKS; i++)
	{
		block_list[i].next = NULL;
		block_list[i].dsp_struct_ptr = NULL;
		block_list[i].process = NULL;
		block_list[i].type = BLOCK_TYPE_UNKNOWN;
	}
	blocklist_initialized = 1;

	return EOK;
}

int8_t blocklist_insert(void* dsp_struct_ptr, char* name, void (*process)(void*, float*, size_t), uint8_t type)
{
	if (!blocklist_initialized)
		return -EINVAL;

	int16_t free_block_index = -1;
	uint8_t mask = 0x01;
	for (uint8_t i = 0; i < MAX_DSP_BLOCKS; i++)
	{
		if (block_status_bitmap[i >> 3] & mask)
		{
			free_block_index = i;
			block_status_bitmap[i >> 3] &= ~mask;
			break;
		}
		uint8_t top_bit = (mask >> 7) & 0x01;
		mask <<= 1;
		mask |= top_bit;
	}

	if (free_block_index == -1)
		return -EINVAL;

	uint8_t str_size = strlen(name);
	str_size = str_size > BLOCK_NAME_SIZE ? BLOCK_NAME_SIZE : str_size;
	memcpy(block_list[free_block_index].name, name, str_size);
	block_list[free_block_index].name[str_size] = '\0';
	block_list[free_block_index].dsp_struct_ptr = dsp_struct_ptr;
	block_list[free_block_index].process = process;
	block_list[free_block_index].type = type;
	return EOK;
}

struct Block* blocklist_get_by_name(char* name)
{
	for (uint8_t i = 0; i < MAX_DSP_BLOCKS; i++)
	{
		if (block_list[i].type != BLOCK_TYPE_UNKNOWN &&
			!strcmp(block_list[i].name, name))
		{
			return &block_list[i];
		}
	}
	return NULL;
}
