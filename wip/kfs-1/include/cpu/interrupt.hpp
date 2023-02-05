/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrupt.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:35:56 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/30 18:35:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERRUPT_HPP_
# define INTERRUPT_HPP_

# include <types.h>

namespace kfs::interrupt
{
	constexpr uint32_t IRQ_OFFSET = 32;
	constexpr uint32_t IRQ0 = IRQ_OFFSET + 0;
	constexpr uint32_t IRQ1 = IRQ_OFFSET + 1;
	constexpr uint32_t IRQ2 = IRQ_OFFSET + 2;
	constexpr uint32_t IRQ3 = IRQ_OFFSET + 3;
	constexpr uint32_t IRQ4 = IRQ_OFFSET + 4;
	constexpr uint32_t IRQ5 = IRQ_OFFSET + 5;
	constexpr uint32_t IRQ6 = IRQ_OFFSET + 6;
	constexpr uint32_t IRQ7 = IRQ_OFFSET + 7;
	constexpr uint32_t IRQ8 = IRQ_OFFSET + 8;
	constexpr uint32_t IRQ9 = IRQ_OFFSET + 9;
	constexpr uint32_t IRQ10 = IRQ_OFFSET + 10;
	constexpr uint32_t IRQ11 = IRQ_OFFSET + 11;
	constexpr uint32_t IRQ12 = IRQ_OFFSET + 12;
	constexpr uint32_t IRQ13 = IRQ_OFFSET + 13;
	constexpr uint32_t IRQ14 = IRQ_OFFSET + 14;
	constexpr uint32_t IRQ15 = IRQ_OFFSET + 15;

	typedef struct registers
	{
			uint32_t ds; // Data segment selector

			// Pushed by pusha.
			uint32_t edi;
			uint32_t esi;
			uint32_t ebp;
			uint32_t esp;
			uint32_t ebx;
			uint32_t edx;
			uint32_t ecx;
			uint32_t eax;

			// Interrupt number and error code (if applicable)
			uint32_t int_no;
			uint32_t err_code;

			// Pushed by the processor automatically.
			uint32_t eip;
			uint32_t cs;
			uint32_t eflags;
			uint32_t useresp;
			uint32_t ss;
	} registers_t;

	void initialize(void);

	void handle(registers_t regs);
	void install(int id, const char *name, void (*function)(registers_t regs));
}

#endif /* INTERRUPT_HPP_ */
