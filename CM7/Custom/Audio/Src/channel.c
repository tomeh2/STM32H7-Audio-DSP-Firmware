/*
 * channel.c
 *
 *  Created on: Aug 7, 2024
 *      Author: PC
 */

#include "channel.h"

void channel_init(struct Channel* ch, uint8_t id)
{
	ch->channel_id = id;
	ch->head = NULL;
}

void channel_process(struct Channel* ch, float* buf, size_t block_size)
{

}

// TODO: ADD INSERTS AT SPECIFIC INDEXES
void channel_insert_block(struct Channel* ch, struct Block* block, uint8_t pos)
{

}

void channel_remove_block(struct Channel* ch, uint8_t pos)
{

}
