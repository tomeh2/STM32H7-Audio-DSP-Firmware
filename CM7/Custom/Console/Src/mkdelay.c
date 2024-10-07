/*
 * mkdelay.c
 *
 *  Created on: Aug 9, 2024
 *      Author: PC
 */

#include "mkdelay.h"
#include "console.h"
#include "delay_line.h"
#include "audio_defs.h"
#include "block_list.h"

#include <stdlib.h>

void mkdelay(char** args, uint8_t argc)
{
	if (argc < 2)
	{
		console_println("Usage: delayline_create <name> <num_taps> <max_delay>");
		console_println("name = string which is used to reference this block");
		console_println("num_taps = maximum number of taps for this delay line");
		console_println("max_delay = maximum possible delay in number of samples");
		return;
	}

	uint8_t num_taps = atoi(args[1]);
	int32_t max_delay = atoi(args[2]);

	struct DelayLine* new_delayline = malloc(sizeof(struct DelayLine));
	if (!new_delayline)
	{
		console_println("Failed to allocate memory for DelayLine block");
		return;
	}

	int8_t err = delayline_init(new_delayline, num_taps, max_delay, SAMPLES_PER_BLOCK);
	if (err)
	{
		delayline_destroy(new_delayline);
		console_println("Failed to create DelayLine block");
		return;
	}

	if (blocklist_insert(new_delayline, args[0], delayline_process, delayline_set_param, delayline_get_param_str, delayline_get_num_params) == -1)
	{
		console_println("Failed inserting the DelayLine block into the block list");
		delayline_destroy(new_delayline);
		return;
	}
	console_println("DelayLine block created");
}
