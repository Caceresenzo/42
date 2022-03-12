/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwApplication.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:40:47 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:40:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFWAPPLICATION_HPP_
# define GLFWAPPLICATION_HPP_

#include <engine/core/Application.hpp>

class GlfwApplication :
		public Application
{
	public:
		GlfwApplication();

		virtual
		~GlfwApplication();
};

#endif /* GLFWAPPLICATION_HPP_ */
