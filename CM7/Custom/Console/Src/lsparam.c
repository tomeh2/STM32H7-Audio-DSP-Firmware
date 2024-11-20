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
		console_printf("lsparam <block_name>\n\r");
		console_printf("Lists all parameters contained in the <block_name> block\n\r");
		console_printf("<block_name> - Name of the block whose parameters will be listed\n\r");
		return;
	}

	struct Block* block = blocklist_get_by_name(args[0]);

	if (!block)
	{
		console_printf("Block does not exist\n\r");
		return;
	}

	if (!block->get_num_params)
	{
		console_printf("Block does not implement get_num_params function\n\r");
		return;
	}

	if (!block->get_param_string)
	{
		console_printf("Block does not implement get_param_str function\n\r");
		return;
	}

	char param_str[128];
	uint8_t num_params = block_get_num_params(block);
	for (uint8_t i = 0; i < num_params; i++)
	{
		block_get_param_string(block, i, param_str);
		console_printf("%s\n\r", param_str);
	}
}

