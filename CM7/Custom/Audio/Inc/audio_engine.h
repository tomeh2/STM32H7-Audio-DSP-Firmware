/*
 * audio_engine.h
 *
 *  Created on: Aug 29, 2024
 *      Author: PC
 */

#ifndef AUDIO_INC_AUDIO_ENGINE_H_
#define AUDIO_INC_AUDIO_ENGINE_H_

#include "channel.h"
#include "arm_math.h"

void audio_engine_init();
void audio_engine_process(float32_t* buf, int32_t block_size);
void audio_engine_insblk(uint8_t ch_id, struct Block* block);

#endif /* AUDIO_INC_AUDIO_ENGINE_H_ */
