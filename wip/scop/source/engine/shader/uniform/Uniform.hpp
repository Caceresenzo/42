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

#include <engine/opengl.hpp>
#include <engine/shader/ShaderVariable.hpp>
#include <GL/glew.h>
#include <string>

class ShaderProgram;

class Uniform :
		public ShaderVariable
{
	protected:
		Uniform(const std::string &name);

		virtual
		~Uniform();

	protected:
		virtual GLint
		find_location(GLuint program_id, const char *name) const;
};

#endif /* UNIFORM_HPP_ */
