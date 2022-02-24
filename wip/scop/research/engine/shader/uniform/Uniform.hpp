/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uniform.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:47:18 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 13:47:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIFORM_HPP_
# define UNIFORM_HPP_

#include <GL/glew.h>
#include <opengl.hpp>
#include <string>

class ShaderProgram;

class Uniform
{
	private:
		std::string m_name;
		GLint m_location;

	protected:
		Uniform(const std::string &name);
		Uniform(const Uniform &other);

		virtual
		~Uniform();

		Uniform&
		operator=(const Uniform &other);

	public:
		const std::string&
		name() const;

		GLint
		location() const;

		void
		locate(const ShaderProgram &program);
};

#endif /* UNIFORM_HPP_ */
