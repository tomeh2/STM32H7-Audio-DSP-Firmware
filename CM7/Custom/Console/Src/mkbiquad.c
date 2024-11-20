/*
 * mkdelay.c
 *
 *  Created on: Aug 9, 2024
 *      Author: PC
 */

#include "mkbiquad.h"
#include "console.h"
#include "biquad_filter.h"
#include "audio_defs.h"
#include "block_list.h"

#include <stdlib.h>

void mkbiquad(char** args, uint8_t argc)
{
	if (argc < 6)
	{
		console_printf("Usage: mkbiquad <name> <type> <center_freq> <Q> <order> <sample_rate>\n\r");
		console_printf("name = string which is used to reference this block\n\r");
		console_printf("type = [0 - LPF] [1 - BPF] [2 - HPF]\n\r");
		console_printf("center_freq = center frequency of this band-pass filter\n\r");
		console_printf("Q = Q factor");
		console_printf("order = number of cascaded instances of the filter\n\r");
		console_printf("sample_rate = sample rate of the audio engine\n\r");
		return;
	}

	int32_t filter_type = atof(args[1]);
	float center_freq = atof(args[2]);
	float Q = atof(args[3]);
	int order = atof(args[4]);
	float sr = atof(args[5]);

	struct BiquadFilter* new_biquad = malloc(sizeof(struct BiquadFilter));
	if (!new_biquad)
	{
		console_printf("Failed to allocate memory for BiquadFilter block\n\r");
		return;
	}

	biquad_filter_init(new_biquad, center_freq, sr, Q, order, filter_type);
	/*if (err)
	{
		biquad_filter_destroy(new_biquad);
		console_println("Failed to create BiquadFilter block");
		return;
	}*/

	if (blocklist_insert(new_biquad,
						 args[0],
						 biquad_filter_process,
						 NULL,
						 NULL,
						 biquad_filter_get_param_string,
						 biquad_filter_get_num_params) != EOK)
	{
		console_printf("Failed inserting the BiquadFilter block into the block list\n\r");
		//biquad_filter_destroy(new_biquad);
		return;
	}
	console_printf("BiquadFilter block created\n\r");
}
