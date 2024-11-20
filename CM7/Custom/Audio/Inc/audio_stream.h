/*
 * audio_engine.h
 *
 *  Created on: Aug 29, 2024
 *      Author: PC
 */

#ifndef AUDIO_INC_AUDIO_STREAM_H_
#define AUDIO_INC_AUDIO_STREAM_H_

#include "channel.h"
#include "arm_math.h"
#include "linked_list.h"

struct AudioStream
{
	struct LinkedList processing_chain;
};

extern struct LinkedList processing_chain;

void audio_stream_init(struct AudioStream* stream);
void audio_stream_process(struct AudioStream* stream, float32_t* src, float32_t* dst, int32_t block_size);
void audio_stream_insblk(struct AudioStream* stream, struct Block* block);
void audio_stream_rmblk(struct AudioStream* stream, uint32_t index);

#endif /* AUDIO_INC_AUDIO_ENGINE_H_ */
