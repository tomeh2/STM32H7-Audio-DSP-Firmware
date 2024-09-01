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
	struct Block* curr = ch->head;
	while (curr)
	{
		curr->process(curr->dsp_struct_ptr, buf, block_size);
		curr = curr->next;
	}
}

// TODO: ADD INSERTS AT SPECIFIC INDEXES
void channel_insert_block(struct Channel* ch, struct Block* block, uint8_t pos)
{
	if (!ch->head)
	{
		ch->head = block;
		return;
	}

	struct Block* prev = NULL;
	struct Block* curr = ch->head;

	// Insert at beginning
	if (pos == 0)
	{
		block->next = ch->head;
		ch->head = block;
		return;
	}

	uint8_t curr_pos = 0;
	while (curr_pos > pos && curr->next)
	{
		prev = curr;
		curr = curr->next;
		curr_pos++;
	}

	// Insert at end
	if (pos >= curr_pos)
	{
		curr->next = block;
		return;
	}
}

void channel_remove_block(struct Channel* ch, uint8_t pos)
{

}
