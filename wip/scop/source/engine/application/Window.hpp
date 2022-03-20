/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:17:46 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:17:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_HPP_
# define WINDOW_HPP_

#include <engine/application/listener/WindowKeyboardListener.hpp>
#include <engine/application/listener/WindowMouseListener.hpp>
#include <engine/control/Keyboard.hpp>
#include <engine/math/vector.hpp>
#include <lang/reference/SharedReference.hpp>
#include <string>
#include <vector>

struct GLFWwindow;

class Window
{
	private:
		GLFWwindow *m_window;
		Vector<4, int> m_old_position_and_size;

	public:
		std::vector<SharedReference<WindowMouseListener> > mouse_listeners;
		std::vector<SharedReference<WindowKeyboardListener> > keyboard_listeners;

	public:
		Window(int width, int height);

		virtual
		~Window();

	public:
		void
		set_as_current();

		void
		set_title(const std::string &title);

		bool
		is_fullscreen() const;

		void
		set_fullscreen(bool fullscreen);

		void
		toggle_fullscreen();

		void
		swap_buffers();

		void
		set_cursor_position(const Vector<2, int> &position);

		void
		set_should_close(bool should_close);

		bool
		is_should_be_closed() const;

		Vector<2, int>
		position() const;

		Vector<2, int>
		size() const;

	public:
		void
		fire_mouse_move(const Vector<2, int> &position);

		void
		fire_mouse_scroll(const Vector<2, int> &offset);

		void
		fire_mouse_key_press(Keyboard::Key key);

		void
		fire_mouse_key_release(Keyboard::Key key);

	public:
		static Window&
		current();

		static Window*
		resolve(GLFWwindow *raw_window);

		static Window&
		ensure_resolve(GLFWwindow *raw_window);
};

#endif /* WINDOW_HPP_ */
