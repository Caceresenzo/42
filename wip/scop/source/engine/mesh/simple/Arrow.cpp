/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Arrow.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 02:18:21 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/04 02:18:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/math/vector.hpp>
#include <engine/mesh/Mesh.hpp>
#include <engine/mesh/simple/Arrow.hpp>
#include <engine/mesh/Vertex.hpp>
#include <vector>

Mesh*
Arrow::of(float length)
{
	std::vector<Vector<3, float> > vertices;
	std::vector<unsigned int> indices;

	// X

	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(0.0, 0.0f, 0.0f));
	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(length, 0.0f, 0.0f));

	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(length, 0.0f, 0.0f));
	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(length * 0.75f, length * 0.25f, 0.0f));

	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(length, 0.0f, 0.0f));
	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(length * 0.75f, -length * 0.25f, 0.0f));

	// Y

	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(0.0, 0.0, 0.0f));
	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(0.0, length, 0.0f));

	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(0.0, length, 0.0f));
	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(length * 0.25f, length * 0.75f, 0.0f));

	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(0.0, length, 0.0f));
	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(-length * 0.25f, length * 0.75f, 0.0f));

	// Z

	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(0.0, 0.0f, 0.0));
	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(0.0, 0.0f, length));

	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(0.0, 0.0f, length));
	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(0.0, length * 0.25f, length * 0.75f));

	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(0.0, 0.0f, length));
	indices.push_back(vertices.size());
	vertices.push_back(Vector<3, float>(0.0, -length * 0.25f, length * 0.75f));

	return (new Mesh(Vertex<3>::convert(vertices), indices, Mesh::LINE));
}
