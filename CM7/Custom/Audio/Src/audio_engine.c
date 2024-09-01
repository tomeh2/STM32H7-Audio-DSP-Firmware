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

#define NUM_CHANNELS 2

static struct Channel channels[NUM_CHANNELS];

void audio_engine_init()
{
	for (uint8_t i = 0; i < NUM_CHANNELS; i++)
	{
		channel_init(&channels[i], i);
	}
}

void audio_engine_process(float32_t* buf, int32_t block_size)
{
	for (uint8_t ch = 0; ch < NUM_CHANNELS; ch++)
	{
		struct Block* curr = channels[ch].head;
		while (curr)
		{
			curr->process(curr, &buf[ch * SAMPLES_PER_BLOCK], SAMPLES_PER_BLOCK);
			curr = curr->next;
		}
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

	channel_insert_block(&channels[ch_id], block, 100);
}
