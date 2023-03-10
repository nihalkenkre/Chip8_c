#pragma once

#include <vulkan/vulkan.h>

#include "vk_queue_create_infos.h"

typedef struct vk_device
{
    VkDevice dev;
} vk_device;

vk_device vk_device_create(const VkPhysicalDevice *phy_dev, const vk_queue_create_infos *q_create_infos);
void vk_device_destroy(vk_device dev);