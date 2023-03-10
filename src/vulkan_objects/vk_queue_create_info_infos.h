#pragma once

#include <vulkan/vulkan.h>

#include "vk_queue_family_indices.h"

typedef struct info_info
{
    uint32_t q_fly_idx;
    uint32_t q_count;
    float* priorities;
} info_info;

typedef struct vk_queue_create_info_infos
{
    info_info* info_infos;
    uint32_t info_infos_count;
} vk_queue_create_info_infos;

vk_queue_create_info_infos vk_queue_create_info_infos_create(const vk_queue_family_indices* q_fly_idx);
void vk_queue_create_info_infos_destroy(vk_queue_create_info_infos info_infos);