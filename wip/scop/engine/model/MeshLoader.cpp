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
			std::cout << line_number << std::endl;

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

			bool square = stream >> indice.w;

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

	std::cout << "----" << std::endl;
	std::cout << vertices.size() << std::endl;
	std::cout << textures.size() << std::endl;
	std::cout << indices.size() << std::endl;

	return (new Mesh(vertices, textures, indices));
}
