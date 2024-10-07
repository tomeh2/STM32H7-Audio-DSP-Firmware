/*
 * lsparam.c
 *
 *  Created on: Sep 9, 2024
 *      Author: PC
 */

#include "lsparam.h"
#include "block_list.h"
#include "delay_line.h"

void lsparam(char** args, uint8_t argc)
{
	if (argc < 1)
	{
		console_println("lsparam <block_name>");
		console_println("Lists all parameters contained in the <block_name> block");
		console_println("<block_name> - Name of the block whose parameters will be listed");
		return;
	}

	struct Block* block = blocklist_get_by_name(args[0]);

	if (!block)
	{
		console_println("Block does not exist");
		return;
	}

	char print_buf[128];
	for (uint8_t param_index = 0; param_index < block_get_num_params(block); param_index++)
		console_println(block_get_param_str(block, param_index));
}

