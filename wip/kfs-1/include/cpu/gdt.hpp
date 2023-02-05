/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:35:56 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/30 18:35:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GDT_HPP_
# define GDT_HPP_

# include <types.h>

namespace kfs::gdt
{
	typedef struct
	{
			uint16_t limit_low;
			uint16_t base_low;
			uint8_t base_middle;
			uint8_t access;
			uint8_t granularity;
			uint8_t base_high;
	} __attribute__((packed)) entry_t;

	typedef struct
	{
			uint16_t limit;
			uint32_t base;
	} __attribute__((packed)) ptr_t;

	void initialize();
	void set(int32_t id, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);
	void flush(uint32_t address);
}

#endif /* GDT_HPP_ */
