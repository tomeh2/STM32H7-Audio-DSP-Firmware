/*
 * rmblk.c
 *
 *  Created on: Sep 16, 2024
 *      Author: PC
 */

#include "rmblk.h"
#include "audio_engine.h"
#include "console.h"

#include <stdlib.h>

void rmblk(char** args, uint8_t argc)
{
	if (argc < 2)
	{
		console_println("rmblk <channel> <index>");
		console_println("Removes a block from the processing chain of the specified channel");
		console_println("<channel> - Channel ID from which to remove the block");
		console_println("<index> - Which block to remove");
		return;
	}

	uint8_t channel = atoi(args[0]);
	uint32_t index = atoi(args[1]);

	audio_engine_rmblk(channel, index);
}
