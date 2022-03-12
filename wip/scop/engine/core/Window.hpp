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

#include <engine/math/vector.hpp>
#include <string>

class Window
{
	public:
		virtual
		~Window();

	public:
		virtual void
		set_title(const std::string &title) = 0;

		virtual bool
		is_fullscreen() const = 0;

		virtual void
		set_fullscreen(bool fullscreen) = 0;

		virtual void
		toggle_fullscreen();

		virtual Vector<2, int>
		position() const = 0;

		virtual Vector<2, int>
		size() const = 0;
};

#endif /* WINDOW_HPP_ */
