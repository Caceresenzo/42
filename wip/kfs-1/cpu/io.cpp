/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:35:35 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/30 18:35:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/io.hpp>
#include <stdio.h>
#include <string.h>

namespace kfs::io
{
	void sti(void)
	{
		asm volatile ("sti");
	}

	void cli(void)
	{
		asm volatile ("cli");
	}

	void outb(uint16_t port, uint8_t value)
	{
		asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
	}

	void outw(uint16_t port, uint16_t value)
	{
		asm volatile ("outw %w0, %w1" : : "a" (value), "Nd" (port));
	}

	void halt(void)
	{
		asm volatile ("hlt");
	}

	uint8_t inb(uint16_t port)
	{
		uint8_t result;
		asm volatile("inb %1, %0" : "=a" (result) : "dN" (port));

		return (result);
	}

	void wait(void)
	{
		outb(0x80, 0);
	}

	void cpuid(cpuid_requests code, uint32_t *a, uint32_t *d)
	{
		asm volatile("cpuid" : "=a"(*a), "=d"(*d) : "a"(code) : "ecx", "ebx");
	}

	void cpuid(cpuid_requests code, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
	{
		asm volatile(
			"cpuid"
			: "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
			: "0" (code), "2" (*ecx)
		);
	}

	bool cpuid(cpuid_requests code, char *buffer)
	{
		uint32_t where[4];
		asm volatile("cpuid" : "=a"(*where), "=b"(*(where + 1)), "=c"(*(where + 2)), "=d"(*(where + 3)) : "a"(code));

		if ((int)where[0])
		{
			buffer[0] = (where[1] >> 0) & 0xFF;
			buffer[1] = (where[1] >> 8) & 0xFF;
			buffer[2] = (where[1] >> 16) & 0xFF;
			buffer[3] = (where[1] >> 24) & 0xFF;
			buffer[4] = (where[3] >> 0) & 0xFF;
			buffer[5] = (where[3] >> 8) & 0xFF;
			buffer[6] = (where[3] >> 16) & 0xFF;
			buffer[7] = (where[3] >> 24) & 0xFF;
			buffer[8] = (where[2] >> 0) & 0xFF;
			buffer[9] = (where[2] >> 8) & 0xFF;
			buffer[10] = (where[2] >> 16) & 0xFF;
			buffer[11] = (where[2] >> 24) & 0xFF;
			buffer[12] = '\0';
			return (true);
		}

		return (false);
	}

	void reboot()
	{
		uint8_t good;
		do
		{
			good = inb(0x64);
		}
		while (good & 0x02);

		outb(0x64, 0xFE);
		halt();
	}

	void shutdown()
	{
		/* Bochs & QEMU */
		kfs::io::outw(0xB004, 0x2000);

		/* QEMU */
		kfs::io::outw(0x604, 0x2000);

		/* Virtual Box */
		kfs::io::outw(0x4004, 0x3400);
	}
}
