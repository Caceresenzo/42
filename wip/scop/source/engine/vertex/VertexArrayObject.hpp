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
		typedef std::vector<SharedReference<VertexBufferObject>> vector;
		typedef typename vector::iterator iterator;

	private:
		GLuint m_id;
		vector m_attached;

	public:
		VertexArrayObject();

		virtual
		~VertexArrayObject();

	public:
		bool
		add(SharedReference<VertexBufferObject> &object);

		SharedReference<VertexBufferObject>
		get(size_t index);

		void
		bind(bool with_attached = false);

		void
		unbind(bool with_attached = false);
};

#endif /* VERTEXARRAYOBJECT_HPP_ */
