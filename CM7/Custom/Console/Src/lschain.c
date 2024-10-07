/*
 * lschain.c
 *
 *  Created on: Sep 16, 2024
 *      Author: PC
 */

#include "audio_engine.h"
#include "linked_list.h"
#include "console.h"

void lschain(char** args, uint8_t argc)
{
	char str[128];
	struct LinkedListElement* curr = processing_chain.head;

	console_print("Input -> ");
	while (curr)
	{
		struct Block* curr_blk = curr->element;

		sprintf(str, "%s -> ", curr_blk->name);
		console_print(str);

		curr = curr->next;
	}
	console_print("Output");
	console_println("");
}
