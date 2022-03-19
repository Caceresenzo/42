/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyboardListener.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:47:37 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 19:47:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARDLISTENER_HPP_
# define KEYBOARDLISTENER_HPP_

#include <engine/application/listener/WindowKeyboardListener.hpp>

class KeyboardListener :
		public WindowKeyboardListener
{
	public:
		KeyboardListener();

		virtual
		~KeyboardListener();

	public:
		virtual void
		on_key_press(Window &window, Keyboard::Key key);

		virtual void
		on_key_release(Window &window, Keyboard::Key key);
};

#endif /* KEYBOARDLISTENER_HPP_ */
