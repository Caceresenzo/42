/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwWindow.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:32:24 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:32:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFWWINDOW_HPP_
# define GLFWWINDOW_HPP_

#include <engine/core/Window.hpp>
#include <engine/math/vector.hpp>

struct GLFWwindow;

class GlfwWindow :
		public Window
{
	private:
		GLFWwindow *m_window;

	public:
		virtual bool
		is_fullscreen() const;

		virtual void
		set_fullscreen(bool fullscreen);

		virtual void
		toggle_fullscreen();

		virtual Vector<2, int>
		size() const;
};

#endif /* GLFWWINDOW_HPP_ */
