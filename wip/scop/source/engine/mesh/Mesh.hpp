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
#include <engine/texture/Texture.hpp>
#include <engine/vertex/VertexArrayObject.hpp>
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
		std::vector<Vector<3, float> > vertices;
		std::vector<Vector<2, float> > textures;
		std::vector<unsigned int> indices;
		Mode mode;

	public:
		Mesh(const std::vector<Vector<3, float> > &vertices, const std::vector<Vector<2, float> > &textures, const std::vector<unsigned int> &indices, Mode mode = TRIANGLE);

		virtual
		~Mesh();

	public:
		void
		align(Vector<3, float> center);

		BoundingBox<3, float>
		compute_bounding_box() const;
};

#endif /* MESH_HPP_ */
