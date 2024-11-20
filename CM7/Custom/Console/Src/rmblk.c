/*
 * rmblk.c
 *
 *  Created on: Sep 16, 2024
 *      Author: PC
 */

#include "audio_engine.h"
#include "rmblk.h"
#include "console.h"
#include "audio_defs.h"

#include <stdlib.h>

void rmblk(char** args, uint8_t argc)
{
	if (argc < 2)
	{
		console_printf("rmblk <index> <channel>\n\r");
		console_printf("Removes a block from the processing chain of the specified channel\n\r");
		console_printf("<index> - Which block to remove\n\r");
		console_printf("<channel> - Channel ID from which to remove the block\n\r");
		return;
	}

	uint32_t index = atoi(args[0]);
	uint8_t channel = atoi(args[1]);

	if (channel > 1)
	{
		console_printf("Channel index out of range!\n\r");
		return;
	}

	audio_engine_rmblk(channel, index);
}
