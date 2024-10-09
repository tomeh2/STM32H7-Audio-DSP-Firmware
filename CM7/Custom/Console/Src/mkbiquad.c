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
	if (argc < 4)
	{
		console_println("Usage: mkbiquad <name> <type> <center_freq> <Q> <sample_rate>");
		console_println("name = string which is used to reference this block");
		console_println("type = [0 - LPF] [1 - BPF] [2 - HPF]");
		console_println("center_freq = center frequency of this band-pass filter");
		console_println("Q = Q factor");
		console_println("sample_rate = sample rate of the audio engine");
		return;
	}

	int32_t filter_type = atof(args[1]);
	float center_freq = atof(args[2]);
	float Q = atof(args[3]);
	float sr = atof(args[4]);

	struct BiquadFilter* new_biquad = malloc(sizeof(struct BiquadFilter));
	if (!new_biquad)
	{
		console_println("Failed to allocate memory for BiquadFilter block");
		return;
	}

	biquad_filter_init(new_biquad, center_freq, sr, Q, filter_type);
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
						 biquad_filter_get_num_params,
						 biquad_filter_to_string))
	{
		console_println("Failed inserting the BiquadFilter block into the block list");
		//biquad_filter_destroy(new_biquad);
		return;
	}
	console_println("BiquadFilter block created");
}
