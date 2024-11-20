/*
 * audio_engine.h
 *
 *  Created on: Nov 19, 2024
 *      Author: PC
 */

#ifndef AUDIO_INC_AUDIO_ENGINE_H_
#define AUDIO_INC_AUDIO_ENGINE_H_

#include "block.h"
#include "arm_math.h"
#include "audio_stream.h"

#define NUM_AUDIO_STREAMS 2

int8_t audio_engine_init();
int8_t audio_engine_process(float32_t* src, float32_t* dst, int32_t block_size);
int8_t audio_engine_insblk(uint8_t stream_id, struct Block* block);
int8_t audio_engine_rmblk(uint8_t stream_id, uint32_t index);
struct AudioStream* audio_engine_get_stream(uint8_t stream_id);

#endif /* AUDIO_INC_AUDIO_ENGINE_H_ */
