/*
 * console.h
 *
 *  Created on: Aug 5, 2024
 *      Author: PC
 */

#ifndef CONSOLE_INC_CONSOLE_H_
#define CONSOLE_INC_CONSOLE_H_

#include "interface.h"

void console_init();
void console_printf(const char* fmt, ...);
void console_exec_script(char* str);
void console_exec(char* str);
void console_register_command(char* name, void (*func)());
struct Command* console_get_command_list();
void console_iteration();

struct Command
{
	char* name;
	void (*func)(char** args, uint8_t argc);
	struct Command* next;
};

#endif /* CONSOLE_INC_CONSOLE_H_ */
