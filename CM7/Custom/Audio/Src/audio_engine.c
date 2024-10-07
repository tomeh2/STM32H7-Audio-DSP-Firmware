/*
 * audio_engine.c
 *
 *  Created on: Aug 29, 2024
 *      Author: PC
 */

#include "block_list.h"
#include "audio_defs.h"
#include "arm_math.h"
#include "console.h"
#include "audio_engine.h"
#include "linked_list.h"

#define NUM_CHANNELS 2

struct LinkedList processing_chain;

void audio_engine_init()
{

}

void audio_engine_process(float32_t* buf, int32_t block_size)
{
	struct LinkedListElement* curr = processing_chain.head;
	while (curr)
	{
		struct Block* curr_blk = curr->element;
		curr_blk->process(curr_blk->dsp_struct_ptr, buf, block_size);
		curr = curr->next;
	}
}

void audio_engine_insblk(uint8_t ch_id, struct Block* block)
{
	if (ch_id >= NUM_CHANNELS)
	{
		console_println("[Audio Engine] Invalid channel ID");
		return;
	}

	if (!block)
	{
		console_println("[Audio Engine] Tried to insert a NULL block");
		return;
	}

	linkedlist_insert(&processing_chain, block, 100);
}

void audio_engine_rmblk(uint8_t ch_id, uint32_t index)
{
	if (ch_id >= NUM_CHANNELS)
	{
		console_println("[Audio Engine] Invalid channel ID");
		return;
	}

	linkedlist_remove(&processing_chain, index);
}
