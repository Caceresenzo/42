/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:23:24 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/04 00:23:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/math/vector.hpp>
#include <engine/mesh/Mesh.hpp>
#include <engine/mesh/simple/Grid.hpp>
#include <engine/mesh/Vertex.hpp>
#include <vector>

Mesh*
Grid::of(int slices, bool centered)
{
	std::vector<Vector<3, float> > vertices;
	std::vector<unsigned int> indices;

	int start = 0;
	int end = slices;

	if (centered)
	{
		end = slices / 2;
		start = -end;
	}

	for (int j = start; j <= end; ++j)
	{
		for (int i = start; i <= end; ++i)
		{
			float x = (float)i / (float)slices;
			float z = (float)j / (float)slices;

			vertices.push_back(Vector<3, float>(x, 0, z));
		}
	}

	int rows = slices + 1;
	int vertex_count = (int)vertices.size();
	for (int j = 0; j <= slices; ++j)
	{
		indices.push_back(j * rows);
		indices.push_back((j + 1) * rows - 1);
		indices.push_back(j);
		indices.push_back(vertex_count - rows + j);
	}

	return (new Mesh(Vertex<3>::convert(vertices), indices, Mesh::LINE));
}
