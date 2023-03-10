#include "vk_surface.h"

#include <stdlib.h>

VkInstance inst;

vk_surface vk_surface_create(const VkInstance *instance,
                             const HINSTANCE *h_instance,
                             const HWND *h_wnd,
                             const VkPhysicalDevice *phy_dev,
                             const uint32_t *gfx_q_fly_idx)
{
    VkPhysicalDeviceMemoryProperties phy_dev_mem_props;
    vkGetPhysicalDeviceMemoryProperties(*phy_dev, &phy_dev_mem_props);

    VkPhysicalDeviceProperties dev_props;
    vkGetPhysicalDeviceProperties(*phy_dev, &dev_props);

    VkWin32SurfaceCreateInfoKHR surface_create_info = {
        VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
        NULL,
        0,
        *h_instance,
        *h_wnd};

    vk_surface surface;

    vkCreateWin32SurfaceKHR(*instance, &surface_create_info, NULL, &surface.surface);

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*phy_dev, surface.surface, &surface.surface_capabilities);

    surface.extent = surface.surface_capabilities.currentExtent;

    uint32_t surface_format_count = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(*phy_dev, surface.surface, &surface_format_count, NULL);

    VkSurfaceFormatKHR *surface_formats = (VkSurfaceFormatKHR *)malloc(sizeof(VkSurfaceFormatKHR) * surface_format_count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(*phy_dev, surface.surface, &surface_format_count, surface_formats);

    surface.format = surface_formats[0];

    free(surface_formats);

    uint32_t present_mode_count = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(*phy_dev, surface.surface, &present_mode_count, NULL);

    VkPresentModeKHR *present_modes = (VkPresentModeKHR *)malloc(sizeof(VkPresentModeKHR) * present_mode_count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(*phy_dev, surface.surface, &present_mode_count, present_modes);

    for (uint32_t p = 0; p < present_mode_count; p++)
    {
        if (present_modes[p] == VK_PRESENT_MODE_FIFO_KHR)
        {
            surface.present_mode = present_modes[p];
            break;
        }
    }

    free(present_modes);

    inst = *instance;

    return surface;
}

void vk_surface_destroy(vk_surface surface)
{
    if (inst != VK_NULL_HANDLE && surface.surface != VK_NULL_HANDLE)
    {
        vkDestroySurfaceKHR(inst, surface.surface, NULL);
    }
}