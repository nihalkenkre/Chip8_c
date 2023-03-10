#pragma once

#include <vulkan/vulkan.h>

#include "vk_queue_create_info_infos.h"

typedef struct vk_queue_create_infos
{
    VkDeviceQueueCreateInfo* q_create_infos;
    uint32_t q_create_infos_count;
} vk_queue_create_infos;

vk_queue_create_infos vk_queue_create_infos_create(const vk_queue_create_info_infos* q_create_info_infos);
void vk_queue_create_infos_destroy(vk_queue_create_infos infos);