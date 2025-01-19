/*
 * logger.c
 *
 *  Created on: Aug 21, 2024
 *      Author: PC
 */

#include "logger.h"
#include "stm32h7xx_hal.h"
#include "audio_defs.h"
#include "console.h"
#include <stdarg.h>

struct LogEvent events[NUM_EVENTCNTRS];
struct LogEvent* event_list = events;

struct LogTimer timers[NUM_TIMERS];
struct LogTimer* timer_list = timers;

TIM_HandleTypeDef* tim_hndl = NULL;

char* DEBUG_LEVEL_STRINGS[5] = {
		"[INFO]",
		"[WARNING]",
		"[ERROR]",
		"[CRITICAL]",
		"[UNKNOWN]"
};

int8_t logger_init(TIM_HandleTypeDef* htim)
{
	if (!htim)
		return -EINVAL;

	tim_hndl = htim;

	for (uint8_t i = 0; i < NUM_TIMERS; i++)
	{
		timers[i].head = 0;
		timers[i].last_start = 0;

		for (uint8_t j = 0; j < MEASUREMENTS_PER_TIMER; j++)
			timers[i].measurements[j] = 0;

		timers[i].name = "";
		timers[i].worst_time = 0;
		timers[i].best_time = 0xFFFFFFFF;
	}

	for (uint8_t i = 0; i < NUM_EVENTCNTRS; i++)
	{
		events[i].name = "";
		events[i].evnt_count = 0;
	}
	HAL_TIM_Base_Start(tim_hndl);
}

int8_t logger_timer_set_name(uint8_t timer_id, char* name)
{
	if (timer_id >= NUM_TIMERS)
		return -EINVAL;

	timers[timer_id].name = name;
	return EOK;
}

int8_t logger_log_timer_start(uint8_t timer_id)
{
	if (timer_id >= NUM_TIMERS)
		return -EINVAL;

	if (!tim_hndl)
		return -EINVAL;

	timers[timer_id].last_start = tim_hndl->Instance->CNT;

	return EOK;
}

int8_t logger_log_timer_stop(uint8_t timer_id)
{
	if (timer_id >= NUM_TIMERS)
		return -EINVAL;

	if (!tim_hndl)
		return -EINVAL;

	uint32_t time_stop = tim_hndl->Instance->CNT;
	uint32_t measured_time;
	if (time_stop < timers[timer_id].last_start)
		measured_time = 0xFFFFFFFF - timers[timer_id].last_start + time_stop;
	else
		measured_time = time_stop - timers[timer_id].last_start;

	timers[timer_id].measurements[timers[timer_id].head++] = measured_time;
	if (timers[timer_id].head >= MEASUREMENTS_PER_TIMER)
		timers[timer_id].head = 0;

	if (measured_time > timers[timer_id].worst_time)
		timers[timer_id].worst_time = measured_time;

	if (measured_time < timers[timer_id].best_time)
		timers[timer_id].best_time = measured_time;

	return EOK;
}

int8_t logger_log_timer_avg(uint8_t timer_id, uint32_t* avg_time)
{
	if (timer_id >= NUM_TIMERS)
		return -EINVAL;

	if (!tim_hndl)
		return -EINVAL;

	if (!avg_time)
		return -EINVAL;

	*avg_time = 0;

	uint64_t avg_sum = 0;
	for (uint8_t i = 0; i < MEASUREMENTS_PER_TIMER; i++)
	{
		avg_sum += timers[timer_id].measurements[i];
	}
	*avg_time = avg_sum / MEASUREMENTS_PER_TIMER;

	return EOK;
}

int8_t logger_event_set_name(uint8_t event_id, char* name)
{
	if (event_id >= NUM_EVENTCNTRS)
		return -EINVAL;

	events[event_id].name = name;

	return EOK;
}

int8_t logger_event_increment(uint8_t event_id)
{
	if (event_id >= NUM_EVENTCNTRS)
		return -EINVAL;

	events[event_id].evnt_count++;

	return EOK;
}

void logger_printf(uint8_t level, char* fmt, ...)
{
	if (level >= DEBUG_LEVELS)
		level = 4;

	char temp[256];
	snprintf(temp, 256, "%s %s", DEBUG_LEVEL_STRINGS[level], fmt);

	va_list argptr;
	va_start(argptr, fmt);
	console_vsprintf(temp, argptr);
	va_end(argptr);
}
