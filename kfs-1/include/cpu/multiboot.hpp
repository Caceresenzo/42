/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiboot.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:35:56 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/30 18:35:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIBOOT_HPP_
# define MULTIBOOT_HPP_

# include <types.h>
# include <multiboot.h>

namespace kfs::multiboot
{
	bool initialize(unsigned long magic, unsigned long addr);

	void dump(void);
	const multiboot_info_t* get(void);
}

#endif /* MULTIBOOT_HPP_ */
