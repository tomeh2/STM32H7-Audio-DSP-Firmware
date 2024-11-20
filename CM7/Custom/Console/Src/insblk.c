/*
 * insblk.c
 *
 *  Created on: Aug 9, 2024
 *      Author: PC
 */

#include "audio_engine.h"
#include "insblk.h"
#include "console.h"
#include "audio_defs.h"
#include "block_list.h"

#include <stdlib.h>

void insblk(char** args, uint8_t argc)
{
	if (argc < 2)
	{
		console_printf("insblk <name> <channel>\n\r");
		console_printf("name = name of the block to insert into the processing chain\n\r");
		console_printf("channel = into which channel will be block be put\n\r");
		return;
	}

	struct Block* block = blocklist_get_by_name(args[0]);

	if (!block)
	{
		console_printf("Invalid block type\n\r");
		return;
	}

	uint8_t channel = atoi(args[1]);

	audio_engine_insblk(channel, block);
	console_printf("Block inserted\n\r");
}
