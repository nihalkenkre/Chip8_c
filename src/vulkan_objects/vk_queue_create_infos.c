#include "vk_queue_create_infos.h"

#include <stdlib.h>

vk_queue_create_infos vk_queue_create_infos_create(const vk_queue_create_info_infos *q_create_info_infos)
{
    vk_queue_create_infos q_create_infos;
    q_create_infos.q_create_infos = (VkDeviceQueueCreateInfo *)malloc(q_create_info_infos->info_infos_count * sizeof(VkDeviceQueueCreateInfo));
    q_create_infos.q_create_infos_count = q_create_info_infos->info_infos_count;

    for (uint32_t info_infos_idx = 0; info_infos_idx < q_create_info_infos->info_infos_count; ++info_infos_idx)
    {
        q_create_infos.q_create_infos[info_infos_idx].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        q_create_infos.q_create_infos[info_infos_idx].pNext = NULL;
        q_create_infos.q_create_infos[info_infos_idx].flags = 0;
        q_create_infos.q_create_infos[info_infos_idx].queueFamilyIndex = q_create_info_infos->info_infos[info_infos_idx].q_fly_idx;
        q_create_infos.q_create_infos[info_infos_idx].queueCount = q_create_info_infos->info_infos[info_infos_idx].q_count;
        q_create_infos.q_create_infos[info_infos_idx].pQueuePriorities = q_create_info_infos->info_infos[info_infos_idx].priorities;
    }

    return q_create_infos;
}

void vk_queue_create_infos_destroy(vk_queue_create_infos q_create_infos)
{
    if (q_create_infos.q_create_infos != NULL)
    {
        free(q_create_infos.q_create_infos);
    }
}
