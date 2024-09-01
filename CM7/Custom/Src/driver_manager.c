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
struct Interface* usb_device = NULL;

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
	char print_buf[128];
	if (!driver)
	{
		sprintf(print_buf, "%s Tried to register a NULL driver", module_str);
		console_println(print_buf);
		return;
	}

	if (registered_drivers < MAX_DRIVERS)
	{
		drivers[registered_drivers++] = driver;

		sprintf(print_buf, "%s Registered driver: %s", module_str, driver->name);
		console_println(print_buf);
	}
	else
	{
		sprintf(print_buf, "%s No free driver slots", module_str);
		console_println(print_buf);
	}
}

void drvman_set_serial_driver(uint8_t driver_id)
{
	char print_buf[128];
	if (driver_id >= MAX_DRIVERS)
	{
		sprintf(print_buf, "%s Serial driver ID out of range", module_str);
		console_println(print_buf);
		return;
	}

	if (!drivers[driver_id])
	{
		sprintf(print_buf, "%s Target serial driver is NULL", module_str);
		console_println(print_buf);
		return;
	}

	serial_device = drivers[driver_id];
	serial_device->io_ops->start(serial_device);

	sprintf(print_buf, "%s Set serial driver: %s", module_str, serial_device->name);
	console_println(print_buf);
}

void drvman_set_audio_driver(uint8_t driver_id)
{
	char print_buf[128];
	if (driver_id >= MAX_DRIVERS)
	{
		sprintf(print_buf, "%s Audio driver ID out of range", module_str);
		console_println(print_buf);
		return;
	}

	if (!drivers[driver_id])
	{
		sprintf(print_buf, "%s Target audio driver is NULL", module_str);
		console_println(print_buf);
		return;
	}

	audio_device = drivers[driver_id];
	audio_device->io_ops->start(audio_device);

	sprintf(print_buf, "%s Set audio driver: %s", module_str, drivers[driver_id]->name);
	console_println(print_buf);
}

void drvman_set_usb_driver(uint8_t driver_id)
{
	char print_buf[128];
	if (driver_id >= MAX_DRIVERS)
	{
		sprintf(print_buf, "%s USB ID out of range", module_str);
		console_println(print_buf);
		return;
	}

	if (!drivers[driver_id])
	{
		sprintf(print_buf, "%s Target USB driver is NULL", module_str);
		console_println(print_buf);
		return;
	}

	usb_device = drivers[driver_id];
	usb_device->io_ops->start(usb_device);

	sprintf(print_buf, "%s Set USB driver: %s", module_str, drivers[driver_id]->name);
	console_println(print_buf);
}
