/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:35:35 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/30 18:35:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/gdt.hpp>
#include <stdio.h>

#define NULL_SEGMENT_ACCESS 0
#define CODE_SEGMENT_ACCESS 0x9A
#define DATA_SEGMENT_ACCESS 0x92
#define USERM_CODE_SEGMENT_ACCESS 0xFA
#define USERM_DATA_SEGMENT_ACCESS 0xF2

extern "C"
{
	void __asm_kfs_gdt_flush(uint32_t address);
}

namespace kfs::gdt
{
	static entry_t gdt_entries[5];
	static ptr_t gdt_ptr;

	void initialize()
	{
		gdt_ptr.limit = (sizeof(entry_t) * 5) - 1;
		gdt_ptr.base = (uint32_t)&gdt_entries;

		set(0, 0, 0, NULL_SEGMENT_ACCESS, 0);
		set(1, 0, 0xFFFFFFFF, CODE_SEGMENT_ACCESS, 0xCF);
		set(2, 0, 0xFFFFFFFF, DATA_SEGMENT_ACCESS, 0xCF);
		set(3, 0, 0xFFFFFFFF, USERM_CODE_SEGMENT_ACCESS, 0xCF);
		set(4, 0, 0xFFFFFFFF, USERM_DATA_SEGMENT_ACCESS, 0xCF);

		flush((uint32_t)&gdt_ptr);

		printk("[gdt]: initialized\n");
	}

	void set(int32_t id, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
	{
		gdt_entries[id].base_low = base & 0xFFFF;
		gdt_entries[id].base_middle = (base >> 16) & 0xFF;
		gdt_entries[id].base_high = (base >> 24) & 0xFF;
		gdt_entries[id].limit_low = (limit & 0xFFFF);
		gdt_entries[id].granularity = (limit >> 16) & 0x0F;
		gdt_entries[id].granularity |= granularity & 0xF0;
		gdt_entries[id].access = access;
	}

	void flush(uint32_t address)
	{
		__asm_kfs_gdt_flush(address);
	}

}
