/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:08:20 by ecaceres          #+#    #+#             */
/*   Updated: 2022/11/14 16:08:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/model/Model.hpp>

Model::Model(SharedReference<Mesh> mesh, std::vector<SharedReference<Texture>> textures) :
	mesh(mesh),
	textures(textures)
{
	VertexArrayObject *vertex_buffer_array = NULL;

	try
	{
		vertex_buffer_array = new VertexArrayObject();
		vertex_buffer_array->bind();

		VertexBufferObject &element_buffer = *new VertexBufferObject(VertexBufferObject::ELEMENT_ARRAY, VertexBufferObject::STATIC_DRAW);
		vertex_buffer_array->add(element_buffer, true);

		element_buffer.bind();
		element_buffer.store(mesh->indices, false);

		VertexBufferObject &vertex_buffer = *new VertexBufferObject(VertexBufferObject::ARRAY, VertexBufferObject::STATIC_DRAW);
		vertex_buffer_array->add(vertex_buffer, true);

		vertex_buffer.bind();
		vertex_buffer.store(mesh->vertices, false);

		VertexBufferObject &texture_buffer = *new VertexBufferObject(VertexBufferObject::ARRAY, VertexBufferObject::STATIC_DRAW);
		vertex_buffer_array->add(texture_buffer, true);

		texture_buffer.bind();
		texture_buffer.store(mesh->textures, false);

		vertex_buffer_array->unbind();
	}
	catch (...)
	{
		if (vertex_buffer_array)
			delete vertex_buffer_array;
	}

	this->vertex_buffer_array = *vertex_buffer_array;
}

Model::~Model()
{
}
