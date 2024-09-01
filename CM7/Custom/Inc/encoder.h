/*
 * encoder.h
 *
 *  Created on: Jul 22, 2024
 *      Author: PC
 */

#ifndef SRC_ENCODER_H_
#define SRC_ENCODER_H_

#include <stdint.h>
#include <stddef.h>

#include "arm_math.h"

#define LITTLE_ENDIAN 0
#define BIG_ENDIAN 1

#define ENCODER_UINT8 0
#define ENCODER_UINT16 1
#define ENCODER_UINT24 2
#define ENCODER_UINT32 3
#define ENCODER_INT8 4
#define ENCODER_INT16 5
#define ENCODER_INT24 6
#define ENCODER_INT32 7

int8_t encoder_decode_stream(float32_t* dst,
							 uint8_t* src,
							 const size_t block_size,
							 const size_t bytes_per_sample,
							 const size_t channel,
							 const size_t max_channels);

int8_t encoder_decode_2ch_16b(float32_t* dst_ch1, float32_t* dst_ch2, uint8_t* src, int32_t block_size);

#endif /* SRC_ENCODER_H_ */
