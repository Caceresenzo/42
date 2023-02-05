#include <drivers/vga.hpp>
#include <cpu/gdt.hpp>
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
			printk(" size = 0x%x, base_addr = 0x%x%08x,"
				" length = 0x%x%08x, type = 0x%x\n",
				(unsigned)mmap->size,
				(unsigned)(mmap->addr >> 32),
				(unsigned)(mmap->addr & 0xffffffff),
				(unsigned)(mmap->len >> 32),
				(unsigned)(mmap->len & 0xffffffff),
				(unsigned)mmap->type);
	}

	return (mbi);
}

extern "C"
{
	void kmain(unsigned long magic, unsigned long addr)
	{
		kfs::vga::initialize();

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

		multiboot_info_t *mbi = multiboot(magic, addr);
		if (!mbi)
			return;

		kfs::gdt::initialize();
	}
}
