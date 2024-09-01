/*
 * help.c
 *
 *  Created on: Aug 5, 2024
 *      Author: PC
 */

#include "help.h"

void help(char** args, uint8_t argc)
{
	struct Command* curr = command_list_head;

	while (curr)
	{
		console_print(curr->name);
		console_print(STRING_NEWLINE);
		curr = curr->next;
	}
}
