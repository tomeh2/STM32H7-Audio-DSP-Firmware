/*
 * driver_manager.c
 *
 *  Created on: Aug 6, 2024
 *      Author: PC
 */

#include "driver_manager.h"
#include "logger.h"

#include <string.h>

static char module_str[] = "[Driver Manager]";

struct AudioDriver* audio_device = NULL;
struct TerminalDriver* serial_device = NULL;
struct HostDriver* host_device = NULL;

void drvman_init()
{
	audio_device = NULL;
	serial_device = NULL;
	host_device = NULL;

	logger_printf(DEBUG_LEVEL_INFO, "%s Initialization finished", module_str);
}

void drvman_set_terminal_driver(struct TerminalDriver* driver)
{
	if (!driver)
	{
		logger_printf(DEBUG_LEVEL_ERROR, "%s Tried to set NULL as terminal driver", module_str);
		return;
	}

	serial_device = driver;
	serial_device->io_ops->start(serial_device);

	logger_printf(DEBUG_LEVEL_INFO, "%s Terminal driver set to: %s\n\r", module_str, serial_device->name);
}

void drvman_set_audio_driver(struct AudioDriver* driver)
{
	if (!driver)
	{
		logger_printf(DEBUG_LEVEL_ERROR, "%s Tried to set NULL as audio driver", module_str);
		return;
	}

	audio_device = driver;
	audio_device->io_ops->start(audio_device);

	logger_printf(DEBUG_LEVEL_INFO, "%s Audio driver set to: %s\n\r", module_str, audio_device->name);
}

void drvman_set_host_driver(struct HostDriver* driver)
{
	if (!driver)
	{
		logger_printf(DEBUG_LEVEL_ERROR, "%s Tried to set NULL as host driver\n\r", module_str);
		return;
	}

	host_device = driver;
	host_device->io_ops->start(host_device);

	logger_printf(DEBUG_LEVEL_INFO, "%s Host driver set to: %s\n\r", module_str, host_device->name);
}
