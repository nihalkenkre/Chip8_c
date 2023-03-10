#include "vk_device_queues.h"

#include <stdlib.h>

vk_device_queues vk_device_queues_create(const VkDevice *dev, const vk_queue_family_indices *q_fly_idx, const vk_queue_create_info_infos *q_create_info_infos)
{
    uint32_t gfx_q_idx = 0;
    uint32_t cmpt_q_idx = 0;

    if (q_fly_idx->cmpt == q_fly_idx->gfx)
    {
        for (uint32_t info_infos_idx = 0; info_infos_idx < q_create_info_infos->info_infos_count; ++info_infos_idx)
        {
            info_info cur_info_info = q_create_info_infos->info_infos[info_infos_idx];
            if (q_fly_idx->cmpt == cur_info_info.q_fly_idx)
            {
                cmpt_q_idx = gfx_q_idx + 1 < cur_info_info.q_count ? gfx_q_idx + 1 : gfx_q_idx;
            }
        }
    }

    uint32_t xfer_q_idx = 0;

    if (q_fly_idx->xfer == q_fly_idx->gfx)
    {
        for (uint32_t info_infos_idx = 0; info_infos_idx < q_create_info_infos->info_infos_count; ++info_infos_idx)
        {
            info_info cur_info_info = q_create_info_infos->info_infos[info_infos_idx];
            if (q_fly_idx->xfer == cur_info_info.q_fly_idx)
            {
                xfer_q_idx = gfx_q_idx + 1 < cur_info_info.q_count ? gfx_q_idx + 1 : gfx_q_idx;
            }
        }
    }
    else if (q_fly_idx->xfer == q_fly_idx->cmpt)
    {
        for (uint32_t info_infos_idx = 0; info_infos_idx < q_create_info_infos->info_infos_count; ++info_infos_idx)
        {
            info_info cur_info_info = q_create_info_infos->info_infos[info_infos_idx];
            if (q_fly_idx->xfer == cur_info_info.q_fly_idx)
            {
                xfer_q_idx = cmpt_q_idx + 1 < cur_info_info.q_count ? cmpt_q_idx + 1 : cmpt_q_idx;
            }
        }
    }

    vk_device_queues dev_qs;
    dev_qs.gfx = vk_queue_create(VK_NULL_HANDLE);
    dev_qs.cmpt = vk_queue_create(VK_NULL_HANDLE);
    dev_qs.xfer = vk_queue_create(VK_NULL_HANDLE);

    vkGetDeviceQueue(*dev, q_fly_idx->gfx, gfx_q_idx, &dev_qs.gfx.q);
    vkGetDeviceQueue(*dev, q_fly_idx->cmpt, cmpt_q_idx, &dev_qs.cmpt.q);
    vkGetDeviceQueue(*dev, q_fly_idx->xfer, xfer_q_idx, &dev_qs.xfer.q);

    return dev_qs;
}

void vk_device_queues_destroy(vk_device_queues dev_q)
{
    vk_queue_destroy(dev_q.gfx);
    vk_queue_destroy(dev_q.cmpt);
    vk_queue_destroy(dev_q.xfer);
}