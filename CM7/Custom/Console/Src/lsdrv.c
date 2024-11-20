/*
 * lsdrv.c
 *
 *  Created on: Aug 20, 2024
 *      Author: PC
 */

#include <stdint.h>
#include <stdio.h>

#include "driver_manager.h"
#include "console.h"

void lsdrv(char** args, uint8_t argc)
{
	for (uint8_t i = 0; i < registered_drivers; i++)
	{
		console_printf("===== DRIVER %u =====\n\r");
		console_printf("Name: %s\n\r", driver_list[i]->name);
	}

	console_printf("Serial Driver: %s\n\r", serial_device->name);
	console_printf("Audio Driver: %s\n\r", audio_device->name);
	console_printf("USB Driver: %s\n\r", usb_device->name);
}
