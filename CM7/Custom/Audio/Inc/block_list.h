/*
 * block_list.h
 *
 *  Created on: Aug 9, 2024
 *      Author: PC
 */

#ifndef AUDIO_INC_BLOCK_LIST_H_
#define AUDIO_INC_BLOCK_LIST_H_

#include <stdint.h>
#include "block.h"

#define MAX_DSP_BLOCKS 16

extern struct Block block_list[MAX_DSP_BLOCKS];

int8_t blocklist_init();
int8_t blocklist_insert(void* dsp_struct_ptr,
						char* name,
						void (*process)(void*, float*, size_t),
						int8_t (*set_param)(void*, uint8_t, float),
						int8_t (*get_param)(void*, uint8_t, float*),
						int8_t (*get_param_string)(void*, uint8_t, char*),
						uint8_t (*get_num_params)(void*));
struct Block* blocklist_get_by_name(char* name);

#endif /* AUDIO_INC_BLOCK_LIST_H_ */
