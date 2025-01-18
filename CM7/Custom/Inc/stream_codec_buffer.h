/*
 * stream_codec_buffer.h
 *
 *  Created on: Jan 16, 2025
 *      Author: PC
 */

#ifndef INC_STREAM_CODEC_BUFFER_H_
#define INC_STREAM_CODEC_BUFFER_H_

#include <stdint.h>
#include <stddef.h>

struct StreamCodecBuffer
{
	float* buf;
	size_t head;
	size_t tail;
	size_t size;
};

int8_t scb_initialize(struct StreamCodecBuffer* scb, float* buf, size_t buf_size);
int8_t scb_fp32_write(struct StreamCodecBuffer* scb, float* src_buf, size_t len);
int8_t scb_fp32_read(struct StreamCodecBuffer* scb, float* dst_buf, size_t len);
int8_t scb_int8_write(struct StreamCodecBuffer* scb, char* dst_buf, size_t len);
int8_t scb_int8_read(struct StreamCodecBuffer* scb, char* dst_buf, size_t len);

#endif /* INC_STREAM_CODEC_BUFFER_H_ */
