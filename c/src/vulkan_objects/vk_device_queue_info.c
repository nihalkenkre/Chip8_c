#include "vk_device_queue_info.h"

#include <stdlib.h>

vk_device_queue_info *vk_device_queue_info_create(const VkPhysicalDevice* phy_dev)
{
    uint32_t q_fly_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(*phy_dev, &q_fly_count, NULL);
    
    VkQueueFamilyProperties* q_fly_props = (VkQueueFamilyProperties*) malloc(sizeof(VkQueueFamilyProperties) * q_fly_count);
    vkGetPhysicalDeviceQueueFamilyProperties(*phy_dev, &q_fly_count, q_fly_props);

    free(q_fly_props);

    vk_device_queue_info* qi = (vk_device_queue_info*) malloc(sizeof(vk_device_queue_info));
    memset(qi, 0, sizeof(vk_device_queue_info));
    return qi;
}

void vk_device_queue_info_destroy(vk_device_queue_info *qi)
{
    if (qi != NULL)
    {
        free(qi);
    }
}