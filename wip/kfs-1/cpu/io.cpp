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

	void hlt(void)
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
}
