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

#include <cpu/idt.hpp>
#include <cpu/io.hpp>
#include <cpu/pit.hpp>
#include <stdio.h>

extern "C"
{
	void __asm_kfs_idt_flush(uint32_t address);
	extern void *__asm_kfs_isr_stub_table[];
}

namespace kfs::idt
{
	static entry_t idt[256] __attribute__((aligned(0x10))) = { 0 };
	static idtr_t idtr;

	void initialize()
	{
		idtr.base = (uint32_t)&idt[0];
		idtr.limit = (uint16_t)(sizeof(idt) - 1);

		for (uint8_t id = 0; id < 32; id++)
			set(id, __asm_kfs_isr_stub_table[id], 0x8E);

		for (uint8_t id = 32; id < 48; id++)
			set(id, __asm_kfs_isr_stub_table[id], 0x8E);

		flush((uint32_t)&idtr);

		kfs::pit::remap(0x20, 0x28);
	}

	void set(int32_t id, void *isr, uint8_t flags)
	{
		entry_t *descriptor = &idt[id];

		descriptor->isr_low = (uint32_t)isr & 0xFFFF;
		descriptor->kernel_cs = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
		descriptor->attributes = flags;
		descriptor->isr_high = (uint32_t)isr >> 16;
		descriptor->reserved = 0;
	}

	void flush(uint32_t address)
	{
		__asm_kfs_idt_flush(address);
	}
}
