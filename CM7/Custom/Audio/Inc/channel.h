/*
 * channel.h
 *
 *  Created on: Aug 7, 2024
 *      Author: PC
 */

#ifndef AUDIO_INC_CHANNEL_H_
#define AUDIO_INC_CHANNEL_H_

#include <stdint.h>
#include <stddef.h>

#include "block.h"

struct Channel
{
	uint8_t channel_id;
	struct Block* head;
};

void channel_init(struct Channel* ch, uint8_t id);
void channel_process(struct Channel* ch, float* buf, size_t block_size);
void channel_insert_block(struct Channel* ch, struct Block* block, uint8_t pos);
void channel_remove_block(struct Channel* ch, uint8_t pos);

#endif /* AUDIO_INC_CHANNEL_H_ */
