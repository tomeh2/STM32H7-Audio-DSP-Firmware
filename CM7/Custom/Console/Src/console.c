/*
 * console.c
 *
 *  Created on: Jul 31, 2024
 *      Author: PC
 */

#include "stm32h7xx_hal.h"
#include "interface.h"
#include "console.h"
#include "driver_manager.h"

#include <string.h>
#include <stdlib.h>

#define CONSOLE_MAX_COMMANDS 32
#define CONSOLE_BUFFER_SIZE 64
#define CONSOLE_MAX_ARGS 8

#define KEY_ENTER 0x0D
#define KEY_BACKSPACE 0x08

#define MAX_ARGS 8

static char module_str[] = "[Console]";

char STRING_PROMPT[] = "> ";
char STRING_BACKSPACE[] = "\b \b";
char STRING_NEWLINE[] = "\n\r";

static uint8_t console_buffer[CONSOLE_BUFFER_SIZE + 1];
static uint8_t console_buffer_index;

uint8_t console_initialized = 0;
uint8_t registered_commands;
struct Command* command_list_head;

static char* args[MAX_ARGS];

void console_init()
{
	if (!serial_device)
		return;

	console_buffer_index = 0;
	console_buffer[CONSOLE_BUFFER_SIZE] = '\0';
	registered_commands = 0;
	command_list_head = NULL;
	console_initialized = 1;
}

void console_print(char* str)
{
	if (!console_initialized)
		return;

	size_t str_len = strlen(str);
	serial_device->io_ops->write
		(serial_device, str, str_len);
}

void console_println(char* str)
{
	if (!console_initialized)
			return;

	console_print(str);
	console_print(STRING_NEWLINE);
}

void console_register_command(char* name, void (*func)())
{
	char print_buf[128];
	if (!console_initialized)
		return;

	struct Command* new_command = malloc(sizeof(struct Command));
	new_command->name = name;
	new_command->func = func;
	new_command->next = NULL;
	if (!command_list_head)
	{
		command_list_head = new_command;
	}
	else
	{
		struct Command* curr = command_list_head;
		while (curr->next) curr = curr->next;
		curr->next = new_command;
	}
	sprintf(print_buf, "%s Registered command: %s", module_str, name);
	console_println(print_buf);
}

void console_parse()
{
	if (!console_initialized)
		return;

	if (console_buffer[0] == '\0' || console_buffer_index == 0)
	{
		console_print(STRING_NEWLINE);
		console_print(STRING_PROMPT);
		return;
	}

	uint8_t command_found = 0;
	struct Command* curr = command_list_head;
	while (curr)
	{
		if (strcmp(curr->name, console_buffer) == 0)
		{
			uint8_t arg_index = 0;
			uint8_t arg_start_index = strlen(console_buffer) + 1;
			while (arg_start_index < console_buffer_index && console_buffer[arg_start_index] != '\0' && arg_index < MAX_ARGS)
			{
				args[arg_index++] = &console_buffer[arg_start_index];
				arg_start_index += strlen(&console_buffer[arg_start_index]) + 1;
			}

			console_print(STRING_NEWLINE);
			curr->func(args, arg_index);
			console_print(STRING_NEWLINE);
			console_print(STRING_PROMPT);
			command_found = 1;
			break;
		}
		curr = curr->next;
	}


	// This action is taken if no matching command was found
	if (command_found == 0)
	{
		console_print(STRING_NEWLINE);
		console_print("Unrecognized command!");
		console_print(STRING_NEWLINE);
		console_print(STRING_PROMPT);
	}
}

void console_exec(char* str)
{
	console_print(str);

	strcpy(console_buffer, str);
	console_buffer_index = strlen(str);

	for (uint8_t i = 0; i < console_buffer_index; i++)
	{
		if (console_buffer[i] == ' ')
			console_buffer[i] = '\0';
	}
	console_buffer[console_buffer_index] = '\0';
	console_parse();
	console_buffer_index = 0;
}

void console_iteration()
{
	if (!console_initialized)
		return;

	uint8_t next_char;
	while (serial_device->io_ops->read(serial_device, &next_char, 1))
	{
		switch (next_char)
		{
		case KEY_ENTER:
			console_buffer[console_buffer_index] = '\0';
			console_parse();
			console_buffer_index = 0;
			break;
		case KEY_BACKSPACE:
			if (console_buffer_index != 0)
			{
				console_buffer_index--;

				console_print(STRING_BACKSPACE);
			}
			break;
		case 32 ... 126:
			if (console_buffer_index < CONSOLE_BUFFER_SIZE)
			{
				console_buffer[console_buffer_index++] = (next_char == ' ' ? '\0' : next_char);
				serial_device->io_ops->write(serial_device, &next_char, 1);
			}
			break;
		}
	}
}