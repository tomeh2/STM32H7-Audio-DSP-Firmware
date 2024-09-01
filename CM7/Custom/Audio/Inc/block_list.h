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

extern int8_t blocklist_init();
extern int8_t blocklist_insert(void* dsp_struct_ptr, char* name, void (*process)(), uint8_t type);
extern struct Block* blocklist_get_by_name(char* name);

#endif /* AUDIO_INC_BLOCK_LIST_H_ */
