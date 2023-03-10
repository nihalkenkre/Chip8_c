#pragma once

#include <Windows.h>
#include <stdint.h>

typedef struct display display;

display *display_create(HINSTANCE h_instance, HWND h_wnd);
void display_init(display *d);
//void display_generate_diagonal(display *d);

void display_draw(display* d, unsigned char* pixels);

void display_destroy(display *d);