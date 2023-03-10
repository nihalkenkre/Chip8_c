#include "vk_image_view.h"

#include <stdlib.h>

VkDevice d;

vk_image_view vk_image_view_create(const VkDevice *dev, const VkImage *img, const VkFormat* fmt)
{
    VkImageSubresourceRange subresource_range = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
    VkComponentMapping component_mapping = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY};
    VkImageViewCreateInfo create_info = {
        VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        NULL,
        0,
        *img,
        VK_IMAGE_VIEW_TYPE_2D,
        *fmt,
        component_mapping,
        subresource_range};

    vk_image_view img_view;

    vkCreateImageView(*dev, &create_info, NULL, &img_view.img_view);

    d = *dev;

    return img_view;
}

void vk_image_view_destroy(vk_image_view img_view)
{
    if (d != VK_NULL_HANDLE && img_view.img_view != VK_NULL_HANDLE)
    {

        vkDestroyImageView(d, img_view.img_view, NULL);
    }
}