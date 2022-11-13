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
#include <engine/math/MathObject.hpp>
#include <engine/shader/Variable.hpp>
#include <string>

template<typename T>
	class Attribute :
		public Variable
	{
		private:
			GLenum m_size;
			GLenum m_data_type;
			GLboolean m_normalized;

		public:
			Attribute(const std::string &name) :
				Variable(name),
				m_size(MathObject<T>::size),
				m_data_type(GLType<typename MathObject<T>::value_type>::DATA_TYPE),
				m_normalized(false)
			{
			}

			Attribute(const std::string &name, GLint size, GLenum data_type, GLenum normalized) :
				Variable(name),
				m_size(size),
				m_data_type(data_type),
				m_normalized(normalized)
			{
			}

			virtual
			~Attribute()
			{
			}

		public:
			inline void
			enable()
			{
				glEnableVertexAttribArray(location());
				OpenGL::check_error();
			}

			inline void
			disable()
			{
				glDisableVertexAttribArray(location());
				OpenGL::check_error();
			}

			inline void
			link(GLsizei stride = 0, const void *pointer = NULL)
			{
//				std::cout << name() << ":" << __PRETTY_FUNCTION__ << std::endl;
				glVertexAttribPointer(location(), m_size, m_data_type, m_normalized, stride, pointer);
				OpenGL::check_error();
			}

		protected:
			inline virtual GLint
			find_location(GLuint program_id, const char *name) const
			{
				return (glGetAttribLocation(program_id, name));
			}
	};

#endif /* ATTRIBUTE_HPP_ */
