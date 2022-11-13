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
		enum PressState
		{
			UNPRESSED,
			JUST_PRESSED,
			PRESSED,
		};

		enum Key
		{
			A = 'a',
			B = 'b',
			C = 'c',
			D = 'd',
			F = 'f',
			I = 'i',
			J = 'j',
			K = 'k',
			L = 'l',
			O = 'o',
			P = 'p',
			Q = 'q',
			S = 's',
			V = 'V',
			W = 'w',
			X = 'x',
			Y = 'y',
			Z = 'z',
			SPACE = ' ',
			ESCAPE = 27,
			SHIFT = 254,
		};

	private:
		static PressState s_states[UCHAR_MAX];

	private:
		Keyboard();

	public:
		static PressState
		is_pressed(Key key);

		static void
		set_pressed(Key key, bool state);

		static void
		increment();
};

#endif /* KEYBOARD_HPP_ */
