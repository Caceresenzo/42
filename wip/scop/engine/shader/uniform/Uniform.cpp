/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uniform.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:28:28 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 21:28:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/shader/uniform/Uniform.hpp>

Uniform::Uniform(const std::string &name) :
		ShaderVariable(name)
{
}

Uniform::~Uniform()
{
}

GLint
Uniform::find_location(GLuint program_id, const char *name) const
{
	return (glGetUniformLocation(program_id, name));
}
