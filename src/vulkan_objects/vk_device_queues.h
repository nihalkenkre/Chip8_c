#pragma once

#include <vulkan/vulkan.h>

#include "vk_queue.h"
#include "vk_queue_family_indices.h"
#include "vk_queue_create_info_infos.h"

typedef struct vk_device_queues
{
    vk_queue gfx;
    vk_queue cmpt;
    vk_queue xfer;
} vk_device_queues;


vk_device_queues vk_device_queues_create(const VkDevice* dev, const vk_queue_family_indices* q_fly_idx, const vk_queue_create_info_infos* q_create_info_infos);
void vk_device_queues_destroy(vk_device_queues dev_q);