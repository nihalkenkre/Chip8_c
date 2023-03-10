#pragma once

#include <Windows.h>

typedef struct cpu cpu;

cpu* cpu_create(HINSTANCE h_instance, HWND h_wnd);
void cpu_execute(cpu* c);
void cpu_destroy(cpu* c);