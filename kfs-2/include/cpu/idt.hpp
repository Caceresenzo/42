/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:35:56 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/30 18:35:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDT_HPP_
# define IDT_HPP_

# include <types.h>

namespace kfs::idt
{
	typedef struct
	{
			uint16_t isr_low; // The lower 16 bits of the ISR's address
			uint16_t kernel_cs; // The GDT segment selector that the CPU will load into CS before calling the ISR
			uint8_t reserved; // Set to zero
			uint8_t attributes; // Type and attributes; see the IDT page
			uint16_t isr_high; // The higher 16 bits of the ISR's address
	} __attribute__((packed)) entry_t;

	typedef struct
	{
			uint16_t limit;
			uint32_t base;
	} __attribute__((packed)) idtr_t;

	void initialize();
	void set(int32_t id, void *isr, uint8_t flags);
	void flush(uint32_t address);
}

#endif /* GDT_HPP_ */
