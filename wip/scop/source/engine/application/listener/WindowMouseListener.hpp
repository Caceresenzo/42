/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WindowMouseListener.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:39:03 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 19:39:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOWMOUSELISTENER_HPP_
# define WINDOWMOUSELISTENER_HPP_

#include <engine/math/vector.hpp>

class Window;

class WindowMouseListener
{
	public:
		virtual
		~WindowMouseListener();

	public:
		virtual void
		on_mouse_move(Window &window, const Vector<2, int> &position);

		virtual void
		on_mouse_scroll(Window &window, const Vector<2, int> &offset);
};

#endif /* WINDOWMOUSELISTENER_HPP_ */
