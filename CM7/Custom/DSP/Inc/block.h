/*
 * block.h
 *
 *  Created on: Jul 30, 2024
 *      Author: PC
 */

#ifndef DSP_INC_BLOCK_H_
#define DSP_INC_BLOCK_H_

#include <stdlib.h>
#include <stdint.h>

struct ProcessingBlock
{
	void (*process)(void* private_data, float* block, size_t block_size);
};

#endif /* DSP_INC_BLOCK_H_ */
