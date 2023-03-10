#include "vk_device.h"

#include <stdlib.h>

typedef struct q_create_info_info
{
    uint32_t idx;
    uint32_t q_count;
} q_create_info_info;

vk_device vk_device_create(const VkPhysicalDevice *phy_dev, const vk_queue_create_infos *q_create_infos)
{
    char *dev_ext[1];
    dev_ext[0] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

    float priorities[3] = {1.0, 1.0, 1.0};

    VkPhysicalDeviceFeatures dev_feats;
    vkGetPhysicalDeviceFeatures(*phy_dev, &dev_feats);

    VkDeviceCreateInfo dev_create_info = {
        VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        NULL,
        0,
        q_create_infos->q_create_infos_count,
        q_create_infos->q_create_infos,
        0,
        NULL,
        1,
        dev_ext,
        &dev_feats};

    vk_device dev;

    vkCreateDevice(*phy_dev, &dev_create_info, NULL, &dev.dev);

    return dev;
}

void vk_device_destroy(vk_device dev)
{
    vkDestroyDevice(dev.dev, NULL);
}