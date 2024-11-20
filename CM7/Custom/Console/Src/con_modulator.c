/*
 * con_modulator.c
 *
 *  Created on: Aug 14, 2024
 *      Author: PC
 */

#include "con_modulator.h"
#include "modulator.h"
#include "console.h"
#include "block_list.h"

#include <stdlib.h>

void modulator_create(char** args, uint8_t argc)
{
	if (argc < 1)
	{
		console_printf("modulator_create <name>\n\r");
		console_printf("name = string which will be used to reference this block\n\r");
		return;
	}

	char* name = args[0];

	struct Modulator* new_modulator = malloc(sizeof(struct Modulator));
	modulator_init(new_modulator);

	if (!new_modulator)
	{
		console_printf("Failed to create a modulator\n\r");
		return;
	}

	if (blocklist_insert(new_modulator,
						 args[0],
						 modulator_process,
						 modulator_set_param,
						 modulator_get_param,
						 modulator_get_param_string,
						 modulator_get_num_params) != 0)
	{
		console_printf("Failed inserting the modulator block into the block list\n\r");
		modulator_destroy(new_modulator);
		return;
	}
	console_printf("Modulator block created\n\r");
}
