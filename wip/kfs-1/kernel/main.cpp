#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>
#include <cpu/interrupt.hpp>
#include <cpu/io.hpp>
#include <cpu/multiboot.hpp>
#include <drivers/keyboard.hpp>
#include <drivers/timer.hpp>
#include <drivers/vga.hpp>
#include <program/shell.hpp>

extern "C"
{
	void kmain(unsigned long magic, unsigned long addr)
	{
		kfs::io::cli();

		kfs::vga::initialize();
		kfs::gdt::initialize();
		kfs::idt::initialize();
		kfs::interrupt::initialize();

		kfs::timer::initialize();
		kfs::keyboard::initialize();

		if (!kfs::multiboot::initialize(magic, addr))
			return;

		kfs::io::sti();

		kfs::shell::do_ft();
		kfs::shell::initialize();

		while (1)
			kfs::io::halt();
	}
}
