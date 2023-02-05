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
