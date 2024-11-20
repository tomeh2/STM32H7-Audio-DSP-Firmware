/*
 * setparam.c
 *
 *  Created on: Sep 10, 2024
 *      Author: PC
 */

#include "setparam.h"
#include "block.h"
#include "block_list.h"
#include "console.h"

#include <stdlib.h>

void setparam(char** args, uint8_t argc)
{
	if (argc < 3)
	{
		console_printf("setparam <block_name> <index> <value>\n\r");
		console_printf("Sets the identified parameter to a specified value\n\r");
		console_printf("<block_name> - Name of the block whose parameter will be set\n\r");
		console_printf("<index> - Index of the parameter to be set\n\r");
		console_printf("<value> - Value to which the parameter will be set\n\r");
		return;
	}

	struct Block* block = blocklist_get_by_name(args[0]);
	uint8_t index = atoi(args[1]);
	float value = atof(args[2]);

	if (!block)
	{
		console_printf("Block does not exist\n\r");
		return;
	}
	int8_t err = block_set_param(block, index, value);

	if (err)
	{
		console_printf("Failed to set the parameter\n\r");
	}
}
