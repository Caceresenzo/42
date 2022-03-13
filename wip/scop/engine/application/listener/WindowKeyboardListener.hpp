/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WindowKeyboardListener.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:40:41 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 19:40:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOWKEYBOARDLISTENER_HPP_
# define WINDOWKEYBOARDLISTENER_HPP_

#include <engine/control/Keyboard.hpp>

class Window;

class WindowKeyboardListener
{
	public:
		virtual
		~WindowKeyboardListener();

	public:
		virtual void
		on_key_press(Window &window, Keyboard::Key key);

		virtual void
		on_key_release(Window &window, Keyboard::Key key);
};

#endif /* WINDOWKEYBOARDLISTENER_HPP_ */
