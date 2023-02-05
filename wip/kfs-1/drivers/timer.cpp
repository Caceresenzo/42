/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 19:54:31 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/05 19:54:31 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drivers/timer.hpp>
#include <cpu/interrupt.hpp>
#include <stdio.h>

namespace kfs::timer
{
	static uint32_t g_tick_count = 0;

	void handle(kfs::interrupt::registers_t regs)
	{
		++g_tick_count;
	}

	void initialize(void)
	{
		kfs::interrupt::install(kfs::interrupt::IRQ0, "Timer", handle);
	}
	
	uint32_t tick_count()
	{
		return (g_tick_count);
	}
}
