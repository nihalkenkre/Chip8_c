#pragma once

#include <vulkan/vulkan.h>

typedef struct vk_device_queue_info
{
    VkDeviceQueueCreateInfo cis;
    VkQueueFlags flags;
} vk_device_queue_info;

vk_device_queue_info* vk_device_queue_info_create(const VkPhysicalDevice* phy_dev);
void vk_device_queue_info_destroy(vk_device_queue_info* qci);