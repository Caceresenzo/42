/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Attribute.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:47:18 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 13:47:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATTRIBUTE_HPP_
# define ATTRIBUTE_HPP_

#include <engine/opengl.hpp>
#include <engine/shader/ShaderVariable.hpp>
#include <GL/glew.h>
#include <string>

class ShaderProgram;

class Attribute :
		public ShaderVariable
{
	private:
		GLenum m_size;
		GLenum m_data_type;
		GLboolean m_normalized;

	protected:
		Attribute(const std::string &name, GLint size, GLenum data_type, GLenum normalized);

		virtual
		~Attribute();

	public:
		void
		enable();

		void
		disable();

		void
		link(GLsizei stride = 0, const void *pointer = NULL);

	protected:
		virtual GLint
		find_location(GLuint program_id, const char *name) const;
};

#endif /* ATTRIBUTE_HPP_ */
