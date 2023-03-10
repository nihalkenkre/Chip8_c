#include "vulkan.h"
#include <vulkan/vulkan_win32.h>

#include <stdlib.h>
#include <stdio.h>


vulkan vulkan_create(HINSTANCE h_instance, HWND h_wnd)
{
	vulkan v;

	v.inst = vk_instance_create();
	v.phy_dev = vk_physical_device_create(&v.inst.inst);
	v.q_fly_idx = vk_queue_family_indices_create(&v.phy_dev.phy_dev);
	v.surface = vk_surface_create(&v.inst.inst, &h_instance, &h_wnd, &v.phy_dev.phy_dev, &v.q_fly_idx.gfx);
	v.gfx_dev = vk_device_create(&v.phy_dev.phy_dev, &v.q_fly_idx);
	v.dev_qs = vk_device_queues_create(&v.gfx_dev.dev, &v.q_fly_idx);
	v.sc = vk_swapchain_create(&v.gfx_dev.dev, &v.surface);

	return v;
}

void vulkan_draw(vulkan v, unsigned char *pixels)
{
}

void vulkan_destroy(vulkan v)
{
	vk_swapchain_destroy(v.sc);
	vk_device_queues_destroy(v.dev_qs);
	vk_device_destroy(v.gfx_dev);
	vk_surface_destroy(v.surface);
	vk_queue_family_indices_destroy(v.q_fly_idx);
	vk_physical_device_destroy(v.phy_dev);
	vk_instance_destroy(v.inst);
}