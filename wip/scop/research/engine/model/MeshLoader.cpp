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

#include <engine/exception/IOException.hpp>
#include <engine/math/vector.hpp>
#include <engine/model/Mesh.hpp>
#include <engine/model/MeshException.hpp>
#include <engine/model/MeshLoader.hpp>
#include <stddef.h>
#include <cstdio>
#include <fstream>
#include <iostream>
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
	std::vector<unsigned int> indices;

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
				throw MeshException();

			if (!(stream >> vertice.y))
				throw MeshException();

			if (!(stream >> vertice.z))
				throw MeshException();

			if ((stream >> std::ws).peek() != std::char_traits<char>::eof())
				throw MeshException();

			vertices.push_back(vertice);
		}
		else if (identifier == "f")
		{
			Vector<4, float> indice;

			if (!(stream >> indice.x))
				throw MeshException();

			if (!(stream >> indice.y))
				throw MeshException();

			if (!(stream >> indice.z))
				throw MeshException();

			bool square = stream >> indice.w;

			if ((stream >> std::ws).peek() != std::char_traits<char>::eof())
				throw MeshException();

			indices.push_back(indice.x);
			indices.push_back(indice.y);
			indices.push_back(indice.z);

			if (square)
			{
				indices.push_back(indice.x);
				indices.push_back(indice.z);
				indices.push_back(indice.w);
			}
		}
	}

	std::vector<Vector<3, float> > vertices_buffer;

	for (size_t i = 0; i < indices.size(); i++)
	{
		int index = indices[i];

		vertices_buffer.push_back(vertices[index - 1]);
	}

	return (new Mesh(vertices_buffer, indices));
//	return (new Mesh(vertices, indices));
}
