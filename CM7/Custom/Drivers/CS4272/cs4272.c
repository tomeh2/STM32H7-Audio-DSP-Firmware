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
#include "logger.h"

#define CS4272_REG_MODE_CONTROL_1 0x01
#define CS4272_REG_DAC_CONTROL 0x02
#define CS4272_REG_DAC_VOL_MIX_CONTROL 0x03
#define CS4272_REG_DAC_CHA_VOL_CONTROL 0x04
#define CS4272_REG_DAC_CHB_VOL_CONTROL 0x05
#define CS4272_REG_ADC_CONTROL 0x06
#define CS4272_REG_MODE_CONTROL_2 0x07
#define CS4272_REG_CHIP_ID 0x08

// ================================
// MODE CONTROL REGISTER DEFINITONS
// ================================
#define MODE_CONTROL_1_INTF_FMT_MASK 0x07
#define MODE_CONTROL_1_INTF_FMT_POS 0
#define MODE_CONTROL_1_INTF_FMT_LEFT_JUSTIFIED_24BIT (0 << MODE_CONTROL_1_INTF_FMT_POS)
#define MODE_CONTROL_1_INTF_FMT_I2S_24BIT (1 << MODE_CONTROL_1_INTF_FMT_POS)
#define MODE_CONTROL_1_INTF_FMT_RIGHT_JUSTIFIED_16BIT (2 << MODE_CONTROL_1_INTF_FMT_POS)
#define MODE_CONTROL_1_INTF_FMT_RIGHT_JUSTIFIED_24BIT (3 << MODE_CONTROL_1_INTF_FMT_POS)
#define MODE_CONTROL_1_INTF_FMT_RIGHT_JUSTIFIED_20BIT (4 << MODE_CONTROL_1_INTF_FMT_POS)
#define MODE_CONTROL_1_INTF_FMT_RIGHT_JUSTIFIED_18BIT (5 << MODE_CONTROL_1_INTF_FMT_POS)

#define MODE_CONTROL_1_MASTER_SLAVE_MASK 0x01
#define MODE_CONTROL_1_MASTER_SLAVE_POS 3
#define MODE_CONTROL_1_MASTER_SLAVE_MODE_SLAVE (0 << MODE_CONTROL_1_MASTER_SLAVE_POS)
#define MODE_CONTROL_1_MASTER_SLAVE_MODE_MASTER (1 << MODE_CONTROL_1_MASTER_SLAVE_POS)

#define MODE_CONTROL_1_RATIO_MASK 0x03
#define MODE_CONTROL_1_RATIO_POS 4
#define MODE_CONTROL_1_RATIO_0 (0 << MODE_CONTROL_1_RATIO_POS)

#define MODE_CONTROL_1_FUNC_MODE_MASK 0x03
#define MODE_CONTROL_1_FUNC_MODE_POS 6
#define MODE_CONTROL_1_FUNC_MODE_SINGLE_SPEED_1 (0 << MODE_CONTROL_1_FUNC_MODE_POS)
#define MODE_CONTROL_1_FUNC_MODE_SINGLE_SPEED_2 (1 << MODE_CONTROL_1_FUNC_MODE_POS)
#define MODE_CONTROL_1_FUNC_MODE_DOUBLE_SPEED (2 << MODE_CONTROL_1_FUNC_MODE_POS)
#define MODE_CONTROL_1_FUNC_MODE_QUAD_SPEED (3 << MODE_CONTROL_1_FUNC_MODE_POS)

#define MODE_CONTROL_1_DEFAULT (MODE_CONTROL_1_INTF_FMT_I2S_24BIT |						\
								MODE_CONTROL_1_MASTER_SLAVE_MODE_SLAVE |				\
								MODE_CONTROL_1_RATIO_0 |								\
								MODE_CONTROL_1_FUNC_MODE_SINGLE_SPEED_1)

// ===============================
// DAC CONTROL REGISTER DEFINITONS
// ===============================
#define DAC_CONTROL_INVB_MASK 0x01
#define DAC_CONTROL_INVB_POS 0
#define DAC_CONTROL_INVB_OFF (0 << DAC_CONTROL_INVB_POS)
#define DAC_CONTROL_INVB_ON (1 << DAC_CONTROL_INVB_POS)

#define DAC_CONTROL_INVA_MASK 0x01
#define DAC_CONTROL_INVA_POS 1
#define DAC_CONTROL_INVA_OFF (0 << DAC_CONTROL_INVA_POS)
#define DAC_CONTROL_INVA_ON (1 << DAC_CONTROL_INVA_POS)

#define DAC_CONTROL_RMP_DN_MASK 0x01
#define DAC_CONTROL_RMP_DN_POS 2
#define DAC_CONTROL_RMP_DN_OFF (0 << DAC_CONTROL_RMP_DN_POS)
#define DAC_CONTROL_RMP_DN_ON (1 << DAC_CONTROL_RMP_DN_POS)

#define DAC_CONTROL_RMP_UP_MASK 0x01
#define DAC_CONTROL_RMP_UP_POS 3
#define DAC_CONTROL_RMP_UP_OFF (0 << DAC_CONTROL_RMP_UP_POS)
#define DAC_CONTROL_RMP_UP_ON (1 << DAC_CONTROL_RMP_UP_POS)

#define DAC_CONTROL_DEM_MASK 0x03
#define DAC_CONTROL_DEM_POS 4
#define DAC_CONTROL_DEM_DISABLED (0 << DAC_CONTROL_DEM_POS)
#define DAC_CONTROL_DEM_44K1 (1 << DAC_CONTROL_DEM_POS)
#define DAC_CONTROL_DEM_48K (2 << DAC_CONTROL_DEM_POS)
#define DAC_CONTROL_DEM_32K (3 << DAC_CONTROL_DEM_POS)

#define DAC_CONTROL_FILT_SEL_MASK 0x01
#define DAC_CONTROL_FILT_SEL_POS 6
#define DAC_CONTROL_FILT_SEL_FAST (0 << DAC_CONTROL_FILT_SEL_POS)
#define DAC_CONTROL_FILT_SEL_SLOW (1 << DAC_CONTROL_FILT_SEL_POS)

#define DAC_CONTROL_AMUTE_MASK 0x01
#define DAC_CONTROL_AMUTE_POS 7
#define DAC_CONTROL_AMUTE_OFF (0 << DAC_CONTROL_AMUTE_POS)
#define DAC_CONTROL_AMUTE_ON (1 << DAC_CONTROL_AMUTE_POS)

#define DAC_CONTROL_DEFAULT (DAC_CONTROL_INVB_OFF |										\
							DAC_CONTROL_INVA_OFF |										\
							DAC_CONTROL_RMP_DN_OFF |									\
							DAC_CONTROL_RMP_UP_OFF |									\
							DAC_CONTROL_DEM_DISABLED |									\
							DAC_CONTROL_FILT_SEL_FAST |									\
							DAC_CONTROL_AMUTE_OFF)

// =============================
// DAC VOLUME AND MIXING CONTROL
// =============================
#define DAC_VOL_MIX_CONTROL_ATAPI_MASK 0x0F
#define DAC_VOL_MIX_CONTROL_ATAPI_POS 0
#define DAC_VOL_MIX_CONTROL_ATAPI_DEFAULT (9 << DAC_VOL_MIX_CONTROL_ATAPI_POS)

#define DAC_VOL_MIX_CONTROL_SOFT_ZEROCROSS_MASK 0x03
#define DAC_VOL_MIX_CONTROL_SOFT_ZEROCROSS_POS 4
#define DAC_VOL_MIX_CONTROL_SOFT_ZEROCROSS_NONE (0 << DAC_VOL_MIX_CONTROL_SOFT_ZEROCROSS_POS)
#define DAC_VOL_MIX_CONTROL_SOFT_ZEROCROSS_ZC_ONLY (1 << DAC_VOL_MIX_CONTROL_SOFT_ZEROCROSS_POS)
#define DAC_VOL_MIX_CONTROL_SOFT_ZEROCROSS_SR_ONLY (2 << DAC_VOL_MIX_CONTROL_SOFT_ZEROCROSS_POS)
#define DAC_VOL_MIX_CONTROL_SOFT_ZEROCROSS_BOTH (3 << DAC_VOL_MIX_CONTROL_SOFT_ZEROCROSS_POS)

#define DAC_VOL_MIX_CONTROL_MATCH_VOLUME_MASK 0x01
#define DAC_VOL_MIX_CONTROL_MATCH_VOLUME_POS 6
#define DAC_VOL_MIX_CONTROL_MATCH_VOLUME_DISABLE (0 << DAC_VOL_MIX_CONTROL_MATCH_VOLUME_POS)
#define DAC_VOL_MIX_CONTROL_MATCH_VOLUME_ENABLE (1 << DAC_VOL_MIX_CONTROL_MATCH_VOLUME_POS)

#define DAC_VOL_MIX_CONTROL_DEFAULT (DAC_VOL_MIX_CONTROL_ATAPI_DEFAULT |				\
									DAC_VOL_MIX_CONTROL_SOFT_ZEROCROSS_NONE	|			\
									DAC_VOL_MIX_CONTROL_MATCH_VOLUME_ENABLE)

// ============================
// DAC CHANNEL A VOLUME CONTROL
// ============================
#define DAC_CHA_VOL_VOLUME_MASK 0x7F
#define DAC_CHA_VOL_VOLUME_POS 0
#define DAC_CHA_VOL_VOLUME_DEFAULT (0 << DAC_CHA_VOL_VOLUME_POS)

#define DAC_CHA_VOL_MUTE_MASK 0x01
#define DAC_CHA_VOL_MUTE_POS 7
#define DAC_CHA_VOL_MUTE_DEFAULT (0 << DAC_CHA_VOL_MUTE_POS)

#define DAC_CHA_VOL_DEFAULT (DAC_CHA_VOL_VOLUME_DEFAULT |								\
							 DAC_CHA_VOL_MUTE_DEFAULT)

// ============================
// DAC CHANNEL B VOLUME CONTROL
// ============================
#define DAC_CHB_VOL_VOLUME_MASK 0x7F
#define DAC_CHB_VOL_VOLUME_POS 0
#define DAC_CHB_VOL_VOLUME_DEFAULT (0 << DAC_CHB_VOL_VOLUME_POS)

#define DAC_CHB_VOL_MUTE_MASK 0x01
#define DAC_CHB_VOL_MUTE_POS 7
#define DAC_CHB_VOL_MUTE_OFF (0 << DAC_CHB_VOL_MUTE_POS)
#define DAC_CHB_VOL_MUTE_ON (1 << DAC_CHB_VOL_MUTE_POS)

#define DAC_CHB_VOL_DEFAULT (DAC_CHB_VOL_VOLUME_DEFAULT |								\
							 DAC_CHB_VOL_MUTE_OFF)

// ===========
// ADC CONTROL
// ===========
#define ADC_CONTROL_HPFDISABLEB_MASK 0x01
#define ADC_CONTROL_HPFDISABLEB_POS 0
#define ADC_CONTROL_HPFDISABLEB_OFF (0 << ADC_CONTROL_HPFDISABLEB_POS)
#define ADC_CONTROL_HPFDISABLEB_ON (1 << ADC_CONTROL_HPFDISABLEB_POS)

#define ADC_CONTROL_HPFDISABLEA_MASK 0x01
#define ADC_CONTROL_HPFDISABLEA_POS 1
#define ADC_CONTROL_HPFDISABLEA_OFF (0 << ADC_CONTROL_HPFDISABLEA_POS)
#define ADC_CONTROL_HPFDISABLEA_ON (1 << ADC_CONTROL_HPFDISABLEA_POS)

#define ADC_CONTROL_MUTEB_MASK 0x01
#define ADC_CONTROL_MUTEB_POS 2
#define ADC_CONTROL_MUTEB_OFF (0 << ADC_CONTROL_MUTEB_POS)
#define ADC_CONTROL_MUTEB_ON (1 << ADC_CONTROL_MUTEB_POS)

#define ADC_CONTROL_MUTEA_MASK 0x01
#define ADC_CONTROL_MUTEA_POS 3
#define ADC_CONTROL_MUTEA_OFF (0 << ADC_CONTROL_MUTEA_POS)
#define ADC_CONTROL_MUTEA_ON (1 << ADC_CONTROL_MUTEA_POS)

#define ADC_CONTROL_ADC_DIF_MASK 0x01
#define ADC_CONTROL_ADC_DIF_POS 4
#define ADC_CONTROL_ADC_DIF_LEFT_JUSTIFIED_24BIT (0 << ADC_CONTROL_ADC_DIF_POS)
#define ADC_CONTROL_ADC_DIF_I2S_24BIT (1 << ADC_CONTROL_ADC_DIF_POS)

#define ADC_CONTROL_DITHER16_MASK 0x01
#define ADC_CONTROL_DITHER16_POS 5
#define ADC_CONTROL_DITHER16_OFF (0 << ADC_CONTROL_DITHER16_POS)
#define ADC_CONTROL_DITHER16_ON (1 << ADC_CONTROL_DITHER16_POS)

#define ADC_CONTROL_DEFAULT (ADC_CONTROL_HPFDISABLEB_OFF |								\
							ADC_CONTROL_HPFDISABLEA_OFF |								\
							ADC_CONTROL_MUTEB_OFF |										\
							ADC_CONTROL_MUTEA_OFF |										\
							ADC_CONTROL_ADC_DIF_I2S_24BIT |								\
							ADC_CONTROL_DITHER16_OFF)

// ==============
// MODE CONTROL 2
// ==============
#define MODE_CONTROL_2_PDN_MASK 0x01
#define MODE_CONTROL_2_PDN_POS 0
#define MODE_CONTROL_2_PDN_OFF (0 << MODE_CONTROL_2_PDN_POS)
#define MODE_CONTROL_2_PDN_ON (1 << MODE_CONTROL_2_PDN_POS)

#define MODE_CONTROL_2_CPEN_MASK 0x01
#define MODE_CONTROL_2_CPEN_POS 1
#define MODE_CONTROL_2_CPEN_DISABLED (0 << MODE_CONTROL_2_CPEN_POS)
#define MODE_CONTROL_2_CPEN_ENABLED (1 << MODE_CONTROL_2_CPEN_POS)

#define MODE_CONTROL_2_FREEZE_MASK 0x01
#define MODE_CONTROL_2_FREEZE_POS 2
#define MODE_CONTROL_2_FREEZE_DISABLED (0 << MODE_CONTROL_2_FREEZE_POS)
#define MODE_CONTROL_2_FREEZE_ENABLED (1 << MODE_CONTROL_2_FREEZE_POS)

#define MODE_CONTROL_2_ABMUTEC_MASK 0x01
#define MODE_CONTROL_2_ABMUTEC_POS 3
#define MODE_CONTROL_2_ABMUTEC_DISABLED (0 << MODE_CONTROL_2_ABMUTEC_POS)
#define MODE_CONTROL_2_ABMUTEC_ENABLED (1 << MODE_CONTROL_2_ABMUTEC_POS)

#define MODE_CONTROL_2_LOOP_MASK 0x01
#define MODE_CONTROL_2_LOOP_POS 4
#define MODE_CONTROL_2_LOOP_DISABLED (0 << MODE_CONTROL_2_LOOP_POS)
#define MODE_CONTROL_2_LOOP_ENABLED (1 << MODE_CONTROL_2_LOOP_POS)

#define MODE_CONTROL_2_DEFAULT (MODE_CONTROL_2_PDN_OFF |								\
								MODE_CONTROL_2_CPEN_ENABLED |							\
								MODE_CONTROL_2_FREEZE_DISABLED |						\
								MODE_CONTROL_2_ABMUTEC_DISABLED | 						\
								MODE_CONTROL_2_LOOP_DISABLED)

// =======
// CHIP ID
// =======
#define CHIP_ID_REV_MASK 0x0F
#define CHIP_ID_REV_POS 0

#define CHIP_ID_PART_MASK 0x0F
#define CHIP_ID_PART_POS 4

#define MAX_CHANNELS 2
#define RXTX_BUFFER_SIZE (SAMPLES_PER_BLOCK * MAX_CHANNELS * 2)

static volatile int32_t tx_buf[RXTX_BUFFER_SIZE] __attribute__((section(".i2s_tx")));
static volatile int32_t rx_buf[RXTX_BUFFER_SIZE] __attribute__((section(".i2s_rx")));;
static volatile int32_t* inactive_tx_buf = tx_buf;
static volatile int32_t* inactive_rx_buf = rx_buf;

static uint8_t is_running = 0;

static char* module_name = "[CS4272]";

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

void cs4272_write_register(struct CS4272_PrivateData* pd, uint8_t reg_addr, uint8_t val)
{
	uint16_t addr = 0x0022;
	uint8_t data[2];
	data[0] = reg_addr;
	data[1] = val;

	HAL_I2C_Master_Transmit(pd->i2c_hndl, addr, data, 2, 100);
}

void cs4272_init_regs(struct CS4272_PrivateData* pd)
{
		cs4272_write_register(pd, CS4272_REG_MODE_CONTROL_2, MODE_CONTROL_2_DEFAULT);
		cs4272_write_register(pd, CS4272_REG_MODE_CONTROL_1, MODE_CONTROL_1_DEFAULT);
		cs4272_write_register(pd, CS4272_REG_DAC_CONTROL, DAC_CONTROL_DEFAULT);
		cs4272_write_register(pd, CS4272_REG_DAC_VOL_MIX_CONTROL, DAC_VOL_MIX_CONTROL_DEFAULT);
		cs4272_write_register(pd, CS4272_REG_DAC_CHA_VOL_CONTROL, DAC_CHA_VOL_DEFAULT);
		cs4272_write_register(pd, CS4272_REG_DAC_CHB_VOL_CONTROL, DAC_CHB_VOL_DEFAULT);
		cs4272_write_register(pd, CS4272_REG_ADC_CONTROL, ADC_CONTROL_DEFAULT);
}

int8_t cs4272_start(struct AudioDriver* intf)
{
	if (is_running)
	{
		logger_printf(DEBUG_LEVEL_WARNING, "%s Tried to initialize initialized driver\n\r", module_name);
		return -EINVAL;
	}

	if (!intf->private_data)
	{
		logger_printf(DEBUG_LEVEL_ERROR, "%s Tried to initialize driver without passing i2c and i2s handles (private_data is NULL)\n\r", module_name);
		return -EINVAL;
	}

	logger_printf(DEBUG_LEVEL_INFO, "%s Resetting codec...\n\r", module_name);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);
	logger_printf(DEBUG_LEVEL_INFO, "%s Reset done\n\r", module_name);

	struct CS4272_PrivateData* pd = intf->private_data;

	if (!pd->i2c_hndl || !pd->i2s_hndl)
		return -EINVAL;

	memset(tx_buf, 0, sizeof(uint32_t) * RXTX_BUFFER_SIZE);
	memset(rx_buf, 0, sizeof(uint32_t) * RXTX_BUFFER_SIZE);

	HAL_I2S_RegisterCallback(pd->i2s_hndl, HAL_I2S_TX_RX_HALF_COMPLETE_CB_ID, cs4272_dma_half_cmpl_callback);
	HAL_I2S_RegisterCallback(pd->i2s_hndl, HAL_I2S_TX_RX_COMPLETE_CB_ID, cs4272_dma_cmpl_callback);

	HAL_I2SEx_TransmitReceive_DMA(pd->i2s_hndl, tx_buf, rx_buf, RXTX_BUFFER_SIZE);
	logger_printf(DEBUG_LEVEL_INFO, "%s DMA started\n\r", module_name);

	logger_printf(DEBUG_LEVEL_INFO, "%s Configuring codec...\n\r", module_name);
	cs4272_init_regs(pd);

	logger_printf(DEBUG_LEVEL_INFO, "%s Configuration done\n\r", module_name);

	is_running = 1;

	logger_printf(DEBUG_LEVEL_INFO, "%s Initialization done\n\r", module_name);
	return EOK;
}

int8_t cs4272_stop(struct AudioDriver* intf)
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

int8_t cs4272_read(struct AudioDriver* intf, float* buf, size_t len)
{
	return EOK;
}

int8_t cs4272_write(struct AudioDriver* intf, float* buf, size_t len)
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

int8_t cs4272_ioctl(struct AudioDriver* intf, uint32_t ctl_id)
{
	if (!is_running)
		return -EINVAL;
	return 0;
}

struct AudioDriverOps cs4272_ops = {
	.start = cs4272_start,
	.stop = cs4272_stop,
	.read = cs4272_read,
	.write = cs4272_write,
	.ioctl = cs4272_ioctl,
};
