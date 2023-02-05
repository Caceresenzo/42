/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pit.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:49:26 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/05 18:49:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/io.hpp>
#include <stdio.h>
#include "../include/cpu/interrupt.hpp"

#define PIC1            0x20	/* IO base address for master PIC */
#define PIC2            0xA0	/* IO base address for slave PIC */
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)

#define ICW1_ICW4       0x01	/* ICW4 (not) needed */
#define ICW1_SINGLE     0x02	/* Single (cascade) mode */
#define ICW1_INTERVAL4  0x04	/* Call address interval 4 (8) */
#define ICW1_LEVEL      0x08	/* Level triggered (edge) mode */
#define ICW1_INIT       0x10	/* Initialization - required! */

#define ICW4_8086       0x01	/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO       0x02	/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE  0x08	/* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C	/* Buffered mode/master */
#define ICW4_SFNM       0x10	/* Special fully nested (not) */

namespace kfs::pit
{
	void remap(int offset1, int offset2)
	{
		uint8_t a1 = kfs::io::inb(PIC1_DATA);
		uint8_t a2 = kfs::io::inb(PIC2_DATA);

		kfs::io::outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); // starts the initialization sequence (in cascade mode)
		kfs::io::wait();
		kfs::io::outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
		kfs::io::wait();
		kfs::io::outb(PIC1_DATA, offset1); // ICW2: Master PIC vector offset
		kfs::io::wait();
		kfs::io::outb(PIC2_DATA, offset2); // ICW2: Slave PIC vector offset
		kfs::io::wait();
		kfs::io::outb(PIC1_DATA, 4); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
		kfs::io::wait();
		kfs::io::outb(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)
		kfs::io::wait();

		kfs::io::outb(PIC1_DATA, ICW4_8086);
		kfs::io::wait();
		kfs::io::outb(PIC2_DATA, ICW4_8086);
		kfs::io::wait();

		kfs::io::outb(PIC1_DATA, a1); // restore saved masks.
		kfs::io::outb(PIC2_DATA, a2);
	}
}
