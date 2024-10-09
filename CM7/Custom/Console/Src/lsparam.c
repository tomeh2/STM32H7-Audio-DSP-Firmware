/*
 * lsparam.c
 *
 *  Created on: Sep 9, 2024
 *      Author: PC
 */

#include "lsparam.h"
#include "block_list.h"
#include "delay_line.h"
#include "audio_defs.h"

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

	if (!block->get_num_params)
	{
		console_println("Block does not implement get_num_params function");
		return;
	}

	if (!block->get_param_string)
	{
		console_println("Block does not implement get_param_str function");
		return;
	}

	char print_buf[128];
	uint8_t num_params = block_get_num_params(block);
	for (uint8_t i = 0; i < num_params; i++)
	{
		block_get_param_string(block, i, print_buf);
		console_println(print_buf);
	}
}

