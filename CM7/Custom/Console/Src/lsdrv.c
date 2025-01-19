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
	console_printf("Serial Driver: %s\n\r", serial_device->name);
	console_printf("Audio Driver: %s\n\r", audio_device->name);
	console_printf("Host Driver: %s\n\r", host_device->name);
}
