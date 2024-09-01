/*
 * encoder.c
 *
 *  Created on: Jul 22, 2024
 *      Author: PC
 */

#include "encoder.h"
#include "audio_defs.h"

#include <math.h>

int8_t encoder_decode_stream(float32_t* dst,
							  uint8_t* src,
							  const size_t block_size,
							  const size_t bytes_per_sample,
							  const size_t channel,
							  const size_t max_channels)
{
	size_t offset = channel * bytes_per_sample;
	size_t stride = bytes_per_sample * max_channels;
	float normalization_factor = 2.f / (pow(2.f, (bytes_per_sample << 3)));
	size_t sign_shift_amount = 8 * (4 - bytes_per_sample);
	size_t src_base_index = offset;
	for (size_t i = 0; i < block_size; i++)
	{
		int32_t sample = 0;
		for (int j = bytes_per_sample - 1; j >= 0; j--)
		{
			sample <<= 8;
			sample |= src[src_base_index + j];
		}
		sample <<= sign_shift_amount;
		sample >>= sign_shift_amount;
		dst[i] = (float32_t) sample * normalization_factor;

		src_base_index += stride;
	}
	return EOK;
}

// Experimental optimized function to decode a byte stream to a float32 block
// Removal of generic logic should hopefully speed things up a bit
// Loop unroll by a factor of 4

// This function seems to run about 2x faster then the generic decoder implementation
// (108 us vs 210 us) in debug mode
int8_t encoder_decode_2ch_16b(float32_t* dst_ch1, float32_t* dst_ch2, uint8_t* src, int32_t block_size)
{
	if (block_size & 0x7)
		return -EINVBLKSIZE;

	int32_t dst_index = 0;
	int32_t src_index = 0;
	float32_t normalization_factor = 1.f / 32768.f;

	int16_t samples[4];
	while (dst_index < block_size)
	{
		samples[0] = 0;
		samples[1] = 0;
		samples[2] = 0;
		samples[3] = 0;

		samples[0] = src[src_index + 1];
		samples[1] = src[src_index + 3];
		samples[2] = src[src_index + 5];
		samples[3] = src[src_index + 7];

		samples[0] <<= 8;
		samples[1] <<= 8;
		samples[2] <<= 8;
		samples[3] <<= 8;

		samples[0] |= src[src_index];
		samples[1] |= src[src_index + 2];
		samples[2] |= src[src_index + 4];
		samples[3] |= src[src_index + 6];

		dst_ch1[dst_index] = (float32_t) samples[0] * normalization_factor;
		dst_ch2[dst_index] = (float32_t) samples[1] * normalization_factor;
		dst_ch1[dst_index + 1] = (float32_t) samples[2] * normalization_factor;
		dst_ch2[dst_index + 1] = (float32_t) samples[3] * normalization_factor;

		src_index += 8;
		dst_index += 2;
	}
	return EOK;
}
