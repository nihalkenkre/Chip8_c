#pragma once

#include <vulkan/vulkan.h>

typedef struct vk_instance
{
    VkInstance inst;
} vk_instance;

vk_instance vk_instance_create(void);
void vk_instance_destroy(vk_instance inst);