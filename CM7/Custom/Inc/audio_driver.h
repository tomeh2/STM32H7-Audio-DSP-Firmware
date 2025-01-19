/*
 * audio_interface.h
 *
 *  Created on: Jan 19, 2025
 *      Author: PC
 */

#ifndef INC_AUDIO_DRIVER_H_
#define INC_AUDIO_DRIVER_H_

/*
 * Host driver represents a communication interface between the device and the audio hardware (ex. external CODEC)
 */

#include <stddef.h>
#include <stdint.h>

struct AudioDriverOps;

struct AudioDriver
{
	char* name;
	struct AudioDriverOps* io_ops;
	void* private_data;
};

struct AudioDriverOps
{
	int8_t (*start)(struct AudioDriver* intf);
	int8_t (*stop)(struct AudioDriver* intf);
	int8_t (*read)(struct AudioDriver* intf, float* buf, size_t len);
	int8_t (*write)(struct AudioDriver* intf, float* buf, size_t len);
	int8_t (*ioctl)(struct AudioDriver* intf, uint32_t ctl_id);
};

#endif /* INC_AUDIO_DRIVER_H_ */
