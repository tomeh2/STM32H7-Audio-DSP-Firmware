/*
 * driver_manager.h
 *
 *  Created on: Aug 6, 2024
 *      Author: PC
 */

#ifndef INC_DRIVER_MANAGER_H_
#define INC_DRIVER_MANAGER_H_

#include "host_driver.h"
#include "interface.h"

#define MAX_DRIVERS 8

extern size_t registered_drivers;
extern struct Interface** driver_list;

extern struct Interface* audio_device;
extern struct Interface* serial_device;
extern struct HostInterface* usb_device;

extern void drvman_init();
extern void drvman_register_driver(struct Interface* driver);
extern void drvman_set_serial_driver(uint8_t driver_id);
extern void drvman_set_audio_driver(uint8_t driver_id);
extern void drvman_set_usb_driver(struct HostInterface* driver);

#endif /* INC_DRIVER_MANAGER_H_ */
