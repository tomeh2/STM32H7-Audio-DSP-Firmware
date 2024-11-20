/*
 * help.c
 *
 *  Created on: Aug 5, 2024
 *      Author: PC
 */

#include "help.h"

void help(char** args, uint8_t argc)
{
	struct Command* curr = console_get_command_list();

	while (curr)
	{
		console_printf(curr->name);
		console_printf("\n\r");
		curr = curr->next;
	}
}
