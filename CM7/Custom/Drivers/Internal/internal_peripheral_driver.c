#include "internal_peripheral_driver.h"
#include "audio_defs.h"

#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE (SAMPLES_PER_BLOCK * 2)

static uint8_t is_running = 0;

static uint16_t tx_buf[BUFFER_SIZE];
static uint16_t* inactive_tx_buf;

void intper_dma_half_cmpl_callback()
{
	temp_next_block_ready = 1;

	inactive_tx_buf = &tx_buf[0];
}

void intper_dma_cmpl_callback()
{
	temp_next_block_ready = 1;

	inactive_tx_buf = &tx_buf[BUFFER_SIZE / 2];
}

int32_t intper_start(struct Interface* intf)
{
	if (is_running)
		return -EINVAL;

	if (!intf->private_data)
		return -EINVAL;
	struct IntPerDrvPrivateData* private_data = intf->private_data;

	if (!private_data->hdac || !private_data->htim)
		return -EINVAL;

	memset(tx_buf, 0, sizeof(uint16_t) * BUFFER_SIZE);
	inactive_tx_buf = &tx_buf[SAMPLES_PER_BLOCK];

	HAL_DAC_RegisterCallback(private_data->hdac, HAL_DAC_CH1_HALF_COMPLETE_CB_ID, intper_dma_half_cmpl_callback);
	HAL_DAC_RegisterCallback(private_data->hdac, HAL_DAC_CH1_COMPLETE_CB_ID, intper_dma_cmpl_callback);

	HAL_DAC_Start_DMA(private_data->hdac,
		DAC_CHANNEL_1,
		tx_buf,
		SAMPLES_PER_BLOCK * 2, DAC_ALIGN_12B_R);

	HAL_TIM_Base_Start(private_data->htim);
	is_running = 1;
}

int8_t intper_stop(struct Interface* intf)
{
	if (!intf->private_data)
		return -EINVAL;
	struct IntPerDrvPrivateData* private_data = intf->private_data;

	if (!private_data->hdac || !private_data->htim)
		return -EINVAL;

	HAL_DAC_Stop_DMA(private_data->hdac, DAC_CHANNEL_1);
	HAL_TIM_Base_Stop(private_data->htim);

	is_running = 0;
}

int32_t intper_read(struct Interface* intf, void* buf, size_t len)
{
	return 0;
}

int32_t intper_write(struct Interface* intf, void* buf, size_t len)
{
	if (!is_running)
		return -EINVAL;
	if (len < SAMPLES_PER_BLOCK)
		return -ERBUFUDF;
	if (len > SAMPLES_PER_BLOCK)
		return -ERBUFOVF;
	float* buf_float = (float*) buf;

	for (size_t i = 0; i < SAMPLES_PER_BLOCK; i++)
	{
		uint16_t sample = (uint16_t)((buf_float[i] + 1.f) * 2048.f);
		inactive_tx_buf[i] = (uint16_t) sample;
	}
	return 0;
}

int32_t intper_ioctl(struct Interface* intf, uint32_t ctl_id)
{
	if (!is_running)
		return -EINVAL;
	return 0;
}

struct InterfaceOperations int_per_drv_ops = {
	.start = intper_start,
	.stop = intper_stop,
	.read = intper_read,
	.write = intper_write,
	.ioctl = intper_ioctl,
};
