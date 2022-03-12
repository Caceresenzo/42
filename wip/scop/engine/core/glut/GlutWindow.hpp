/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlutWindow.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:18:19 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:18:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLUTWINDOW_HPP_
# define GLUTWINDOW_HPP_

#include <engine/core/Window.hpp>

class GlutWindow :
		public Window
{
	private:
		int m_window;

	public:
		GlutWindow(int width, int height);

		virtual
		~GlutWindow();

	public:
		virtual void
		set_title(const std::string &title);

		virtual bool
		is_fullscreen() const;

		virtual void
		set_fullscreen(bool fullscreen);

		virtual void
		toggle_fullscreen();

		virtual Vector<2, int>
		position() const;

		virtual Vector<2, int>
		size() const;

	protected:
		void
		set_active() const;
};

#endif /* GLUTWINDOW_HPP_ */
