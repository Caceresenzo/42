/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiboot.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:49:26 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/05 18:49:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/multiboot.hpp>
#include <drivers/vga.hpp>
#include <drivers/keyboard.hpp>
#include <multiboot.h>
#include <stdio.h>
#include <elf.h>
#include <string.h>

#define CHECK_FLAG(flags, bit) ((flags) & (1 << (bit)))

namespace kfs::multiboot
{
	static multiboot_info_t *g_info = NULL;

	bool initialize(unsigned long magic, unsigned long addr)
	{
		multiboot_info_t *info = (multiboot_info_t*)addr;

		if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		{
			printk("multiboot: invalid magic number: 0x%x\n", (unsigned)magic);
			return (false);
		}

		g_info = info;
		return (true);
	}

	void dump(void)
	{
		if (CHECK_FLAG(g_info->flags, 0))
			printk("mem_lower = %uKB, mem_upper = %uKB\n",
				(unsigned)g_info->mem_lower, (unsigned)g_info->mem_upper);

		/* Is boot_device valid? */
		if (CHECK_FLAG(g_info->flags, 1))
			printk("boot_device = 0x%x\n", (unsigned)g_info->boot_device);

		/* Is the command line passed? */
		if (CHECK_FLAG(g_info->flags, 2))
			printk("cmdline = %s\n", (char*)g_info->cmdline);

		/* Are mods_* valid? */
		if (CHECK_FLAG(g_info->flags, 3))
		{
			multiboot_module_t *mod;
			int i;

			printk("mods_count = %d, mods_addr = 0x%x\n",
				(int)g_info->mods_count, (int)g_info->mods_addr);
			for (i = 0, mod = (multiboot_module_t*)g_info->mods_addr;
				i < g_info->mods_count;
				i++, mod++)
				printk(" mod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n",
					(unsigned)mod->mod_start,
					(unsigned)mod->mod_end,
					(char*)mod->cmdline);
		}

		/* Are mmap_* valid? */
		if (CHECK_FLAG(g_info->flags, 6))
		{
			multiboot_memory_map_t *mmap;

			printk("mmap_addr = 0x%x, mmap_length = 0x%x\n",
				(unsigned)g_info->mmap_addr, (unsigned)g_info->mmap_length);
			for (mmap = (multiboot_memory_map_t*)g_info->mmap_addr;
				(unsigned long)mmap < g_info->mmap_addr + g_info->mmap_length;
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
	}

	const multiboot_info_t* get(void)
	{
		return (g_info);
	}
}
