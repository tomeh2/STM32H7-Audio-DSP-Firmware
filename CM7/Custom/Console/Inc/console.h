/*
 * console.h
 *
 *  Created on: Aug 5, 2024
 *      Author: PC
 */

#ifndef CONSOLE_INC_CONSOLE_H_
#define CONSOLE_INC_CONSOLE_H_

#include "interface.h"

extern void console_init();
extern void console_print(char* str);
extern void console_println(char* str);
extern void console_exec(char* str);
extern void console_register_command(char* name, void (*func)());
extern void console_iteration();

extern char STRING_PROMPT[];
extern char STRING_NEWLINE[];
extern char STRING_BACKSPACE[];

struct Command
{
	char* name;
	void (*func)(char** args, uint8_t argc);
	struct Command* next;
};

extern uint8_t registered_commands;
extern struct Command* command_list_head;

#endif /* CONSOLE_INC_CONSOLE_H_ */
