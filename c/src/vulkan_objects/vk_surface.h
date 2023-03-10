#pragma once

#include <vulkan/vulkan.h>
#include <Windows.h>

typedef struct vk_surface
{
    VkSurfaceKHR surface;
    VkPresentModeKHR present_mode;
    VkSurfaceCapabilitiesKHR surface_capabilities;
    VkSurfaceFormatKHR format;
    VkExtent2D extent;
} vk_surface;

vk_surface vk_surface_create(const VkInstance *instance,
                             const HINSTANCE *h_instance,
                             const HWND *h_wnd,
                             const VkPhysicalDevice *phy_dev,
                             const uint32_t *gfx_q_fly_idx);
void vk_surface_destroy(vk_surface surface);