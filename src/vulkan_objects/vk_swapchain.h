#pragma once

#include <vulkan/vulkan.h>

#include "vk_surface.h"
#include "vk_image_view.h"

typedef struct vk_swapchain
{
    VkSwapchainKHR swapchain;
    VkImage* imgs;
    vk_image_view* img_views;

    uint32_t img_count;
} vk_swapchain;


vk_swapchain vk_swapchain_create(const VkDevice* dev, const vk_surface* surface);
void vk_swapchain_destroy(vk_swapchain sc);
