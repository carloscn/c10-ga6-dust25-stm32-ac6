// STM32   Project.                                                     GitLab
/****************************************************************************/
/*                                                                          */
/*  @file       : ring.c                                                    */
/*  @Copyright  : Powered by MULTIBEANS ORG rights reserved.                */
/*  @Revision   : Ver 1.0.                                                  */
/*  @Data       : 2018.08.26 Release.                                       */
/*  @Belong     : EDU class.                                                */
/*  @Git        :                                                           */
/*  **code : (GB2312/GBK) in Windows 10 x64. AC6            platform.       */
/****************************************************************************/
/*  @Attention:                                                             */
/*  ---------------------------------------------------------------------   */
/*  |    Data    |  Behavior |     Offer      |          Content         |  */
/*  | 2018.08.26 |   create  |Carlos Wei(M)   | ceate the document.      |  */
/*  ---------------------------------------------------------------------   */
/*  Email: carlos@mltbns.top                                  MULTIBEANS.   */
/****************************************************************************/
#include "ring.h"

int ring_init(RING* dev)
{
    dev->buffer.out = 0;
    dev->buffer.in = 0;
}

uint32_t ring_module_get_length(RING* dev)
{
	uint32_t length = 0;

	length = dev->buffer.in - dev->buffer.out;

	return length;
}

uint32_t ring_module_pop(RING* dev, void* buffer, uint32_t size)
{
	assert(dev || buffer);
	uint32_t length = 0;
	uint32_t calcu = 0;

	size = min(size, dev->master->get_current_size(dev));
	calcu = dev->buffer.out & (dev->buffer.size - 1);
	length = min(size, dev->buffer.size - calcu);
	memcpy(buffer, dev->buffer.room + calcu, length);
	memcpy(buffer, dev->buffer.room, size - length);
	dev->buffer.out += size;

	return size;
}

uint32_t ring_module_push(RING* dev, void* buffer, uint32_t size)
{
	assert(dev || buffer);
	uint32_t length = 0;

	size = min(size, dev->buffer.size - dev->buffer.in + dev->buffer.out);
    length = min(size, dev->buffer.size - (dev->buffer.in & (dev->buffer.size - 1)));
    memcpy(dev->buffer.room + (dev->buffer.in & (dev->buffer.size - 1)), buffer, length);
    memcpy(dev->buffer.room, buffer + length, size - length);
    dev->buffer.in += size;

	return size;
}

void ring_del_dev(RING* dev)
{
    if (dev){
        if (dev->buffer.room) {
            free(dev->buffer.room);
            dev->buffer.room = NULL;
        }
        free(dev);
        dev = NULL;
    }
}

RING* ring_new_dev(uint32_t ring_max_length, void* buffer_address)
{
    RING* dev = (RING*)malloc(sizeof(RING));

    dev->master = (struct ring_master_t*)malloc(sizeof(struct ring_master_t));
    dev->master->get_current_size = &ring_module_get_length;
    dev->master->pop = &ring_module_pop;
    dev->master->push = &ring_module_push;
    dev->buffer.max_size = ring_max_length;
    dev->buffer.size = dev->buffer.max_size;
    dev->buffer.room = buffer_address;
    ring_init(dev);

    return dev;
}

