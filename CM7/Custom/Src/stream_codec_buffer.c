/*
 * stream_codec_buffer.c
 *
 *  Created on: Jan 16, 2025
 *      Author: PC
 */

#include "stream_codec_buffer.h"

int8_t scb_initialize(struct StreamCodecBuffer* scb, float* buf, size_t buf_size)
{
	if (!scb)
		return -1;

	scb->buf = buf;
	scb->head = 0;
	scb->tail = 0;
	scb->size = buf_size;

	return 0;
}

int8_t scb_fp32_write(struct StreamCodecBuffer* scb, float* src_buf, size_t len)
{
	if (!scb || !src_buf || !scb->size)
		return -1;

	for (size_t i = 0; i < len; i++)
	{
		scb->buf[scb->tail++] = src_buf[i];
		if (scb->tail == scb->size)
			scb->tail = 0;
	}
	return 0;
}

int8_t scb_fp32_read(struct StreamCodecBuffer* scb, float* dst_buf, size_t len)
{
	// 2 channels
	if (!scb || !dst_buf || !scb->size)
		return -1;

	for (size_t i = 0; i < len / 2; i++)
	{
		dst_buf[i] = scb->buf[scb->head++];
		if (scb->head == scb->size)
			scb->head = 0;

		dst_buf[len / 2 + i] = scb->buf[scb->head++];
		if (scb->head == scb->size)
			scb->head = 0;
	}
	return 0;
}

int8_t scb_int8_write(struct StreamCodecBuffer* scb, char* src_buf, size_t len)
{
	if (!scb || !src_buf || !scb->size)
		return -1;

	for (size_t i = 0; i < len; i += 2)
	{
		int16_t sample_i16 = src_buf[i + 1];
		sample_i16 <<= 8;
		sample_i16 |= src_buf[i];

		float sample_f32 = (float) sample_i16 / 32768.f;
		scb->buf[scb->tail++] = sample_f32;
		if (scb->tail == scb->size)
			scb->tail = 0;
	}
	return 0;
}

int8_t scb_int8_read(struct StreamCodecBuffer* scb, char* dst_buf, size_t len)
{
	if (!scb || !dst_buf || !scb->size)
		return -1;

	for (size_t i = 0; i < len; i += 2)
	{
		float sample_f32 = scb->buf[scb->head++];
		if (scb->head == scb->size)
			scb->head = 0;

		int16_t sample_i16 = (int16_t) (sample_f32 * 1000.f);
		dst_buf[i] = sample_i16;
		dst_buf[i + 1] = sample_i16 >> 8;
	}
	return 0;
}
