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

#include <io/IOException.hpp>
#include <lang/Math.hpp>
#include <engine/math/vector.hpp>
#include <engine/model/mesh/Mesh.hpp>
#include <engine/model/mesh/MeshException.hpp>
#include <engine/model/mesh/MeshLoader.hpp>
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

Mesh*
MeshLoader::load(const std::string &path)
{
	std::ifstream file(path.c_str());
	if (!file)
		throw IOException(path);

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

			while (stream.peek() == '/')
			{
				char c;
				stream >> c;
				float x = 0.0f;
				stream >> x;
			}

			if (!(stream >> indice.y))
				throw MeshException("face: y: invalid");

			while (stream.peek() == '/')
			{
				char c;
				stream >> c;
				float x = 0.0f;
				stream >> x;
			}

			if (!(stream >> indice.z))
				throw MeshException("face: z: invalid");

			while (stream.peek() == '/')
			{
				char c;
				stream >> c;
				float x = 0.0f;
				stream >> x;
			}

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

	{
		Vector<3, float> lower(std::numeric_limits<float>::max());
		Vector<3, float> higher(std::numeric_limits<float>::min());

		for (std::vector<Vector<3, float> >::const_iterator iterator = vertices.begin(); iterator < vertices.end(); ++iterator)
		{
			const Vector<3, float> &vector = *iterator;

			lower.x = Math::min(lower.x, vector.x);
			lower.y = Math::min(lower.y, vector.y);
			lower.z = Math::min(lower.z, vector.z);

			higher.x = Math::max(higher.x, vector.x);
			higher.y = Math::max(higher.y, vector.y);
			higher.z = Math::max(higher.z, vector.z);
		}

		Vector<3, float> center = ::abs((lower + higher) / 2.0f);
		if (center != Vector<3, float>(0))
			for (std::vector<Vector<3, float> >::iterator iterator = vertices.begin(); iterator < vertices.end(); ++iterator)
				*iterator -= center;
	}

	return (new Mesh(vertices, textures, indices));
}
