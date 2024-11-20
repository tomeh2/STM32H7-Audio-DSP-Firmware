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
		console_printf("Usage: delayline_create <name> <num_taps> <max_delay>\n\r");
		console_printf("name = string which is used to reference this block\n\r");
		console_printf("num_taps = maximum number of taps for this delay line\n\r");
		console_printf("max_delay = maximum possible delay in number of samples\n\r");
		return;
	}

	uint8_t num_taps = atoi(args[1]);
	int32_t max_delay = atoi(args[2]);

	struct DelayLine* new_delayline = malloc(sizeof(struct DelayLine));
	if (!new_delayline)
	{
		console_printf("Failed to allocate memory for DelayLine block\n\r");
		return;
	}

	int8_t err = delayline_init(new_delayline, num_taps, max_delay, SAMPLES_PER_BLOCK);
	if (err)
	{
		delayline_destroy(new_delayline);
		console_printf("Failed to create DelayLine block\n\r");
		return;
	}

	if (blocklist_insert(new_delayline,
						 args[0],
						 delayline_process,
						 delayline_set_param,
						 delayline_get_param,
						 delayline_get_param_string,
						 delayline_get_num_params) != EOK)
	{
		console_printf("Failed inserting the DelayLine block into the block list\n\r");
		delayline_destroy(new_delayline);
		return;
	}
	console_printf("DelayLine block created\n\r");
}
