/*
 * driver_manager.h
 *
 *  Created on: Aug 6, 2024
 *      Author: PC
 */

#ifndef INC_DRIVER_MANAGER_H_
#define INC_DRIVER_MANAGER_H_

#include "host_driver.h"
#include "audio_driver.h"
#include "terminal_driver.h"

extern struct AudioDriver* audio_device;
extern struct TerminalDriver* serial_device;
extern struct HostDriver* host_device;

extern void drvman_init();
extern void drvman_set_terminal_driver(struct TerminalDriver* driver);
extern void drvman_set_audio_driver(struct AudioDriver* driver);
extern void drvman_set_host_driver(struct HostDriver* driver);

#endif /* INC_DRIVER_MANAGER_H_ */
