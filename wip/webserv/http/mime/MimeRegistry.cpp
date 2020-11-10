/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeRegistry.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:39:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/26 17:39:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/mime/MimeRegistry.hpp>
#include <stddef.h>
#include <list>
#include <string>
#include <fstream>

MimeRegistry::MimeRegistry(void) :
		m_mapping(),
		m_reverse_mapping()
{
}

MimeRegistry::MimeRegistry(const map &mapping, const map &reverse_mapping) :
		m_mapping(mapping),
		m_reverse_mapping(reverse_mapping)
{
}

MimeRegistry::MimeRegistry(const MimeRegistry &other) :
		m_mapping(other.m_mapping),
		m_reverse_mapping(other.m_reverse_mapping)
{
}

MimeRegistry&
MimeRegistry::operator =(const MimeRegistry &other)
{
	if (this != &other)
	{
		m_mapping = other.m_mapping;
		m_reverse_mapping = other.m_reverse_mapping;
	}

	return (*this);
}

void
MimeRegistry::add(const Mime &mime)
{
	const Mime *old;

	if ((old = findByMimeType(mime.type())) != NULL)
		delete old;

	m_mapping[mime.type()] = new Mime(mime);

	Mime::iterator it = mime.extensions().begin();
	Mime::iterator ite = mime.extensions().end();
	while (it != ite)
	{
		const std::string &extension = *it;

		if ((old = findByFileExtension(extension)) != NULL)
			delete old;

		m_reverse_mapping[extension] = new Mime(mime);

		it++;
	}
}

const Mime*
MimeRegistry::MimeRegistry::findByMimeType(const std::string &type) const
{
	const_iterator it = m_mapping.find(type);

	if (it == m_mapping.end())
		return (NULL);

	return (it->second);
}

const Mime*
MimeRegistry::findByFileExtension(const std::string &type) const
{
	const_iterator it = m_reverse_mapping.find(type);

	if (it == m_reverse_mapping.end())
		return (NULL);

	return (it->second);
}

void // TODO need rework
MimeRegistry::loadFromFile(const std::string &path)
{
	std::ifstream mimeMapFile;
	mimeMapFile.open(path.c_str(), std::ifstream::in);

	while (!mimeMapFile.eof())
	{
		std::string line;
		std::getline(mimeMapFile, line);

		size_t tabPos = line.find('\t');
		if (tabPos == std::string::npos)
		{
			std::cout << "invalid mime.map line (no tab): " << line << std::endl;
			continue;
		}

		std::string type = line.substr(0, tabPos);
		if (type.empty())
		{
			std::cout << "invalid mime.map line (empty type): " << line << std::endl;
			continue;
		}

		std::list<std::string> exts;

		size_t comaPos = tabPos;
		while (true)
		{
			size_t prev = comaPos;

//			std::cout << comaPos << std::endl;
//
//			for (size_t i = 0; i < line.length(); i++)
//				std::cout << (line[i] == '\t' ? ' ' : line[i]);
//			std::cout << std::endl;
//
//			for (size_t i = 0; i < comaPos; i++)
//				std::cout << " ";
//			std::cout << "^" << " (" << comaPos << ")" << std::endl;

			if ((comaPos = line.find(',', comaPos + 1)) != std::string::npos)
			{
				std::string ext = line.substr(prev + 1, comaPos - prev - 1);
//				std::cout << ext << std::endl;

				if (ext.empty())
					std::cout << "invalid extension (empty type): " << line << std::endl;
				else
					exts.push_back(ext);
			}
			else if (comaPos == std::string::npos && prev != line.size() - 1)
			{
				std::string ext = line.substr(prev + 1, line.size() - 1);

				if (!ext.empty())
					exts.push_back(ext);

				break;
			}
			else
			{
				break;
			}
		}

		if (exts.empty())
		{
			std::cout << "invalid mime.map line (empty extensions): " << line << std::endl;
			continue;
		}

		add(Mime(type, exts));

//		std::cout << type << ".." << std::endl;
	}
}
