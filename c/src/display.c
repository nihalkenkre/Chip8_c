#include "vulkan.h"
#include "display.h"

#include <stdint.h>
#include <stdlib.h>

struct display
{
    vulkan v;
};

display *display_create(HINSTANCE h_instance, HWND h_wnd)
{
    display *d = (display *)calloc(1, sizeof(display));
    d->v = vulkan_create(h_instance, h_wnd);

    return d;
}

/*void display_generate_diagonal(display *d)
{
    for (uint32_t y = 0; y < d->cols_count; ++y)
    {
        for (uint32_t x = 0; x < d->rows_count; ++x)
        {
            if (x == (y * 2))
            {
                d->pixels[y * d->cols_count + x] = 1;
            }
            else
            {
                d->pixels[y * d->cols_count + x] = 0;
            }
        }
    }
}*/

void display_draw(display* d, unsigned char* pixels)
{
    vulkan_draw(d->v, pixels);
}

void display_destroy(display *d)
{
    if (d != NULL)
    {
        vulkan_destroy(d->v);

        free(d);
    }
}