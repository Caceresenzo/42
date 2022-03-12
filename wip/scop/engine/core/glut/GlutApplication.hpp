/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlutApplication.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:40:34 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:40:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLUTAPPLICATION_HPP_
# define GLUTAPPLICATION_HPP_

#include <engine/core/Application.hpp>
#include <string>

class GlutWindow;

class GlutApplication :
		public Application
{
	private:
		GlutWindow *m_main_window;

	public:
		GlutApplication(const std::string &name);

		virtual
		~GlutApplication();

	public:
		virtual Window*
		create_window(int width, int height, const std::string &name);

		virtual Window&
		main_window();
};

#endif /* GLUTAPPLICATION_HPP_ */
