/*
 * stat.c
 *
 *  Created on: Aug 5, 2024
 *      Author: PC
 */

#include "stat.h"
#include "console.h"
#include "logger.h"
#include "arm_math.h"

void stat(char** args, uint8_t argc)
{
	uint32_t avg_time_int;
	for (uint8_t i = 0; i < NUM_TIMERS; i++)
	{
		console_printf("===== TIMER %u =====\n\r", i);
		console_printf("Name: %s\n\r", timer_list[i].name);

		logger_log_timer_avg(i, &avg_time_int);
		float32_t temp = avg_time_int * 5 / 1000.f;
		console_printf("Avg: %f us\n\r", temp);

		temp = timer_list[i].worst_time * 5 / 1000.f;
		console_printf("Worst: %f us\n\r", temp);

		temp = timer_list[i].best_time * 5 / 1000.f;
		console_printf("Best: %f us\n\r", temp);
	}

	console_printf("");

	for (uint8_t i = 0; i < NUM_EVENTCNTRS; i++)
	{
		console_printf("===== EVENTS %u =====\n\r", i);
		console_printf("Name: %s\n\r", event_list[i].name);
		console_printf("Counter: %u\n\r", event_list[i].evnt_count);
	}
}
