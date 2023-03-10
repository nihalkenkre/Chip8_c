#include "cpu.h"
#include "display.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

struct cpu
{
    unsigned char memory[4096];

    unsigned char vx[16];
    unsigned char vf;
    unsigned short i;

    unsigned char delay_timer;
    unsigned char sound_timer;

    unsigned short pc;
    unsigned char sp;

    unsigned short stack[16];

    display *d;

    uint32_t rows_count;
    uint32_t cols_count;
    unsigned char *pixels;
};

cpu *cpu_create(HINSTANCE h_instance, HWND h_wnd)
{
    cpu *c = (cpu *)calloc(1, sizeof(cpu));

    c->cols_count = 64;
    c->rows_count = 32;

    c->pc = 0x200;
    c->d = display_create(h_instance, h_wnd);
    c->pixels = (unsigned char *)calloc(1, c->rows_count * c->cols_count);

    // 0
    c->memory[0] = 0xF0;
    c->memory[1] = 0x90;
    c->memory[2] = 0x90;
    c->memory[3] = 0x90;
    c->memory[4] = 0xF0;

    // 1
    c->memory[5] = 0x20;
    c->memory[6] = 0x60;
    c->memory[7] = 0x20;
    c->memory[8] = 0x20;
    c->memory[9] = 0x70;

    // 2
    c->memory[10] = 0xF0;
    c->memory[11] = 0x10;
    c->memory[12] = 0xF0;
    c->memory[13] = 0x80;
    c->memory[14] = 0xF0;

    // 3
    c->memory[15] = 0xF0;
    c->memory[16] = 0x10;
    c->memory[17] = 0xF0;
    c->memory[18] = 0x10;
    c->memory[19] = 0xF0;

    // 4
    c->memory[20] = 0x90;
    c->memory[21] = 0x90;
    c->memory[22] = 0xF0;
    c->memory[23] = 0x10;
    c->memory[24] = 0x10;

    // 5
    c->memory[25] = 0xF0;
    c->memory[26] = 0x80;
    c->memory[27] = 0xF0;
    c->memory[28] = 0x10;
    c->memory[29] = 0xF0;

    // 6
    c->memory[30] = 0xF0;
    c->memory[31] = 0x80;
    c->memory[32] = 0xF0;
    c->memory[33] = 0x90;
    c->memory[34] = 0xF0;

    // 7
    c->memory[35] = 0xF0;
    c->memory[36] = 0x10;
    c->memory[37] = 0x20;
    c->memory[38] = 0x40;
    c->memory[39] = 0x40;

    // 8
    c->memory[40] = 0xF0;
    c->memory[41] = 0x90;
    c->memory[42] = 0xF0;
    c->memory[43] = 0xF9;
    c->memory[44] = 0xF0;

    // 9
    c->memory[45] = 0xF0;
    c->memory[46] = 0x90;
    c->memory[47] = 0xF0;
    c->memory[48] = 0x10;
    c->memory[49] = 0xF0;

    // A
    c->memory[50] = 0xF0;
    c->memory[51] = 0x90;
    c->memory[52] = 0xF0;
    c->memory[53] = 0x90;
    c->memory[54] = 0x90;

    // B
    c->memory[55] = 0xE0;
    c->memory[56] = 0x90;
    c->memory[57] = 0xF0;
    c->memory[58] = 0x10;
    c->memory[59] = 0xE0;

    // C
    c->memory[60] = 0xF0;
    c->memory[61] = 0x80;
    c->memory[62] = 0x80;
    c->memory[63] = 0x80;
    c->memory[64] = 0xF0;

    // D
    c->memory[65] = 0xE0;
    c->memory[66] = 0x90;
    c->memory[67] = 0x90;
    c->memory[68] = 0x90;
    c->memory[69] = 0xE0;

    // E
    c->memory[70] = 0xF0;
    c->memory[71] = 0x80;
    c->memory[72] = 0xF0;
    c->memory[73] = 0x80;
    c->memory[74] = 0xF0;

    // F
    c->memory[75] = 0xF0;
    c->memory[76] = 0x80;
    c->memory[77] = 0xF0;
    c->memory[78] = 0x80;
    c->memory[79] = 0x80;

    return c;
}

void cpu_read_rom_from_file(cpu *c, char *path)
{
    FILE *file = fopen(path, "rb");
    if (!file)
    {
        wchar_t buff[256];
        swprintf(buff, 256, L"Failed to open %hs\n", path);
        OutputDebugString(buff);
        return;
    }

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    rewind(file);

    fread(c->memory + 512, sizeof(unsigned char), file_size, file);

    fclose(file);

    for (int i = 512; i < 512 + file_size; i += 2)
    {
        wchar_t buff[256];
        swprintf(buff, 256, L"%02x %02x\n", c->memory[i], c->memory[i + 1]);
        OutputDebugString(buff);
    }
}

void cpu_execute(cpu *c)
{
    for (uint32_t y = 0; y < c->cols_count; ++y)
    {
        for (uint32_t x = 0; x < c->rows_count; ++x)
        {
            if (x == (y * 2))
            {
                memset(c->pixels + (y * c->rows_count + x), 1, sizeof(unsigned char));
            }
            else
            {
                memset(c->pixels + (y * c->rows_count + x), 0, sizeof(unsigned char));
            }
        }
    }

    display_draw(c->d, c->pixels);

    /*unsigned short opcode = c->memory[c->pc] << 8 | c->memory[c->pc + 1];

    wchar_t buff[256];
    swprintf(buff, 256, L"Executing %02x %02x\n", c->memory[c->pc], c->memory[c->pc + 1]);
    OutputDebugString(buff);

    unsigned char opcode_higher_byte = c->memory[c->pc];
    unsigned char opcode_lower_byte = c->memory[c->pc + 1];

    if (opcode_higher_byte == 0x00)
    {
        if (opcode_lower_byte == 0xE0)
        {
            OutputDebugString(L"Clearing the screen\n");

            memset(c->d->pixels, 0, sizeof(unsigned char) * 64 * 32);
            c->pc += 2;
        }
        else if (opcode_lower_byte == 0xEE)
        {
            OutputDebugString(L"Returning from subroutine\n");
        }
    }
    else if ((opcode_higher_byte & 0xF0) == 0xA0)
    {
        unsigned short address = (opcode_higher_byte & 0x0F) << 8 | opcode_lower_byte;

        wchar_t buff[256];
        swprintf(buff, 256, L"Pushing %04x to I\n", address);
        OutputDebugString(buff);

        c->i = address;

        c->pc += 2;
    }
    else if ((opcode_higher_byte & 0xF0) == 0x60)
    {
        c->vx[opcode_higher_byte & 0x0F] = opcode_lower_byte;

        wchar_t buff[256];
        swprintf(buff, 256, L"Putting %02x into V[%02x]\n", opcode_lower_byte, opcode_higher_byte & 0x0F);
        OutputDebugString(buff);

        c->pc += 2;
    }
    else if ((opcode_higher_byte & 0xF0) == 0xD0)
    {
        wchar_t buff[256];
        swprintf(buff, 256, L"Drawing %02x bytes starting at %02x at %02x %02x\n", opcode_lower_byte & 0x0F, c->i, c->vx[opcode_higher_byte & 0x0F], c->vx[opcode_lower_byte & 0xF0]);
        OutputDebugString(buff);

        unsigned char *bytes_to_display = (unsigned char *)malloc(opcode_lower_byte & 0x0F);
        memcpy(bytes_to_display, c->memory + c->i, opcode_lower_byte & 0x0F);

        c->d->pixels[c->vx[opcode_lower_byte & 0xF0] * 64 + c->vx[opcode_higher_byte & 0x0F]] = 1;

        free(bytes_to_display);
        c->pc += 2;
    }
    else if ((opcode_higher_byte & 0xF0) == 0x70)
    {
        wchar_t buff[256];
        swprintf(buff, 256, L"Setting vx[%02x] = vx[%02x] + %02x\n", opcode_higher_byte & 0x0F, opcode_higher_byte & 0x0F, opcode_lower_byte);
        OutputDebugString(buff);

        c->vx[opcode_higher_byte & 0x0F] += opcode_lower_byte;

        c->pc += 2;
    }
    else if ((opcode_higher_byte & 0xF0) == 0x10)
    {
        wchar_t buff[256];
        swprintf(buff, 256, L"Setting pc to %02x\n", (opcode_higher_byte & 0x0F) << 8 | opcode_lower_byte);
        OutputDebugString(buff);

        c->pc = (opcode_higher_byte & 0x0F) << 8 | opcode_lower_byte;
    }

    memset(buff, 0, 256);
    swprintf(buff, 256, L"PC: %04x\n", c->pc);
    OutputDebugString(buff);*/
}

void cpu_draw(cpu *c)
{
}

void cpu_destroy(cpu *c)
{
    if (c != NULL)
    {
        if (c->d != NULL)
        {
            display_destroy(c->d);
        }

        if (c->pixels != NULL)
        {
            free(c->pixels);
        }

        free(c);
    }
}