#include <drivers/vga.hpp>
#include <drivers/timer.hpp>
#include <drivers/keyboard.hpp>
#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>
#include <cpu/pit.hpp>
#include <cpu/io.hpp>
#include <cpu/interrupt.hpp>
#include <string.h>
#include <stdio.h>
#include <multiboot.h>

void lolwrite(const char *str)
{
	static enum kfs::vga::color colors[] = {
		kfs::vga::color::COLOR_LIGHT_BLUE,
		kfs::vga::color::COLOR_LIGHT_GREEN,
		kfs::vga::color::COLOR_LIGHT_CYAN,
		kfs::vga::color::COLOR_LIGHT_RED,
		kfs::vga::color::COLOR_LIGHT_MAGENTA,
	};

	uint32_t line = 0;
	uint32_t offset = 0;

	char c;
	while ((c = *str))
	{
		if (c == '\n')
		{
			++line;
			offset = line * 2;
		}
		else
			++offset;

		enum kfs::vga::color fore = colors[(offset / 8) % countof(colors)];
		kfs::vga::set_color((enum kfs::vga::color)fore, kfs::vga::COLOR_BLACK);

		kfs::vga::put(c);
		str++;
	}

	kfs::vga::write(str);
}

multiboot_info_t* multiboot(unsigned long magic, unsigned long addr)
{
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		printk("multiboot: invalid magic number: 0x%x\n", (unsigned)magic);
		return (NULL);
	}

	multiboot_info_t *mbi = (multiboot_info_t*)addr;
	if (CHECK_FLAG(mbi->flags, 0))
		printk("mem_lower = %uKB, mem_upper = %uKB\n",
			(unsigned)mbi->mem_lower, (unsigned)mbi->mem_upper);

	/* Is boot_device valid? */
	if (CHECK_FLAG(mbi->flags, 1))
		printk("boot_device = 0x%x\n", (unsigned)mbi->boot_device);

	/* Is the command line passed? */
	if (CHECK_FLAG(mbi->flags, 2))
		printk("cmdline = %s\n", (char*)mbi->cmdline);

	/* Are mods_* valid? */
	if (CHECK_FLAG(mbi->flags, 3))
	{
		multiboot_module_t *mod;
		int i;

		printk("mods_count = %d, mods_addr = 0x%x\n",
			(int)mbi->mods_count, (int)mbi->mods_addr);
		for (i = 0, mod = (multiboot_module_t*)mbi->mods_addr;
			i < mbi->mods_count;
			i++, mod++)
			printk(" mod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n",
				(unsigned)mod->mod_start,
				(unsigned)mod->mod_end,
				(char*)mod->cmdline);
	}

	/* Are mmap_* valid? */
	if (CHECK_FLAG(mbi->flags, 6))
	{
		multiboot_memory_map_t *mmap;

		printk("mmap_addr = 0x%x, mmap_length = 0x%x\n",
			(unsigned)mbi->mmap_addr, (unsigned)mbi->mmap_length);
		for (mmap = (multiboot_memory_map_t*)mbi->mmap_addr;
			(unsigned long)mmap < mbi->mmap_addr + mbi->mmap_length;
			mmap = (multiboot_memory_map_t*)((unsigned long)mmap
				+ mmap->size + sizeof(mmap->size)))
			printk(" size = 0x%x, base_addr = 0x%x%x,"
				" length = 0x%x%x, type = 0x%x\n",
				(unsigned)mmap->size,
				(unsigned)(mmap->addr >> 32),
				(unsigned)(mmap->addr & 0xffffffff),
				(unsigned)(mmap->len >> 32),
				(unsigned)(mmap->len & 0xffffffff),
				(unsigned)mmap->type);
	}

	return (mbi);
}

namespace shell
{
	char buffer[32] = { 0 };

	void do_ft()
	{
		lolwrite("\n"
			"     d8888   .d8888b.       888       .d888          \n"
			"    d8P888  d88P  Y88b      888      d88P\"           \n"
			"   d8P 888         888      888      888             \n"
			"  d8P  888       .d88P      888  888 888888 .d8888b  \n"
			" d88   888   .od888P\"       888 .88P 888    88K      \n"
			" 8888888888 d88P\"           888888K  888    \"Y8888b. \n"
			"       888  888\"            888 \"88b 888         X88 \n"
			"       888  888888888       888  888 888     88888P' \n"
			"\n"
			);
	}

	void do_tick()
	{
		printk("%d\n", kfs::timer::tick_count());
	}

	void do_cpuid()
	{
		char buffer[20];
		uint32_t eax;
		uint32_t ebx;
		uint32_t ecx;
		uint32_t edx;

		if (kfs::io::cpuid(kfs::io::cpuid_requests::CPUID_GETVENDORSTRING, buffer))
			printk("vendor:           %s\n", buffer);

		kfs::io::cpuid(kfs::io::cpuid_requests::CPUID_GETFEATURES, &eax, &ebx, &ecx, &edx);
		{
			printk("stepping:         %d\n", eax & 0xF);
			printk("model:            %d\n", (eax >> 4) & 0xF);
			printk("family:           %d\n", (eax >> 8) & 0xF);
			printk("processor type:   %d\n", (eax >> 12) & 0x3);
			printk("extended model:   %d\n", (eax >> 16) & 0xF);
			printk("extended family:  %d\n", (eax >> 20) & 0xFF);
		}
	}

	void execute(const char *line)
	{
		if (strcmp("42", line) == 0 || strcmp("ft", line) == 0)
			do_ft();
		else if (strcmp("tick", line) == 0)
			do_tick();
		else if (strcmp("cpuid", line) == 0)
			do_cpuid();
		else
			printk("unknown command\n");
	}

	void prompt()
	{
		putstr("$> ");
	}

	void callback(kfs::keyboard::key_t key)
	{
		uint8_t letter = key.letter;
		if (!letter || !key.state)
			return;

		uint32_t len = strlen(buffer);

		if (letter == '\r')
		{
			putchar('\n');

			if (buffer[0])
			{
				execute(buffer);
				memset(buffer, 0, sizeof(buffer));
			}

			prompt();
			return;
		}

		bool is_backspace = letter == '\b';

		if (!is_backspace && len + 1 != countof(buffer))
		{
			buffer[len] = letter;
			putchar(letter);
		}

		if (is_backspace && len != 0)
		{
			buffer[len - 1] = '\0';
			putstr("\b \b");
		}

		kfs::vga::move_cursor();
	}

	void initialize()
	{
		kfs::keyboard::set_callback(&callback);
		prompt();
	}
}

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

		multiboot_info_t *mbi = multiboot(magic, addr);
		if (!mbi)
			return;

		kfs::io::sti();

		shell::do_ft();
		shell::initialize();

		while (1)
			asm ("hlt");
	}
}
