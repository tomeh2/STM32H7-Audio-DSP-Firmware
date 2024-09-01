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
		if (block_list[i].type == BLOCK_TYPE_DELAYLINE)
		{
			console_println("Type: DELAY_LINE");
			sprintf(print_buf, "Name: %s", block_list[i].name);
			console_println(print_buf);
			struct DelayLine* delay_line = block_list[i].dsp_struct_ptr;
			sprintf(print_buf, "Max Delay: %u", delay_line->max_delay);
			console_println(print_buf);
			sprintf(print_buf, "Feedback Coeff: %f", delay_line->fb_coeff);
			console_println(print_buf);

			for (uint8_t i = 0; i < delay_line->num_taps; i++)
			{
				sprintf(print_buf, "Tap %u Delay: %i", i, delay_line->taps[i]);
				console_println(print_buf);
				sprintf(print_buf, "Tap %u Coeff: %f", i, delay_line->coeffs[i]);
				console_println(print_buf);
			}
		}
		else if (block_list[i].type == BLOCK_TYPE_MODULATOR)
		{
			console_println("Type: MODULATOR");
		}
		else
			console_println("Type: UNKNOWN");
	}
}
