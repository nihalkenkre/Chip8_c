#pragma once

#include <vulkan/vulkan.h>

typedef struct vk_physical_device
{
    VkPhysicalDevice phy_dev;
    VkPhysicalDeviceMemoryProperties mem_props;
    VkPhysicalDeviceProperties dev_props;
} vk_physical_device;

vk_physical_device vk_physical_device_create(const VkInstance *inst);
void vk_physical_device_destroy(vk_physical_device phy_dev);