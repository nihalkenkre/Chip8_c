#pragma once

#include <vulkan/vulkan.h>
#include <Windows.h>

#include "vulkan_objects.h"

typedef struct vulkan
{
    vk_instance inst;
    vk_physical_device phy_dev;
    vk_queue_family_indices q_fly_idx;
    vk_queue_create_info_infos q_create_info_infos;
    vk_queue_create_infos q_create_infos;
    vk_surface surface;
    vk_device gfx_dev;
    vk_device_queues dev_qs;
    vk_swapchain sc;
} vulkan;

vulkan vulkan_create(HINSTANCE h_instance, HWND h_wnd);
void vulkan_destroy(vulkan v);

void vulkan_draw(vulkan v, unsigned char *pixels);