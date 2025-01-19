/*
 * logger.h
 *
 *  Created on: Aug 21, 2024
 *      Author: PC
 */

#ifndef INC_LOGGER_H_
#define INC_LOGGER_H_

#include <stdint.h>
#include "stm32h7xx_hal.h"

#define MEASUREMENTS_PER_TIMER 64
#define NUM_TIMERS 8

#define NUM_EVENTCNTRS 8

#ifdef ENABLE_LOGGING
	#define LOG_TIME_START(timer_id) {logger_log_timer_start(timer_id);}
	#define LOG_TIME_STOP(timer_id) {logger_log_timer_stop(timer_id);}
#else
	#define LOG_TIME_START(timer_id) ;
	#define LOG_TIME_STOP(timer_id) ;
#endif

#define DEBUG_LEVELS 4
#define DEBUG_LEVEL_INFO 0
#define DEBUG_LEVEL_WARNING 1
#define DEBUG_LEVEL_ERROR 2
#define DEBUG_LEVEL_CRITICAL 3

struct LogTimer
{
	char* name;
	uint8_t head;
	uint32_t measurements[MEASUREMENTS_PER_TIMER];
	uint32_t worst_time;
	uint32_t best_time;
	uint32_t last_start;
};

struct LogEvent
{
	char* name;
	uint32_t evnt_count;
};

extern struct LogTimer* timer_list;
extern struct LogEvent* event_list;

int8_t logger_init(TIM_HandleTypeDef* htim);
int8_t logger_timer_set_name(uint8_t timer_id, char* name);
int8_t logger_log_timer_start(uint8_t timer_id);
int8_t logger_log_timer_stop(uint8_t timer_id);
int8_t logger_log_timer_avg(uint8_t timer_id, uint32_t* avg_time);
int8_t logger_event_set_name(uint8_t event_id, char* name);
int8_t logger_event_increment(uint8_t event_id);
void logger_printf(uint8_t level, char* fmt, ...);

#endif /* INC_LOGGER_H_ */
