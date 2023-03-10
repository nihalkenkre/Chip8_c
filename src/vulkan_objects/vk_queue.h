#pragma once

#include <vulkan/vulkan.h>

typedef struct vk_queue
{
    VkQueue q;
} vk_queue;


vk_queue vk_queue_create(const VkQueue queue);
void vk_queue_destroy(vk_queue queue);