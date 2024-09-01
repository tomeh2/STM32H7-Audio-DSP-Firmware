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
	char print_buf[128];

	for (uint8_t i = 0; i < registered_drivers; i++)
	{
		sprintf(print_buf, "===== DRIVER %u =====");
		console_println(print_buf);
		sprintf(print_buf, "Name: %s", driver_list[i]->name);
		console_println(print_buf);
	}

	console_println("");
	sprintf(print_buf, "Serial Driver: %s", serial_device->name);
	console_println(print_buf);
	sprintf(print_buf, "Audio Driver: %s", audio_device->name);
	console_println(print_buf);
	sprintf(print_buf, "USB Driver: %s", usb_device->name);
	console_println(print_buf);
}
