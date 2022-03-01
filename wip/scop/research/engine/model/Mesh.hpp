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
	private:
		std::vector<Vector<3, float> > m_vertices;
		std::vector<unsigned int> m_indices;
		VertexArrayObject *m_vertex_buffer_array;

	public:
		Mesh(const std::vector<Vector<3, float> > &vertices, const std::vector<unsigned int> &indices);

		virtual
		~Mesh();

	public:
		void
		render(MeshShader &shader);
};

#endif /* MESH_HPP_ */
