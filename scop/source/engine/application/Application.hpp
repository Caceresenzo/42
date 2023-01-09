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

		~Application();

	public:
		void
		poll_events();

	public:
		static Application&
		instance();
};

#endif /* APPLICATION_HPP_ */
