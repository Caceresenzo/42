#include <types.h>

namespace kfs::vga
{
	enum color
	{
		COLOR_BLACK = 0,
		COLOR_BLUE = 1,
		COLOR_GREEN = 2,
		COLOR_CYAN = 3,
		COLOR_RED = 4,
		COLOR_MAGENTA = 5,
		COLOR_BROWN = 6,
		COLOR_LIGHT_GREY = 7,
		COLOR_DARK_GREY = 8,
		COLOR_LIGHT_BLUE = 9,
		COLOR_LIGHT_GREEN = 10,
		COLOR_LIGHT_CYAN = 11,
		COLOR_LIGHT_RED = 12,
		COLOR_LIGHT_MAGENTA = 13,
		COLOR_LIGHT_BROWN = 14,
		COLOR_WHITE = 15,
	};

	void initialize(void);
	void set(char c, enum color color, uint32_t x, uint32_t y);
	void set_color(enum color fore, enum color back);
	void put(char c);
	void write(const char *data);
	void write(const void *data, uint32_t size);
	void scroll(bool down = true);
	void clear_line(uint32_t line);
	void test();

}
