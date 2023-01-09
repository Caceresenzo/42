/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexArrayObject.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:31:58 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/26 23:31:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEXARRAYOBJECT_HPP_
# define VERTEXARRAYOBJECT_HPP_

#include <engine/opengl.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <GL/glew.h>
#include <lang/reference/SharedReference.hpp>
#include <utility>
#include <vector>

class VertexArrayObject
{
	private:
		GLuint m_id;

	public:
		VertexArrayObject();

		virtual
		~VertexArrayObject();

	public:
		void
		bind();

		void
		unbind();

		void
		add(SharedReference<VertexBufferObject> &object);
};

#endif /* VERTEXARRAYOBJECT_HPP_ */
