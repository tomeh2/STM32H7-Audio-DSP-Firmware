#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include <stddef.h>
#include <stdint.h>

struct InterfaceOperations;

struct Interface
{
	char* name;
	struct InterfaceOperations* io_ops;
	void* private_data;
};

struct InterfaceOperations
{
	int8_t (*start)(struct Interface* intf);
	int8_t (*stop)(struct Interface* intf);
	int8_t (*read)(struct Interface* intf, void* buf, size_t len);
	int8_t (*write)(struct Interface* intf, void* buf, size_t len);
	int8_t (*ioctl)(struct Interface* intf, uint32_t ctl_id);
};

#endif
