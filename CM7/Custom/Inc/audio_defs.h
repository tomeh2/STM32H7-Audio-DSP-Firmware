#ifndef __AUDIO_DEFS_H_
#define __AUDIO_DEFS_H_

#include <audio_stream.h>

#define SAMPLE_RATE 48000

#define AUDIO_BUF_TRESHOLD_HIGH 60
#define AUDIO_BUF_TRESHOLD_LOW 40
#define AUDIO_BUF_TRESHOLD_START 50

#define AUDIO_CHANNELS 2
#define BYTES_PER_SAMPLE 2

#define CHANNEL_LEFT 0
#define CHANNEL_RIGHT 1
#define NUM_CHANNELS 2

#define USB_AUDIOCLASS_RXBUF_BLOCKS 32
#define SAMPLES_PER_BLOCK 128

#define DELAY_LINE_BLOCKS 400

#define ERBUFOVF 255
#define ERBUFUDF 255
#define ERINVCTL 255

#define EOK 0
#define EINVAL 1
#define ENOMEM 2
#define EINVBLKSIZE 3
#define EOOB 4			// Out of Bounds error
#define ENULLPTR 5

#define LOG_TIME_PRBLOCK_ID 0
#define LOG_TIME_USB_RD 3
#define LOG_TIME_USB_WR 4
#define LOG_TIME_AUDIO_WR 5
#define LOG_AUDENG_PROCESS_1 1
#define LOG_AUDENG_PROCESS_2 2

extern uint8_t temp_next_block_ready;

#endif
