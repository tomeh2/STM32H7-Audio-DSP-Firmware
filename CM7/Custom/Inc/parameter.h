/*
 * parameter.h
 *
 *  Created on: Sep 9, 2024
 *      Author: PC
 */

#ifndef INC_PARAMETER_H_
#define INC_PARAMETER_H_

#include "arm_math.h"

enum ParameterType
{
	PARAM_TYPE_COEFF,
	PARAM_TYPE_FREQ,
	PARAM_TYPE_DELAY,
	PARAM_TYPE_PHASE,
	PARAM_TYPE_OTHER
};

struct Parameter
{
	char* name;
	uint8_t id;
	enum ParameterType type;
	float32_t value;
	float32_t min;
	float32_t max;
};

int8_t parameter_init(struct Parameter* param, uint8_t id, char* name, enum ParameterType type, float32_t min, float32_t max, float32_t init_value);
int8_t parameter_set(struct Parameter* param, float32_t value);
char* parameter_tostr(struct Parameter* param);

#endif /* INC_PARAMETER_H_ */
