/*
 * audio_engine.c
 *
 *  Created on: Aug 29, 2024
 *      Author: PC
 */

#include <audio_stream.h>
#include "block_list.h"
#include "audio_defs.h"
#include "arm_math.h"
#include "console.h"
#include "linked_list.h"

#define NUM_CHANNELS 2

void audio_stream_init(struct AudioStream* stream)
{
	if (!stream)
		return;
}

void audio_stream_process(struct AudioStream* stream, float32_t* src, float32_t* dst, int32_t block_size)
{
	float32_t* temp = src;

	if (!stream->processing_chain.head)
	{
		for (size_t i = 0; i < block_size; i++)
			dst[i] = src[i];
		return;
	}

	struct LinkedListElement* curr = stream->processing_chain.head;
	while (curr)
	{
		struct Block* curr_blk = curr->element;
		curr_blk->process(curr_blk->dsp_struct_ptr, temp, dst, block_size);
		curr = curr->next;
		temp = dst;
	}
}

void audio_stream_insblk(struct AudioStream* stream, struct Block* block)
{
	if (!block)
	{
		console_printf("[Audio Stream] Tried to insert a NULL block");
		return;
	}

	linkedlist_insert(&stream->processing_chain, block, 100);
}

void audio_stream_rmblk(struct AudioStream* stream, uint32_t index)
{
	linkedlist_remove(&stream->processing_chain, index);
}
