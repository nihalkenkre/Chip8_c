#include "vk_device_queues.h"

#include <stdlib.h>

vk_device_queues vk_device_queues_create(const VkDevice *dev, const vk_queue_family_indices *q_fly_idx)
{
    uint32_t gfx_q_idx = 0;
    uint32_t cmpt_q_idx = q_fly_idx->gfx == q_fly_idx->cmpt ? (q_fly_idx->gfx + 1) : 0;
    uint32_t xfer_q_idx = 0;

    if (q_fly_idx->xfer == q_fly_idx->cmpt)
    {
        xfer_q_idx = cmpt_q_idx + 1;
    }
    else if (q_fly_idx->xfer == q_fly_idx->gfx)
    {
        xfer_q_idx = gfx_q_idx + 1;
    }

    vk_device_queues dev_qs;
    dev_qs.gfx = vk_queue_create(VK_NULL_HANDLE);
    dev_qs.cmpt = vk_queue_create(VK_NULL_HANDLE);
    dev_qs.xfer = vk_queue_create(VK_NULL_HANDLE);

    vkGetDeviceQueue(*dev, q_fly_idx->gfx, 0, &dev_qs.gfx.q);
    vkGetDeviceQueue(*dev, q_fly_idx->cmpt, 0, &dev_qs.cmpt.q);
    vkGetDeviceQueue(*dev, q_fly_idx->xfer, 0, &dev_qs.xfer.q);

    return dev_qs;
}

void vk_device_queues_destroy(vk_device_queues dev_q)
{
    vk_queue_destroy(dev_q.gfx);
    vk_queue_destroy(dev_q.cmpt);
    vk_queue_destroy(dev_q.xfer);
}