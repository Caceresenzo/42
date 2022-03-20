/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MouseListener.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:48:57 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 19:48:57 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSELISTENER_HPP_
# define MOUSELISTENER_HPP_

#include <engine/application/listener/WindowMouseListener.hpp>
#include <engine/camera/ICamera.hpp>
#include <engine/math/vector.hpp>
#include <lang/reference/SharedReference.hpp>

class Window;

class MouseListener :
		public WindowMouseListener
{
	private:
		SharedReference<ICamera> m_camera;

	public:
		MouseListener(SharedReference<ICamera> &camera);

		virtual
		~MouseListener();

	public:
		virtual void
		on_mouse_move(Window &window, const Vector<2, int> &position);

		virtual void
		on_mouse_scroll(Window &window, const Vector<2, int> &offset);
};

#endif /* MOUSELISTENER_HPP_ */
