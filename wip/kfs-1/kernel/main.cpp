#include <drivers/vga.hpp>

extern "C"
{
	void kmain(void)
	{
		kfs::vga::initialize();
		kfs::vga::write("42");
	}
}
