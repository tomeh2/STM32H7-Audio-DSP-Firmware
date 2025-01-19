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
#include "stream_codec_buffer.h"

static uint8_t is_init = 0;

#define RX_BUFSIZE 4096
#define TX_BUFSIZE 4096

float rx_buffer[RX_BUFSIZE];
float tx_buffer[TX_BUFSIZE];

struct StreamCodecBuffer tx_scb;
struct StreamCodecBuffer rx_scb;

int8_t usb_start(struct HostInterface* intf)
{
	__disable_irq();
	if (is_init)
	{
		__enable_irq();
		return -EINVAL;
	}

	scb_initialize(&tx_scb, tx_buffer, TX_BUFSIZE);
	scb_initialize(&rx_scb, rx_buffer, RX_BUFSIZE);

	is_init = 1;

	__enable_irq();
	return EOK;
}

int8_t usb_stop(struct HostDriver* intf)
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


int8_t usb_dev_read(struct HostDriver* intf, float* buf, size_t len)
{
	__disable_irq();

	if (!is_init)
	{
		__enable_irq();
		return -EINVAL;
	}

	scb_fp32_read(&rx_scb, buf, len);

	__enable_irq();
	return EOK;
}

int8_t usb_dev_write(struct HostDriver* intf, float* buf, size_t len)
{
	__disable_irq();

	if (!is_init)
	{
		__enable_irq();
		return -EINVAL;
	}

	scb_fp32_write(&tx_scb, buf, len);

	__enable_irq();
	return EOK;
}

int8_t usb_host_read(struct HostDriver* intf, char* buf, size_t len)
{
	__disable_irq();

	if (!is_init)
	{
		__enable_irq();
		return -EINVAL;
	}

	scb_int8_read(&tx_scb, buf, len);

	__enable_irq();
	return EOK;
}

int8_t usb_host_write(struct HostDriver* intf, char* buf, size_t len)
{
	__disable_irq();
	if (!is_init)
	{
		__enable_irq();
		return -EINVAL;
	}

	scb_int8_write(&rx_scb, buf, len);

	__enable_irq();
	return EOK;
}

int8_t usb_ioctl(struct HostDriver* intf, uint32_t ctl_id)
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

struct HostDriverOps usb_audio_class_driver = {
	.start = usb_start,
	.stop = usb_stop,
	.host_data_read = usb_host_read,
	.host_data_write = usb_host_write,
	.dev_data_read = usb_dev_read,
	.dev_data_write = usb_dev_write,
	.ioctl = usb_ioctl,
};
