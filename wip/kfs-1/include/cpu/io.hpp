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
	void hlt(void);

	void outb(uint16_t port, uint8_t value);
	uint8_t inb(uint16_t port);
	void wait(void);
}

#endif /* IO_HPP_ */
