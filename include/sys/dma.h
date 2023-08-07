#ifndef __SYS_DMA_H__
#define __SYS_DMA_H__

#include "stdint.h"

void free_dma(uint16_t);
int request_dma(uint16_t, const char*);

#endif