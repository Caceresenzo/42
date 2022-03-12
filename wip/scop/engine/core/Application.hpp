/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:18:58 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:18:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATION_HPP_
# define APPLICATION_HPP_

#include <string>

class Window;

class Application
{
	private:
		static Application *m_instance;

	private:
		std::string m_name;

	public:
		Application(const std::string &name);

		virtual
		~Application();

	public:
		virtual Window*
		create_window(int width, int height, const std::string &name) = 0;

		virtual Window&
		main_window() = 0;

	public:
		static Application&
		instance();
};

#endif /* APPLICATION_HPP_ */
