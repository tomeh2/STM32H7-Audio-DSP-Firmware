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

	int8_t err = 0;
	err = delayline_init(new_delayline,
						 num_taps,
					 	 max_delay,
						 SAMPLES_PER_BLOCK);

	if (err)
	{
		delayline_destroy(new_delayline);
		console_println("Failed to create DelayLine block");
		return;
	}

	if (blocklist_insert(new_delayline, args[0], delayline_process, BLOCK_TYPE_DELAYLINE) == -1)
	{
		console_println("Failed inserting the DelayLine block into the block list");
		delayline_destroy(new_delayline);
		return;
	}
	console_println("DelayLine block created");
}

void delayline_tap_delay(char** args, uint8_t argc)
{
	if (argc < 3)
	{
		console_println("Usage: delayline_tap_delay <name> <tap_index> <tap_delay>");
		console_println("name = string which is used to reference a block");
		console_println("tap_index = which tap will the command affect");
		console_println("tap_delay = value to which the delay will be set");
		return;
	}

	struct Block* block = blocklist_get_by_name(args[0]);
	if (!block || block->type != BLOCK_TYPE_DELAYLINE)
	{
		console_println("Invalid block type");
		return;
	}

	uint16_t tap_index = atoi(args[1]);
	int32_t tap_delay = atoi(args[2]);

	int8_t err = 0;
	err = delayline_set_tap_delay(block->dsp_struct_ptr, tap_index, tap_delay);

	if (err)
	{
		console_println("Failed to set given tap delay");
	}
}

void delayline_tap_volume(char** args, uint8_t argc)
{
	if (argc < 3)
	{
		console_println("Usage: delayline_tap_volume <name> <tap_index> <volume>");
		console_println("name = string which is used to reference a block");
		console_println("tap_index = which tap will the command affect");
		console_println("volume = volume of the tap");
		return;
	}

	struct Block* block = blocklist_get_by_name(args[0]);
	if (!block || block->type != BLOCK_TYPE_DELAYLINE)
	{
		console_println("Invalid block type");
		return;
	}

	uint16_t tap_index = atoi(args[1]);
	float32_t tap_volume = atof(args[2]);

	int8_t err = 0;
	err = delayline_set_tap_volume(block->dsp_struct_ptr, tap_index, tap_volume);

	if (err)
	{
		console_println("Failed to set given tap volume");
	}
}

void delayline_fb_volume(char** args, uint8_t argc)
{
	if (argc < 2)
	{
		console_println("Usage: delayline_tap_fb <name> <fb_volume>");
		console_println("name = string which is used to reference a block");
		console_println("fb_volume = sets feedback volume");
		return;
	}

	struct Block* block = blocklist_get_by_name(args[0]);
	if (!block || block->type != BLOCK_TYPE_DELAYLINE)
	{
		console_println("Invalid block type");
		return;
	}

	float32_t fb_volume = atof(args[1]);

	int8_t err = 0;
	err = delayline_set_fb_volume(block->dsp_struct_ptr, fb_volume);

	if (err)
	{
		console_println("Failed to set given feedback volume");
	}
}
