#include "vk_swapchain.h"

#include <stdlib.h>

VkDevice d;

vk_swapchain vk_swapchain_create(const VkDevice *dev, const vk_surface *surface)
{
    VkSwapchainCreateInfoKHR create_info =
        {
            VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
            NULL,
            0,
            surface->surface,
            surface->surface_capabilities.minImageCount + 1,
            surface->format.format,
            surface->format.colorSpace,
            surface->surface_capabilities.currentExtent,
            1,
            surface->surface_capabilities.supportedUsageFlags,
            VK_SHARING_MODE_EXCLUSIVE,
            0,
            NULL,
            surface->surface_capabilities.currentTransform,
            VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
            surface->present_mode,
            1,
            VK_NULL_HANDLE};

    vk_swapchain sc;

    vkCreateSwapchainKHR(*dev, &create_info, NULL, &sc.swapchain);
    vkGetSwapchainImagesKHR(*dev, sc.swapchain, &sc.img_count, NULL);

    sc.imgs = (VkImage *)malloc(sizeof(VkImage) * sc.img_count);
    vkGetSwapchainImagesKHR(*dev, sc.swapchain, &sc.img_count, sc.imgs);

    sc.img_views = (vk_image_view *)malloc(sizeof(vk_image_view) * sc.img_count);

    for (uint32_t i = 0; i < sc.img_count; ++i)
    {
        sc.img_views[i] = vk_image_view_create(dev, sc.imgs + i, &surface->format.format);
    }

    d = *dev;

    return sc;
}

void vk_swapchain_destroy(vk_swapchain sc)
{
    if (d != VK_NULL_HANDLE && sc.swapchain != VK_NULL_HANDLE)
    {
        for (uint32_t i = 0; i < sc.img_count; ++i)
        {
            vk_image_view_destroy(sc.img_views[i]);
        }

        free(sc.img_views);

        vkDestroySwapchainKHR(d, sc.swapchain, NULL);
    }
}