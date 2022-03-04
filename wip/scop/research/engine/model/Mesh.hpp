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

#include <engine/math/vector.hpp>
#include <engine/vertex/VertexArrayObject.hpp>
#include <vector>

class MeshShader;
class VertexArrayObject;

class Mesh
{
	public:
		enum Mode
		{
			LINE = GL_LINES,
			TRIANGLE = GL_TRIANGLES
		};

	private:
		std::vector<Vector<3, float> > m_vertices;
		std::vector<unsigned int> m_indices;
		Mode m_mode;
		VertexArrayObject *m_vertex_buffer_array;

	public:
		Mesh(const std::vector<Vector<3, float> > &vertices, const std::vector<unsigned int> &indices, Mode mode = TRIANGLE);

		virtual
		~Mesh();

	public:
		void
		render(MeshShader &shader);
};

#endif /* MESH_HPP_ */
