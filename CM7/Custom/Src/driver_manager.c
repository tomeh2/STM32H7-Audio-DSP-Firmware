/*
 * driver_manager.c
 *
 *  Created on: Aug 6, 2024
 *      Author: PC
 */

#include "driver_manager.h"
#include "console.h"

#include <string.h>

static char module_str[] = "[Driver Manager]";

size_t registered_drivers;
struct Interface* drivers[MAX_DRIVERS];
struct Interface** driver_list = drivers;

struct Interface* audio_device = NULL;
struct Interface* serial_device = NULL;
struct HostInterface* usb_device = NULL;

void drvman_init()
{
	registered_drivers = 0;

	for (size_t i = registered_drivers; i < MAX_DRIVERS; i++)
		drivers[i] = NULL;

	audio_device = NULL;
	serial_device = NULL;
	usb_device = NULL;
}

void drvman_register_driver(struct Interface* driver)
{
	if (!driver)
	{
		console_printf("%s Tried to register a NULL driver\n\r", module_str);
		return;
	}

	if (registered_drivers < MAX_DRIVERS)
	{
		drivers[registered_drivers++] = driver;

		console_printf("%s Registered driver: %s\n\r", module_str, driver->name);
	}
	else
	{
		console_printf("%s No free driver slots\n\r", module_str);
	}
}

void drvman_set_serial_driver(uint8_t driver_id)
{
	if (driver_id >= MAX_DRIVERS)
	{
		console_printf("%s Serial driver ID out of range\n\r", module_str);
		return;
	}

	if (!drivers[driver_id])
	{
		console_printf("%s Target serial driver is NULL\n\r", module_str);
		return;
	}

	serial_device = drivers[driver_id];
	serial_device->io_ops->start(serial_device);

	console_printf("%s Set serial driver: %s\n\r", module_str, serial_device->name);
}

void drvman_set_audio_driver(uint8_t driver_id)
{
	if (driver_id >= MAX_DRIVERS)
	{
		console_printf("%s Audio driver ID out of range\n\r", module_str);
		return;
	}

	if (!drivers[driver_id])
	{
		console_printf("%s Target audio driver is NULL\n\r", module_str);
		return;
	}

	audio_device = drivers[driver_id];
	audio_device->io_ops->start(audio_device);

	console_printf("%s Set audio driver: %s\n\r", module_str, drivers[driver_id]->name);
}

void drvman_set_usb_driver(struct HostInterface* driver)
{
	if (!driver)
	{
		console_printf("%s Target USB driver is NULL\n\r", module_str);
		return;
	}

	usb_device = driver;
	usb_device->io_ops->start(usb_device);

	console_printf("%s Set USB driver: %s\n\r", module_str, driver->name);
}
