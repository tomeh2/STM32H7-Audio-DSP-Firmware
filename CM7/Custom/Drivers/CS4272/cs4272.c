/*
 * cs4272.c
 *
 *  Created on: Aug 18, 2024
 *      Author: PC
 */

#include "cs4272.h"
#include "audio_defs.h"
#include "arm_math.h"
#include "stm32h7xx_hal.h"

#define MAX_CHANNELS 2
#define RXTX_BUFFER_SIZE (SAMPLES_PER_BLOCK * MAX_CHANNELS * 2)

static int32_t tx_buf[RXTX_BUFFER_SIZE] __attribute__((section(".i2s_tx")));
static int32_t rx_buf[RXTX_BUFFER_SIZE] __attribute__((section(".i2s_rx")));;
static int32_t* inactive_tx_buf = tx_buf;
static int32_t* inactive_rx_buf = rx_buf;

static uint8_t is_running = 0;

void cs4272_dma_half_cmpl_callback()
{
	temp_next_block_ready = 1;

	inactive_tx_buf = &tx_buf[0];
}

void cs4272_dma_cmpl_callback()
{
	temp_next_block_ready = 1;

	inactive_tx_buf = &tx_buf[RXTX_BUFFER_SIZE / 2];
}

int8_t cs4272_start(struct Interface* intf)
{
	if (is_running)
		return -EINVAL;

	if (!intf->private_data)
		return -EINVAL;

	struct CS4272_PrivateData* pd = intf->private_data;

	if (!pd->i2c_hndl || !pd->i2s_hndl)
		return -EINVAL;

	memset(tx_buf, 0, sizeof(uint32_t) * RXTX_BUFFER_SIZE);
	memset(rx_buf, 0, sizeof(uint32_t) * RXTX_BUFFER_SIZE);

	HAL_I2S_RegisterCallback(pd->i2s_hndl, HAL_I2S_TX_RX_HALF_COMPLETE_CB_ID, cs4272_dma_half_cmpl_callback);
	HAL_I2S_RegisterCallback(pd->i2s_hndl, HAL_I2S_TX_RX_COMPLETE_CB_ID, cs4272_dma_cmpl_callback);

	HAL_I2SEx_TransmitReceive_DMA(pd->i2s_hndl, tx_buf, rx_buf, RXTX_BUFFER_SIZE);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);

	uint16_t addr = 0x0022;
	uint8_t wr_data[2];
	// Configure CODEC
	wr_data[0] = 0x07;
	wr_data[1] = 0x02;
	HAL_I2C_Master_Transmit(pd->i2c_hndl, addr, wr_data, 2, 10000);

	wr_data[0] = 0x01;
	wr_data[1] = 0x01;
	HAL_I2C_Master_Transmit(pd->i2c_hndl, addr, wr_data, 2, 10000);

	wr_data[0] = 0x02;
	wr_data[1] = 0x00;
	HAL_I2C_Master_Transmit(pd->i2c_hndl, addr, wr_data, 2, 10000);

	wr_data[0] = 0x03;
	wr_data[1] = 0x29;
	HAL_I2C_Master_Transmit(pd->i2c_hndl, addr, wr_data, 2, 10000);

	wr_data[0] = 0x04;
	wr_data[1] = 0x00;
	HAL_I2C_Master_Transmit(pd->i2c_hndl, addr, wr_data, 2, 10000);

	wr_data[0] = 0x05;
	wr_data[1] = 0x00;
	HAL_I2C_Master_Transmit(pd->i2c_hndl, addr, wr_data, 2, 10000);

	wr_data[0] = 0x06;
	wr_data[1] = 0x00;
	HAL_I2C_Master_Transmit(pd->i2c_hndl, addr, wr_data, 2, 10000);

	is_running = 1;

	return EOK;
}

int8_t cs4272_stop(struct Interface* intf)
{
	if (!is_running)
		return -EINVAL;

	struct CS4272_PrivateData* pd = intf->private_data;

	if (!pd->i2c_hndl || !pd->i2s_hndl)
		return -EINVAL;

	HAL_I2S_DMAStop(pd->i2s_hndl);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_I2S_UnRegisterCallback(pd->i2s_hndl, HAL_I2S_TX_RX_HALF_COMPLETE_CB_ID);
	HAL_I2S_UnRegisterCallback(pd->i2s_hndl, HAL_I2S_TX_RX_COMPLETE_CB_ID);

	return EOK;
}

int8_t cs4272_read(struct Interface* intf, void* buf, size_t len)
{
	return EOK;
}

int8_t cs4272_write(struct Interface* intf, void* buf, size_t len)
{
	if (!is_running)
		return -EINVAL;
	if (len < SAMPLES_PER_BLOCK)
		return -ERBUFUDF;
	if (len > SAMPLES_PER_BLOCK)
		return -ERBUFOVF;

	float32_t* chl_buf = &((float32_t*)buf)[0];
	float32_t* chr_buf = &((float32_t*)buf)[SAMPLES_PER_BLOCK];
	int32_t ch_buf_index = 0;
	int32_t tx_buf_index = 0;

	while (tx_buf_index < RXTX_BUFFER_SIZE >> 1)
	{
		inactive_tx_buf[tx_buf_index] = (int32_t)((chl_buf[ch_buf_index]) * 8388607);
		inactive_tx_buf[tx_buf_index + 1] = (int32_t)((chr_buf[ch_buf_index]) * 8388607);
		inactive_tx_buf[tx_buf_index + 2] = (int32_t)((chl_buf[ch_buf_index + 1]) * 8388607);
		inactive_tx_buf[tx_buf_index + 3] = (int32_t)((chr_buf[ch_buf_index + 1]) * 8388607);

		tx_buf_index += 4;
		ch_buf_index += 2;
	}
}

int8_t cs4272_ioctl(struct Interface* intf, uint32_t ctl_id)
{
	if (!is_running)
		return -EINVAL;
	return 0;
}

struct InterfaceOperations cs4272_ops = {
	.start = cs4272_start,
	.stop = cs4272_stop,
	.read = cs4272_read,
	.write = cs4272_write,
	.ioctl = cs4272_ioctl,
};
