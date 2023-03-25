/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrupt.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:35:35 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/30 18:35:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/interrupt.hpp>
#include <cpu/io.hpp>
#include <stdio.h>
#include <string.h>

extern "C"
{
	void __asm_kfs_isr_handler(kfs::interrupt::registers_t regs)
	{
		kfs::interrupt::handle(regs);
	}

	void __asm_kfs_irq_handler(kfs::interrupt::registers_t regs)
	{
		// Send an EOI (end of interrupt) signal to the PICs.
		// If this interrupt involved the slave.
		if (regs.int_no >= 40)
		{
			// Send reset signal to slave.
			kfs::io::outb(0xA0, 0x20);
		}

		// Send reset signal to master. (As well as slave, if necessary).
		kfs::io::outb(0x20, 0x20);

		kfs::interrupt::handle(regs);
	}
}

namespace kfs::interrupt
{
	typedef struct
	{
			char name[32];
			void (*function)(registers_t regs);
	} handler_t;

	static handler_t handlers[255] = { 0 };

	static const char *errors[32] = {
		[0x00] = "Division by zero exception",
		[0x01] = "Debug exception",
		[0x02] = "Non maskable interrupt",
		[0x03] = "Breakpoint exception",
		[0x04] = "'Into detected overflow'",
		[0x05] = "Out of bounds exception",
		[0x06] = "Invalid opcode exception",
		[0x07] = "No coprocessor exception",
		[0x08] = "Double fault (code)",
		[0x09] = "Coprocessor segment overrun",
		[0x0a] = "Bad TSS (code)",
		[0x0b] = "Segment not present (code)",
		[0x0c] = "Stack fault (code)",
		[0x0d] = "General protection fault (code)",
		[0x0e] = "Page fault (code)",
		[0x0f] = "Unknown interrupt exception",
		[0x10] = "Coprocessor fault",
		[0x11] = "Alignment check exception",
		[0x12] = "Machine check exception",
		[0x13] = "Reserved",
		[0x14] = "Reserved",
		[0x15] = "Reserved",
		[0x16] = "Reserved",
		[0x17] = "Reserved",
		[0x18] = "Reserved",
		[0x19] = "Reserved",
		[0x1a] = "Reserved",
		[0x1b] = "Reserved",
		[0x1c] = "Reserved",
		[0x1d] = "Reserved",
		[0x1e] = "Reserved",
		[0x1f] = "Reserved",
	};
	
	void error(registers_t regs)
	{
		const char *name = errors[regs.int_no];

		printk("[interrupt] no=%d error=\"%s\" code=%b\n", regs.int_no, name, regs.err_code);

		kfs::io::cli();
		kfs::io::halt();
	}
	
	void unhandled(registers_t regs)
	{
		printk("[interrupt] unhandled no=%d code=%b\n", regs.int_no, regs.err_code);

		kfs::io::cli();
		kfs::io::halt();
	}

	void initialize(void)
	{
		for (uint8_t index = 0; index < countof(errors); ++index)
			install(index, errors[index], error);
	}

	void handle(registers_t regs)
	{
		handler_t &handler = handlers[regs.int_no];
		if (handler.function)
			handler.function(regs);
		else
			unhandled(regs);
	}

	void install(int id, const char *name, void (*function)(registers_t regs))
	{
		handler_t &handler = handlers[id];

		strcpy(handler.name, name);
		handler.function = function;
	}

}
