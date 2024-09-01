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
		console_println("modulator_create <name>");
		console_println("name = string which will be used to reference this block");
		return;
	}

	char* name = args[0];

	struct Modulator* new_modulator = malloc(sizeof(struct Modulator));
	modulator_init(new_modulator);

	if (!new_modulator)
	{
		console_println("Failed to create a modulator");
		return;
	}

	if (blocklist_insert(new_modulator, args[0], modulator_process, BLOCK_TYPE_MODULATOR) == -1)
	{
		console_println("Failed inserting the modulator block into the block list");
		modulator_destroy(new_modulator);
		return;
	}
	console_println("Modulator block created");
}
