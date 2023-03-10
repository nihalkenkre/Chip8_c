#include "vk_queue.h"

#include <stdlib.h>

vk_queue vk_queue_create(const VkQueue queue)
{
    vk_queue q;

    q.q = queue;

    return q;
}

void vk_queue_destroy(vk_queue queue)
{
}