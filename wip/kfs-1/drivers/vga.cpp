#include <types.h>
#include <string.h>
#include <drivers/vga.hpp>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ENTRY_COLOR(fore, back) (fore | back << 4)
#define VGA_ENTRY(c, color) ((uint16_t)c | (uint16_t)color << 8)
#define VGA_INDEX(x, y) ((y * VGA_WIDTH + x))
#define VGA_MEMORY_START_ADDRESS ((uint16_t *) 0xB8000)
#define VGA_MEMORY_SIZE_BYTE (VGA_WIDTH * sizeof(uint16_t) * VGA_HEIGHT)

#define VGA_DEFAULT_COLOR (VGA_ENTRY_COLOR(COLOR_LIGHT_GREY, COLOR_BLACK))
#define VGA_ENTRY_EMPTY (VGA_ENTRY(' ', VGA_DEFAULT_COLOR))

namespace kfs::vga
{
	static uint32_t g_row;
	static uint32_t g_column;
	static uint8_t g_color;
	static uint16_t *g_buffer;

	void initialize(void)
	{
		g_row = 0;
		g_column = 0;
		g_color = VGA_DEFAULT_COLOR;
		g_buffer = VGA_MEMORY_START_ADDRESS;

		for (uint32_t y = 0; y < VGA_HEIGHT; y++)
		{
			for (uint32_t x = 0; x < VGA_WIDTH; x++)
			{
				const uint32_t index = y * VGA_WIDTH + x;
				g_buffer[index] = VGA_ENTRY(' ', g_color);
			}
		}
	}

	void set(char c, uint8_t color, uint32_t x, uint32_t y)
	{
		const uint32_t index = y * VGA_WIDTH + x;
		g_buffer[index] = VGA_ENTRY(c, color);
	}

	void set_color(enum color fore, enum color back)
	{
		g_color = VGA_ENTRY_COLOR(fore, back);
	}

	void put(char c)
	{
		if (c != '\n' && c != '\r')
			set(c, g_color, g_column, g_row);

		if (c == '\r')
			g_column = 0;
		else if (++g_column == VGA_WIDTH || c == '\n')
		{
			g_column = 0;
			if (g_row + 1 == VGA_HEIGHT)
				scroll();
			else
				g_row++;
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

	void scroll(bool down)
	{
		if (down)
		{
			memmove(g_buffer, g_buffer + VGA_WIDTH, VGA_MEMORY_SIZE_BYTE);
			clear_line(VGA_HEIGHT - 1);
		}
		else
		{
			memmove(g_buffer + VGA_WIDTH, g_buffer, VGA_MEMORY_SIZE_BYTE);
			clear_line(0);
		}
	}

	void clear(void)
	{
		g_column = 0;
		g_row = 0;

		for (uint32_t y = 0; y < VGA_HEIGHT; y++)
			for (uint32_t x = 0; x < VGA_WIDTH; x++)
				g_buffer[VGA_INDEX(x, y)] = VGA_ENTRY_EMPTY;
	}

	void clear_line(uint32_t line)
	{
		for (uint32_t x = 0; x < VGA_WIDTH; ++x)
			set(' ', g_color, x, line);
	}

	void test()
	{
		uint16_t color = g_color;

		for (uint32_t fore = 0; fore < 16; ++fore)
		{
			for (uint32_t back = 0; back < 16; ++back)
			{
				put('x');
				put('x');
				set_color((enum color)fore, (enum color)back);
			}
			put('\n');
		}

		g_color = color;
	}
}
