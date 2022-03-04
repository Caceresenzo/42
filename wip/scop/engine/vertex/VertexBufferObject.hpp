/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexBufferObject.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:51:05 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/26 21:51:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEXBUFFEROBJECT_HPP_
# define VERTEXBUFFEROBJECT_HPP_

#include <engine/opengl.hpp>
#include <GL/glew.h>
#include <vector>

class VertexBufferObject
{
	public:
		enum BufferType
		{
			ARRAY = GL_ARRAY_BUFFER,
			ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER,
		};

		enum UsageType
		{
			STATIC_DRAW = GL_STATIC_DRAW,
			DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		};

	private:
		GLuint m_id;
		BufferType m_type;
		UsageType m_usage;

	public:
		VertexBufferObject(BufferType type, UsageType usage);

		virtual
		~VertexBufferObject();

	public:
		void
		bind();

		void
		unbind();

		void
		store(GLsizeiptr size, const void *data, bool and_unbind = true);

		template<typename T>
			void
			store(const std::vector<T> &data, bool and_unbind = true)
			{
				store(data.size() * sizeof(T), data.data(), and_unbind);
			}

	public:
		inline GLuint
		id() const
		{
			return (m_id);
		}
};

#endif /* VERTEXBUFFEROBJECT_HPP_ */
