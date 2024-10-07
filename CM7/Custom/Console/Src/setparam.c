/*
 * setparam.c
 *
 *  Created on: Sep 10, 2024
 *      Author: PC
 */

#include "setparam.h"
#include "block.h"

#include <stdlib.h>

void setparam(char** args, uint8_t argc)
{
	if (argc < 3)
	{
		console_println("setparam <block_name> <index> <value>");
		console_println("Sets the identified parameter to a specified value");
		console_println("<block_name> - Name of the block whose parameter will be set");
		console_println("<index> - Index of the parameter to be set");
		console_println("<value> - Value to which the parameter will be set");
		return;
	}

	struct Block* block = blocklist_get_by_name(args[0]);
	uint8_t index = atoi(args[1]);
	float value = atof(args[2]);

	if (!block)
	{
		console_println("Block does not exist");
		return;
	}
	int8_t err = block_set_param(block, index, value);

	if (err)
	{
		console_println("Failed to set the parameter");
	}
}
