/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:40:07 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/28 20:40:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_HPP_
# define MESH_HPP_

#include <engine/math/Box.hpp>
#include <engine/math/vector.hpp>
#include <engine/mesh/Vertex.hpp>
#include <engine/shader/Attribute.hpp>
#include <engine/texture/Texture.hpp>
#include <engine/vertex/VertexArrayObject.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <GL/glew.h>
#include <lang/reference/SharedReference.hpp>
#include <utility>
#include <vector>

class WhiteShader;
class VertexArrayObject;

class Mesh
{
	public:
		enum Mode
		{
			LINE = GL_LINES,
			TRIANGLE = GL_TRIANGLES
		};

	public:
		std::vector<Vertex<3> > vertices;
		std::vector<unsigned int> indices;
		bool has_texture;
		Mode mode;
		SharedReference<VertexArrayObject> vertex_array_object;
		SharedReference<VertexBufferObject> vertex_buffer_object;
		SharedReference<VertexBufferObject> element_buffer_object;

	public:
		Mesh(const std::vector<Vertex<3> > &vertices, const std::vector<unsigned int> &indices, bool has_texture, Mode mode = TRIANGLE);

		virtual
		~Mesh();

	public:
		void
		store();

		void
		align(Vector<3, float> center);

		BoundingBox<3, float>
		compute_bounding_box() const;
};

#endif /* MESH_HPP_ */
