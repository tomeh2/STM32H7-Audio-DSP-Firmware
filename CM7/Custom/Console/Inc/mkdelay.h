/*
 * mkdelay.h
 *
 *  Created on: Aug 9, 2024
 *      Author: PC
 */

#ifndef CONSOLE_INC_MKDELAY_H_
#define CONSOLE_INC_MKDELAY_H_

#include <stdint.h>

void mkdelay(char** args, uint8_t argc);
void delayline_tap_delay(char** args, uint8_t argc);
void delayline_tap_volume(char** args, uint8_t argc);
void delayline_fb_volume(char** args, uint8_t argc);

#endif /* CONSOLE_INC_MKDELAY_H_ */
