/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:03:52 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/05 20:03:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_HPP_
# define KEYBOARD_HPP_

# include <types.h>

namespace kfs::keyboard
{
	typedef struct
	{
			bool state;
			bool shift;
			uint32_t scan_code;
			uint8_t letter;
	} key_t;

	void initialize(void);
	void set_callback(void (*function)(key_t));
}

#endif /* KEYBOARD_HPP_ */
