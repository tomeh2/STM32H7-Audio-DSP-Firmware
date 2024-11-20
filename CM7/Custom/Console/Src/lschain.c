/*
 * lschain.c
 *
 *  Created on: Sep 16, 2024
 *      Author: PC
 */

#include <audio_stream.h>
#include "linked_list.h"
#include "console.h"
#include "audio_defs.h"
#include "audio_engine.h"

void lschain(char** args, uint8_t argc)
{
	console_printf("Number of Channels: %u\n\r", NUM_AUDIO_STREAMS);
	for (uint8_t i = 0; i < NUM_AUDIO_STREAMS; i++)
	{
		struct LinkedListElement* curr = audio_engine_get_stream(i)->processing_chain.head;

		console_printf("Channel %u:\n\rInput -> ", i);
		while (curr)
		{
			struct Block* curr_blk = curr->element;

			console_printf("%s -> ", curr_blk->name);

			curr = curr->next;
		}
		console_printf("Output\n\r");
	}
}
