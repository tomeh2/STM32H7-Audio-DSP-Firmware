/*
 * usb_driver.c
 *
 *  Created on: Aug 26, 2024
 *      Author: PC
 */

#include "usb_audio_driver.h"
#include "audio_defs.h"
#include "arm_math.h"
#include "encoder.h"

#define ACCUMULATOR_BUFFER_SIZE (SAMPLES_PER_BLOCK * AUDIO_CHANNELS * BYTES_PER_SAMPLE)
#define USB_AUDIOCLASS_RXBUF_SIZE (USB_AUDIOCLASS_RXBUF_BLOCKS * SAMPLES_PER_BLOCK)

static uint8_t is_init = 0;

static uint8_t rx_accumulator[ACCUMULATOR_BUFFER_SIZE];
static int32_t rx_accumulator_used;
static float32_t rx_buffer[USB_AUDIOCLASS_RXBUF_SIZE];
static int32_t rx_head_block;
static int32_t rx_tail_block;
static int32_t rx_used_blocks;

int8_t usb_start(struct Interface* intf)
{
	__disable_irq();
	if (is_init)
	{
		__enable_irq();
		return -EINVAL;
	}

	rx_head_block = 0;
	rx_tail_block = 0;
	rx_used_blocks = 0;
	rx_accumulator_used = 0;

	is_init = 1;

	__enable_irq();
	return EOK;
}

int8_t usb_stop(struct Interface* intf)
{
	__disable_irq();
	if (!is_init)
	{
		__enable_irq();
		return -EINVAL;
	}

	__enable_irq();
	return EOK;
}


int8_t usb_read(struct Interface* intf, void* buf, size_t len)
{
	__disable_irq();
	if (!is_init)
	{
		__enable_irq();
		return -EINVAL;
	}

	if (len != SAMPLES_PER_BLOCK * 2)
	{
		__enable_irq();
		return -EINVAL;
	}

	float32_t* dst_buf = buf;
	memcpy(dst_buf, &rx_buffer[rx_head_block * SAMPLES_PER_BLOCK], sizeof(float32_t) * len);

	/*if (rx_used_blocks < 2)
	{
		__enable_irq();
		return -EINVAL;
	}*/

	rx_head_block += 2;
	if (rx_head_block == USB_AUDIOCLASS_RXBUF_BLOCKS)
		rx_head_block = 0;
	//rx_used_blocks -= 2;

	__enable_irq();
	return EOK;
}

int8_t usb_write(struct Interface* intf, void* buf, size_t len)
{
	__disable_irq();
	if (!is_init)
	{
		__enable_irq();
		return -EINVAL;
	}

	uint8_t* buf_uint8p = buf;
	int32_t rx_accumulator_free = ACCUMULATOR_BUFFER_SIZE - rx_accumulator_used;
	int32_t rx_accumulator_leftover = len - rx_accumulator_free;
	if (rx_accumulator_free < len)
	{
		memcpy(&rx_accumulator[rx_accumulator_used], buf_uint8p, rx_accumulator_free);
		rx_accumulator_used += rx_accumulator_free;

		/*if (rx_used_blocks > USB_AUDIOCLASS_RXBUF_BLOCKS - 2)
		{
			rx_accumulator_used = 0;
			memcpy(&rx_accumulator[0], buf_uint8p, rx_accumulator_leftover);
			__enable_irq();
			return -EINVAL;
		}*/
		encoder_decode_2ch_16b(&rx_buffer[rx_tail_block * SAMPLES_PER_BLOCK],
							   &rx_buffer[(rx_tail_block + 1) * SAMPLES_PER_BLOCK],
							   rx_accumulator,
							   SAMPLES_PER_BLOCK);
		//rx_used_blocks += 2;
		rx_tail_block += 2;
		if (rx_tail_block == USB_AUDIOCLASS_RXBUF_BLOCKS)
			rx_tail_block = 0;

		memcpy(&rx_accumulator[0], &buf_uint8p[rx_accumulator_free], rx_accumulator_leftover);
		rx_accumulator_used = rx_accumulator_leftover;
	}
	else
	{
		memcpy(&rx_accumulator[rx_accumulator_used], buf, len);
		rx_accumulator_used += len;
	}

	__enable_irq();
	return EOK;
}

int8_t usb_ioctl(struct Interface* intf, uint32_t ctl_id)
{
	__disable_irq();
	if (!is_init)
	{
		__enable_irq();
		return -EINVAL;
	}

	__enable_irq();
	return EOK;
}

struct InterfaceOperations usb_audio_class_driver = {
	.start = usb_start,
	.stop = usb_stop,
	.read = usb_read,
	.write = usb_write,
	.ioctl = usb_ioctl,
};
