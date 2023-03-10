#pragma once

#include <vulkan/vulkan.h>

typedef struct vk_queue_family_indices
{
    uint32_t gfx;
    uint32_t cmpt;
    uint32_t xfer;

    uint32_t gfx_max_q_count;
    uint32_t cmpt_max_q_count;
    uint32_t xfer_max_q_count;
} vk_queue_family_indices;

vk_queue_family_indices vk_queue_family_indices_create(const VkPhysicalDevice *phy_dev);
void vk_queue_family_indices_destroy(vk_queue_family_indices q_fly_idx);