#include "vk_instance.h"

#include <stdlib.h>

vk_instance vk_instance_create(void)
{
    char *requested_instance_extensions[2] = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_WIN32_SURFACE_EXTENSION_NAME};

    VkApplicationInfo application_info = {
        VK_STRUCTURE_TYPE_APPLICATION_INFO,
        NULL,
        "Chip8",
        VK_MAKE_VERSION(1, 0, 0),
        "Chip8",
        VK_MAKE_VERSION(1, 0, 0),
        VK_MAKE_VERSION(1, 0, 0)};

    VkInstanceCreateInfo instance_create_info = {
        VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        NULL,
        0,
        &application_info,
        0,
        NULL,
        2,
        requested_instance_extensions};

    vk_instance inst;

    vkCreateInstance(&instance_create_info, NULL, &inst.inst);

    return inst;
}

void vk_instance_destroy(vk_instance inst)
{
    if (inst.inst != VK_NULL_HANDLE)
    {
        vkDestroyInstance(inst.inst, NULL);
    }
}