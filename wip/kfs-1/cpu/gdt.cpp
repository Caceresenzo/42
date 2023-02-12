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

#define KERNEL_CODE_SEGMENT_SELECTOR   0x08
#define KERNEL_DATA_SEGMENT_SELECTOR   0x10
#define KERNEL_STACK_SEGMENT_SELECTOR  0x18
#define USER_CODE_SEGMENT_SELECTOR     0x20
#define USER_DATA_SEGMENT_SELECTOR     0x28
#define USER_STACK_SEGMENT_SELECTOR    0x30

#define ACCESS_ACCESSED              (1 << 0)
#define ACCESS_READ_WRITE            (1 << 1)
#define ACCESS_DIRECTION_CONFORMING  (1 << 2)
#define ACCESS_EXECUTABLE            (1 << 3)
#define ACCESS_NOT_SYSTEM            (1 << 4)
#define ACCESS_PRIVILEGE(x)          (x << 5)
#define ACCESS_PRESENT               (1 << 7)

#define FLAGS_LONG_MODE              (1 << 1)
#define FLAGS_SIZE_32                (1 << 2)
#define FLAGS_GRANULARITY_PAGE       (1 << 3)

#define DEFAULT_FLAGS        (FLAGS_SIZE_32 | FLAGS_GRANULARITY_PAGE)
#define DEFAULT_CODE_ACCESS  (ACCESS_READ_WRITE | ACCESS_NOT_SYSTEM | ACCESS_PRESENT | ACCESS_EXECUTABLE)
#define DEFAULT_DATA_ACCESS  (ACCESS_READ_WRITE | ACCESS_NOT_SYSTEM | ACCESS_PRESENT)
#define DEFAULT_STACK_ACCESS (ACCESS_READ_WRITE | ACCESS_NOT_SYSTEM | ACCESS_PRESENT | ACCESS_DIRECTION_CONFORMING)

#define KERNEL_CODE_SEGMENT_ACCESS   (DEFAULT_CODE_ACCESS  | ACCESS_PRIVILEGE(0))
#define KERNEL_DATA_SEGMENT_ACCESS   (DEFAULT_DATA_ACCESS  | ACCESS_PRIVILEGE(0))
#define KERNEL_STACK_SEGMENT_ACCESS  (DEFAULT_STACK_ACCESS | ACCESS_PRIVILEGE(0))

#define USER_CODE_SEGMENT_ACCESS   (DEFAULT_CODE_ACCESS  | ACCESS_PRIVILEGE(3))
#define USER_DATA_SEGMENT_ACCESS   (DEFAULT_DATA_ACCESS  | ACCESS_PRIVILEGE(3))
#define USER_STACK_SEGMENT_ACCESS  (DEFAULT_STACK_ACCESS | ACCESS_PRIVILEGE(3))

extern "C"
{
	void __asm_kfs_gdt_flush(uint32_t address);
}

namespace kfs::gdt
{
	__attribute__((section(".gdt")))
	static entry_t gdt_entries[7];

	static ptr_t gdt_ptr;

	void initialize()
	{
		gdt_ptr.limit = sizeof(gdt_entries) - 1;
		gdt_ptr.base = (uint32_t)&gdt_entries;

		set(0, 0, 0, 0, 0, "null");
		set(1, 0, 0xFFFFF, KERNEL_CODE_SEGMENT_ACCESS, DEFAULT_FLAGS, "kernel.code");
		set(2, 0, 0xFFFFF, KERNEL_DATA_SEGMENT_ACCESS, DEFAULT_FLAGS, "kernel.data");
		set(3, 0, 0xFFFFF, KERNEL_STACK_SEGMENT_ACCESS, DEFAULT_FLAGS, "kernel.stack");
		set(4, 0, 0xFFFFF, USER_CODE_SEGMENT_ACCESS, DEFAULT_FLAGS, "user.code");
		set(5, 0, 0xFFFFF, USER_DATA_SEGMENT_ACCESS, DEFAULT_FLAGS, "user.data");
		set(6, 0, 0xFFFFF, USER_STACK_SEGMENT_ACCESS, DEFAULT_FLAGS, "user.stack");

		flush((uint32_t)&gdt_ptr);

		printk("[gdt] initialized (at=%p)\n", gdt_ptr.base);
	}

	void set(int32_t id, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags, const char *comment)
	{
		gdt_entries[id].base_low = base & 0xffff;
		gdt_entries[id].base_middle = (base >> 16) & 0xff;
		gdt_entries[id].base_high = (base >> 24) & 0xff;
		gdt_entries[id].limit_low = limit & 0xffff;
		gdt_entries[id].limit_high = (limit >> 16) & 0x0f;
		gdt_entries[id].flags = flags & 0xf;
		gdt_entries[id].access = access;

		printk("[gdt] id=%d base=%x limit=%x access=%x flags=%x name=%s\n", id, base, limit, access, flags, comment);
	}

	void flush(uint32_t address)
	{
		__asm_kfs_gdt_flush(address);
	}
}
