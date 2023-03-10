#include "vk_physical_device.h"

#include <stdlib.h>

vk_physical_device vk_physical_device_create(const VkInstance *inst)
{
    uint32_t physical_device_count = 0;
    vkEnumeratePhysicalDevices(*inst, &physical_device_count, NULL);

    VkPhysicalDevice *physical_devices = (VkPhysicalDevice *)malloc(sizeof(VkPhysicalDevice) * physical_device_count);
    vkEnumeratePhysicalDevices(*inst, &physical_device_count, physical_devices);

    vk_physical_device phy_dev;

    phy_dev.phy_dev = physical_devices[1];

    vkGetPhysicalDeviceMemoryProperties(phy_dev.phy_dev, &phy_dev.mem_props);
    vkGetPhysicalDeviceProperties(phy_dev.phy_dev, &phy_dev.dev_props);

    free(physical_devices);

    return phy_dev;
}

void vk_physical_device_destroy(vk_physical_device phy_dev)
{
}