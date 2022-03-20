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
#include <utility>
#include <vector>

class VertexArrayObject
{
	private:
		typedef typename std::vector<std::pair<VertexBufferObject*, bool> >::const_iterator const_iterator;

	private:
		GLuint m_id;
		std::vector<std::pair<VertexBufferObject*, bool> > m_attached;

	public:
		VertexArrayObject();

		virtual
		~VertexArrayObject();

	public:
		bool
		add(VertexBufferObject &object, bool auto_delete = false);

		VertexBufferObject&
		get(size_t index);

		void
		bind(bool with_attached = false);

		void
		unbind(bool with_attached = false);
};

#endif /* VERTEXARRAYOBJECT_HPP_ */