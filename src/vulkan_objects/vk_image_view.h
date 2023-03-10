#pragma once

#include <vulkan/vulkan.h>

typedef struct vk_image_view
{
    VkImageView img_view;
} vk_image_view;


vk_image_view vk_image_view_create(const VkDevice* dev, const VkImage* img, const VkFormat* fmt);
void vk_image_view_destroy(vk_image_view img_view);