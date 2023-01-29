#include <types.h>
#include <string.h>
#include <drivers/vga.hpp>

#define VGA_ENTRY_COLOR(fore, back) (fore | back << 4)
#define VGA_ENTRY(c, color) ((uint16_t)c | (uint16_t)color << 8)

namespace kfs::vga
{
	static const uint32_t VGA_WIDTH = 80;
	static const uint32_t VGA_HEIGHT = 25;

	static uint32_t terminal_row;
	static uint32_t terminal_column;
	static uint8_t terminal_color;
	static uint16_t *terminal_buffer;

	void initialize(void)
	{
		terminal_row = 0;
		terminal_column = 0;
		terminal_color = VGA_ENTRY_COLOR(COLOR_LIGHT_GREY, COLOR_BLACK);
		terminal_buffer = (uint16_t*)0xB8000;
		for (uint32_t y = 0; y < VGA_HEIGHT; y++)
		{
			for (uint32_t x = 0; x < VGA_WIDTH; x++)
			{
				const uint32_t index = y * VGA_WIDTH + x;
				terminal_buffer[index] = VGA_ENTRY(' ', terminal_color);
			}
		}
	}

	void set(char c, uint8_t color, uint32_t x, uint32_t y)
	{
		const uint32_t index = y * VGA_WIDTH + x;
		terminal_buffer[index] = VGA_ENTRY(c, color);
	}

	void set_color(enum color fore, enum color back)
	{
		terminal_color = VGA_ENTRY_COLOR(fore, back);
	}

	void put(char c)
	{
		set(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH)
		{
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		}
	}

	void write(const char *str)
	{
		write(str, strlen(str));
	}

	void write(const void *data, uint32_t size)
	{
		for (uint32_t i = 0; i < size; i++)
			put(((char*)data)[i]);
	}
}
