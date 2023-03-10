#include "vk_queue_family_indices.h"

#include <vulkan/vulkan.h>

#include <stdlib.h>

vk_queue_family_indices vk_queue_family_indices_create(const VkPhysicalDevice *phy_dev)
{
    uint32_t q_fly_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(*phy_dev, &q_fly_count, NULL);

    VkQueueFamilyProperties *q_fly_props = (VkQueueFamilyProperties *)malloc(sizeof(VkQueueFamilyProperties) * q_fly_count);
    vkGetPhysicalDeviceQueueFamilyProperties(*phy_dev, &q_fly_count, q_fly_props);

    int32_t gfx = -1;
    int32_t cmpt = -1;
    int32_t xfer = -1;

    uint32_t num_q_gfx = 0;
    uint32_t num_q_cmpt = 0;
    uint32_t num_q_xfer = 0;

    for (uint32_t i = 0; i < q_fly_count; ++i)
    {
        if (q_fly_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            gfx = i;
            num_q_gfx = q_fly_props[i].queueCount;
            break;
        }
    }

    for (uint32_t i = 0; i < q_fly_count; ++i)
    {
        if (q_fly_props[i].queueFlags & VK_QUEUE_COMPUTE_BIT && (i != gfx))
        {
            cmpt = i;
            num_q_cmpt = q_fly_props[i].queueCount;
            break;
        }
    }

    if (cmpt == -1)
    {
        for (uint32_t i = 0; i < q_fly_count; ++i)
        {
            if (q_fly_props[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
            {
                cmpt = i;
                num_q_cmpt = q_fly_props[i].queueCount;
                break;
            }
        }
    }

    for (uint32_t i = 0; i < q_fly_count; ++i)
    {
        if (q_fly_props[i].queueFlags & VK_QUEUE_TRANSFER_BIT && (i != gfx) && (i != cmpt))
        {
            xfer = i;
            num_q_xfer = q_fly_props[i].queueCount;
            break;
        }
    }

    if (xfer == -1)
    {
        for (uint32_t i = 0; i < q_fly_count; ++i)
        {
            if (q_fly_props[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                xfer = i;
                num_q_xfer = q_fly_props[i].queueCount;
                break;
            }
        }
    }

    free(q_fly_props);

    vk_queue_family_indices q_fly_idx;

    q_fly_idx.gfx = gfx;
    q_fly_idx.gfx_max_q_count = num_q_gfx;

    q_fly_idx.cmpt = cmpt;
    q_fly_idx.cmpt_max_q_count = num_q_cmpt;

    q_fly_idx.xfer = xfer;
    q_fly_idx.xfer_max_q_count = num_q_xfer;
    
    return q_fly_idx;
}

void vk_queue_family_indices_destroy(vk_queue_family_indices q_fly_idx)
{
}