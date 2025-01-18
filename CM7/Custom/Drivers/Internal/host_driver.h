/*
 * host_driver.h
 *
 *  Created on: Jan 15, 2025
 *      Author: PC
 */

#ifndef DRIVERS_INTERNAL_HOST_DRIVER_H_
#define DRIVERS_INTERNAL_HOST_DRIVER_H_

/*
 * Host driver represents a communication interface between the device and the host(ex. PC)
 */

#include <stddef.h>
#include <stdint.h>

struct HostInterfaceOps;

struct HostInterface
{
	char* name;
	struct HostInterfaceOps* io_ops;
	void* private_data;
};

struct HostInterfaceOps
{
	int8_t (*start)(struct HostInterface* intf);
	int8_t (*stop)(struct HostInterface* intf);
	int8_t (*host_data_read)(struct HostInterface* intf, char* buf, size_t len);
	int8_t (*host_data_write)(struct HostInterface* intf, char* buf, size_t len);
	int8_t (*dev_data_read)(struct HostInterface* intf, float* buf, size_t len);
	int8_t (*dev_data_write)(struct HostInterface* intf, float* buf, size_t len);
	int8_t (*ioctl)(struct HostInterface* intf, uint32_t ctl_id);
};

#endif /* DRIVERS_INTERNAL_HOST_DRIVER_H_ */
