/*
 * parameter.c
 *
 *  Created on: Sep 9, 2024
 *      Author: PC
 */

#include "parameter.h"
#include "audio_defs.h"

#include <stdio.h>

#define PTYPE_COEFF_UNIT ""
#define PTYPE_FREQ_UNIT "Hz"
#define PTYPE_DELAY_UNIT "Samples"
#define PTYPE_PHASE_UNIT "Rad"
#define PTYPE_OTHER_UNIT ""

char param_str[128];

int8_t parameter_init(struct Parameter* param, uint8_t id, char* name, enum ParameterType type, float32_t min, float32_t max, float32_t init_value)
{
	param->name = name;
	param->id = id;
	param->type = type;
	param->min = min;
	param->max = max;
	param->value = init_value;
}

int8_t parameter_set(struct Parameter* param, float32_t value)
{
	if (!param)
		return -EINVAL;

	if (value < param->min)
		return -EINVAL;

	if (value > param->max)
		return -EINVAL;

	param->value = value;
	return EOK;
}

char* parameter_tostr(struct Parameter* param)
{
	if (!param)
		return NULL;

	char* unit = PTYPE_OTHER_UNIT;
	switch (param->type)
	{
	case PARAM_TYPE_COEFF:
		unit = PTYPE_COEFF_UNIT;
		break;
	case PARAM_TYPE_FREQ:
		unit = PTYPE_FREQ_UNIT;
		break;
	case PARAM_TYPE_DELAY:
		unit = PTYPE_DELAY_UNIT;
		break;
	case PARAM_TYPE_PHASE:
		unit = PTYPE_PHASE_UNIT;
		break;
	case PARAM_TYPE_OTHER:
		unit = PTYPE_OTHER_UNIT;
		break;
	}

	snprintf(param_str, 128, "%d | %s: %.3f %s | Min: %.3f | Max: %.3f", param->id, param->name, param->value, unit, param->min, param->max);
	return param_str;
}
