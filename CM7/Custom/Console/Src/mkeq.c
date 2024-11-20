/*
 * mkeq.c
 *
 *  Created on: Nov 20, 2024
 *      Author: PC
 */

#include "mkeq.h"
#include "console.h"
#include "equalizer.h"
#include "audio_defs.h"
#include "block_list.h"

#include <stdlib.h>

void mkeq(char** args, uint8_t argc)
{
	if (argc < 1)
	{
		console_printf("Usage: mkeq <name>\n\r");
		console_printf("name = string which is used to reference this block\n\r");
		return;
	}

	struct Equalizer* new_eq = malloc(sizeof(struct Equalizer));
	if (!new_eq)
	{
		console_printf("Failed to allocate memory for Equalizer block\n\r");
		return;
	}

	equalizer_init(new_eq, 48000);
	/*if (err)
	{
		equalizer_destroy(new_eq);
		console_println("Failed to create Equalizer block");
		return;
	}*/

	if (blocklist_insert(new_eq,
						 args[0],
						 equalizer_process,
						 NULL,
						 NULL,
						 equalizer_get_param_string,
						 equalizer_get_num_params) != EOK)
	{
		console_printf("Failed inserting the Equalizer block into the block list\n\r");
		return;
	}
	console_printf("Equalizer block created\n\r");
}
