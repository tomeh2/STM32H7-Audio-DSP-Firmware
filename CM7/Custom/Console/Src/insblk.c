/*
 * insblk.c
 *
 *  Created on: Aug 9, 2024
 *      Author: PC
 */

#include "insblk.h"

#include "console.h"
#include "audio_engine.h"
#include "audio_defs.h"
#include "block_list.h"

#include <stdlib.h>

void insblk(char** args, uint8_t argc)
{
	if (argc < 2)
	{
		console_println("insblk <name> <channel>");
		console_println("name = name of the block to insert into the processing chain");
		console_println("channel = into which channel will be block be put");
		return;
	}

	struct Block* block = blocklist_get_by_name(args[0]);

	if (!block || block->type == BLOCK_TYPE_UNKNOWN)
	{
		console_println("Invalid block type");
		return;
	}

	uint8_t channel = atoi(args[1]);

	audio_engine_insblk(channel, block);
	console_println("Block inserted");
}
