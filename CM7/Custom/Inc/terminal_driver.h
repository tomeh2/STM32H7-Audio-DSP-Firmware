/*
 * communication_driver.h
 *
 *  Created on: Jan 19, 2025
 *      Author: PC
 */

#ifndef INC_TERMINAL_DRIVER_H_
#define INC_TERMINAL_DRIVER_H_

#include <stddef.h>
#include <stdint.h>

struct TerminalDriverOps;

struct TerminalDriver
{
	char* name;
	struct TerminalDriverOps* io_ops;
	void* private_data;
};

struct TerminalDriverOps
{
	int8_t (*start)(struct TerminalDriver* intf);
	int8_t (*stop)(struct TerminalDriver* intf);
	int8_t (*read)(struct TerminalDriver* intf, char* buf, size_t len);
	int8_t (*write)(struct TerminalDriver* intf, char* buf, size_t len);
	int8_t (*ioctl)(struct TerminalDriver* intf, uint32_t ctl_id);
};

#endif /* INC_TERMINAL_DRIVER_H_ */
