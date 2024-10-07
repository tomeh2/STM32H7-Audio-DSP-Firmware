/*
 * lsblk.c
 *
 *  Created on: Aug 9, 2024
 *      Author: PC
 */

#include "lsblk.h"
#include "block_list.h"
#include "console.h"
#include "delay_line.h"

#include <stdio.h>

void lsblk(char** args, uint8_t argc)
{
	char print_buf[128];
	for (uint8_t i = 0; i < MAX_DSP_BLOCKS; i++)
	{
		sprintf(print_buf, "===== Block %u =====", i);
		console_println(print_buf);
		console_println(block_list[i].name);
	}
}
