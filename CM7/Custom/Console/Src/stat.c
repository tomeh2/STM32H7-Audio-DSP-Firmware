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
	char print_buf[128];
	uint32_t avg_time_int;
	for (uint8_t i = 0; i < NUM_TIMERS; i++)
	{
		sprintf(print_buf, "===== TIMER %u =====", i);
		console_println(print_buf);

		sprintf(print_buf, "Name: %s", timer_list[i].name);
		console_println(print_buf);

		logger_log_timer_avg(i, &avg_time_int);
		float32_t temp = avg_time_int * 5 / 1000.f;
		sprintf(print_buf, "Avg: %f us", temp);
		console_println(print_buf);

		temp = timer_list[i].worst_time * 5 / 1000.f;
		sprintf(print_buf, "Worst: %f us", temp);
		console_println(print_buf);

		temp = timer_list[i].best_time * 5 / 1000.f;
		sprintf(print_buf, "Best: %f us", temp);
		console_println(print_buf);
	}

	console_println("");

	for (uint8_t i = 0; i < NUM_EVENTCNTRS; i++)
	{
		sprintf(print_buf, "===== EVENTS %u =====", i);
		console_println(print_buf);

		sprintf(print_buf, "Name: %s", event_list[i].name);
		console_println(print_buf);

		sprintf(print_buf, "Counter: %u", event_list[i].evnt_count);
		console_println(print_buf);
	}
}
