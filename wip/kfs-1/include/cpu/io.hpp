/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:35:56 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/30 18:35:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_HPP_
# define IO_HPP_

# include <types.h>

namespace kfs::io
{
	void sti(void);
	void cli(void);
	void halt(void);

	void outb(uint16_t port, uint8_t value);
	void outw(uint16_t port, uint16_t value);
	uint8_t inb(uint16_t port);
	void wait(void);

	enum cpuid_requests
	{
		CPUID_GETVENDORSTRING,
		CPUID_GETFEATURES,
		CPUID_GETTLB,
		CPUID_GETSERIAL,
	};

	void cpuid(cpuid_requests code, uint32_t *a, uint32_t *d);
	void cpuid(cpuid_requests code, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);
	bool cpuid(cpuid_requests code, char *buffer);

	void reboot();
	void shutdown();
}

#endif /* IO_HPP_ */
