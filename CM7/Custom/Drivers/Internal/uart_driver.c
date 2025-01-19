/*
 * uart_driver.c
 *
 *  Created on: Aug 1, 2024
 *      Author: PC
 */

#include "stm32h7xx_hal.h"
#include "uart_driver.h"
#include "audio_defs.h"

#include <stdlib.h>

#define UART_RECV_BUF_SIZE 64

static UART_HandleTypeDef* huart;

static uint8_t is_init = 0;

static uint8_t rx_buf[UART_RECV_BUF_SIZE];
static size_t rx_head;
static size_t rx_tail;
static size_t rx_used;

static uint8_t recv;

static uint8_t uart_lock;

int8_t uart_start(struct TerminalDriver* intf)
{
	if (is_init)
		return -EINVAL;

	if (intf->private_data == NULL)
		return -EINVAL;

	huart = intf->private_data;
	HAL_UART_Receive_IT(huart, &recv, 1);

	rx_head = 0;
	rx_tail = 0;
	rx_used = 0;
	recv = 0;

	uart_lock = 0;

	is_init = 1;
	return 0;
}

int8_t uart_stop(struct TerminalDriver* intf)
{
	return 0;
}

int8_t uart_read(struct TerminalDriver* intf, void* buf, size_t len)
{
	size_t to_copy = rx_used < len ? rx_used : len;
	uint8_t* char_buf = (uint8_t*) buf;
	for (size_t i = 0; i < to_copy; i++)
	{
		char_buf[i] = rx_buf[rx_head++];

		if (rx_head == UART_RECV_BUF_SIZE)
			rx_head = 0;
		rx_used--;
	}
	return to_copy;
}

int8_t uart_write(struct TerminalDriver* intf, void* buf, size_t len)
{
	HAL_UART_Transmit(intf->private_data, buf, len, 1000000);
	return len;
}

int8_t uart_ioctl(struct TerminalDriver* intf, uint32_t ctlId)
{

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (rx_used < UART_RECV_BUF_SIZE)
	{
		rx_buf[rx_tail++] = recv;

		if (rx_tail == UART_RECV_BUF_SIZE)
			rx_tail = 0;
		rx_used++;
	}
	HAL_UART_Receive_IT(huart, &recv, 1);
}

struct TerminalDriverOps uart_drv_ops = {
	.start = uart_start,
	.stop = uart_stop,
	.read = uart_read,
	.write = uart_write,
	.ioctl = uart_ioctl,
};
