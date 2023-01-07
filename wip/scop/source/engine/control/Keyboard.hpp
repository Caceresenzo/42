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
			N = 'n',
			O = 'o',
			P = 'p',
			Q = 'q',
			R = 'r',
			S = 's',
			V = 'V',
			W = 'w',
			X = 'x',
			Y = 'y',
			Z = 'z',
			SPACE = ' ',
			ESCAPE = 27,
			LEFT_SHIFT = 254,
			RIGHT_SHIFT,
			LEFT_CONTROL,
			RIGHT_CONTROL,
			RIGHT,
			LEFT,
			DOWN,
			UP,
			_LENGTH
		};

	private:
		static PressState s_states[_LENGTH];

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
