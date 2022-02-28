/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Keyboard.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 23:54:03 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/27 23:54:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_HPP_
# define KEYBOARD_HPP_

#include <engine/opengl.hpp>
#include <climits>

class Keyboard
{
	public:
		enum Key
		{
			A = 'a',
			D = 'd',
			I = 'i',
			J = 'j',
			K = 'k',
			L = 'l',
			Q = 'q',
			S = 's',
			Z = 'z',
			SPACE = ' ',
		};

	private:
		static bool s_states[UCHAR_MAX];

	private:
		Keyboard();

	public:
		static bool
		is_pressed(Key key);

		static void
		set_pressed(Key key, bool state);
};

#endif /* KEYBOARD_HPP_ */
