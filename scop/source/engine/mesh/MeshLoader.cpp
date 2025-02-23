/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshLoader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:40:07 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/28 22:40:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/math/Vector.hpp>
#include <engine/mesh/Mesh.hpp>
#include <engine/mesh/MeshException.hpp>
#include <engine/mesh/MeshLoader.hpp>
#include <engine/mesh/Vertex.hpp>
#include <io/IOException.hpp>
#include <lang/Math.hpp>
#include <stddef.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <vector>

MeshLoader::MeshLoader()
{
}

MeshLoader::~MeshLoader()
{
}

void
MeshLoader::skip_face_remaining(std::istream &stream)
{
	while (stream.peek() == '/')
	{
		stream.ignore(1);
		if (stream.peek() != '/')
		{
			float x = 0.0f;
			stream >> x;
		}
	}
}

Mesh*
MeshLoader::load(const std::string &path)
{
	std::ifstream file(path.c_str());
	if (!file)
		throw IOException(path, errno);

	std::vector<Vector<3, float> > vertices;
	std::vector<Vector<2, float> > textures;
	std::vector<unsigned int> indices;

	int line_number = 1;
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream stream;
		stream << line;

		std::string identifier;
		stream >> identifier;

		if (identifier == "v")
		{
			Vector<3, float> vertice;

			if (!(stream >> vertice.x))
				throw MeshException("vertex: x: invalid");

			if (!(stream >> vertice.y))
				throw MeshException("vertex: y: invalid");

			if (!(stream >> vertice.z))
				throw MeshException("vertex: z: invalid");

			if ((stream >> std::ws).peek() != std::char_traits<char>::eof())
				throw MeshException("vertex: content remain in line");

			vertices.push_back(vertice);
		}
		else if (identifier == "vt")
		{
			Vector<2, float> vertice;

			if (!(stream >> vertice.x))
				throw MeshException("texture vertex: x: invalid");

			if (!(stream >> vertice.y))
				throw MeshException("texture vertex: y: invalid");

			if ((stream >> std::ws).peek() != std::char_traits<char>::eof())
				throw MeshException("texture vertex: content remain in line");

			textures.push_back(vertice);
		}
		else if (identifier == "f")
		{
			Vector<4, float> indice;

			if (!(stream >> indice.x))
				throw MeshException("face: x: invalid");

			skip_face_remaining(stream);

			if (!(stream >> indice.y))
				throw MeshException("face: y: invalid");

			skip_face_remaining(stream);

			if (!(stream >> indice.z))
				throw MeshException("face: z: invalid");

			skip_face_remaining(stream);

			bool square = !!(stream >> indice.w);

			if ((stream >> std::ws).peek() != std::char_traits<char>::eof())
				throw MeshException("face: content remain in line");

			indices.push_back(indice.x - 1);
			indices.push_back(indice.y - 1);
			indices.push_back(indice.z - 1);

			if (square)
			{
				indices.push_back(indice.x - 1);
				indices.push_back(indice.z - 1);
				indices.push_back(indice.w - 1);
			}
		}

		++line_number;
	}

	if (vertices.empty())
		throw MeshException("no vertice found");

	bool has_texture = !textures.empty();
	return (new Mesh(Vertex<3>::convert(vertices, textures), indices, has_texture));
}
