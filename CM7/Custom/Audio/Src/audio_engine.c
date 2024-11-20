/*
 * audio_engine.c
 *
 *  Created on: Nov 19, 2024
 *      Author: PC
 */

#include "audio_engine.h"
#include "audio_defs.h"

static struct AudioStream audio_streams[NUM_AUDIO_STREAMS];

int8_t audio_engine_init()
{
	for (uint8_t i = 0; i < NUM_AUDIO_STREAMS; i++)
	{
		audio_stream_init(&audio_streams[i]);
	}
}

int8_t audio_engine_process(float32_t* src, float32_t* dst, int32_t block_size)
{
	for (uint8_t i = 0; i < NUM_AUDIO_STREAMS; i++)
	{
		audio_stream_process(&audio_streams[i], &src[i * block_size], &dst[i * block_size], block_size);
	}
}

int8_t audio_engine_insblk(uint8_t stream_id, struct Block* block)
{
	if (stream_id >= NUM_AUDIO_STREAMS)
		return -EOOB;

	audio_stream_insblk(&audio_streams[stream_id], block);
	return EOK;
}

int8_t audio_engine_rmblk(uint8_t stream_id, uint32_t index)
{
	if (stream_id >= NUM_AUDIO_STREAMS)
		return -EOOB;

	audio_stream_rmblk(&audio_streams[stream_id], index);
	return EOK;
}

struct AudioStream* audio_engine_get_stream(uint8_t stream_id)
{
	if (stream_id >= NUM_AUDIO_STREAMS)
		return NULL;

	return &audio_streams[stream_id];
}
