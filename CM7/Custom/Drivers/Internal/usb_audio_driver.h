/*
 * usb_driver.h
 *
 *  Created on: Aug 26, 2024
 *      Author: PC
 */

#ifndef INC_USB_AUDIO_DRIVER_H_
#define INC_USB_AUDIO_DRIVER_H_

#include "host_driver.h"
#include <stdint.h>

struct USBAudioClassDriverPrivate
{

};

extern struct HostInterfaceOps usb_audio_class_driver;

#endif /* INC_USB_DRIVER_H_ */
