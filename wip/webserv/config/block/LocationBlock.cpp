/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationBlock.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:10:59 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 19:10:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/LocationBlock.hpp>

LocationBlock::LocationBlock(void) :
		m_path(),
		m_allowedMethods(),
		m_alias(),
		m_root(),
		m_listing(),
		m_indexFiles()
{
}

LocationBlock::LocationBlock(std::string path) :
		m_path(path),
		m_allowedMethods(),
		m_alias(),
		m_root(),
		m_listing(),
		m_indexFiles()
{
}

LocationBlock::LocationBlock(const LocationBlock &other) :
		m_path(other.m_path),
		m_allowedMethods(other.m_allowedMethods),
		m_alias(other.m_alias),
		m_root(other.m_root),
		m_listing(other.m_listing),
		m_indexFiles(other.m_indexFiles)
{
}

LocationBlock::~LocationBlock()
{
}

LocationBlock&
LocationBlock::operator =(const LocationBlock &other)
{
	if (this != &other)
	{
		m_path = other.m_path;
		m_allowedMethods = other.m_allowedMethods;
		m_alias = other.m_alias;
		m_root = other.m_root;
		m_listing = other.m_listing;
		m_indexFiles = other.m_indexFiles;
	}

	return (*this);
}

LocationBlock&
LocationBlock::allowedMethods(std::vector<std::string> methods)
{
	m_allowedMethods.set(methods);

	return (*this);
}

LocationBlock&
LocationBlock::alias(std::string alias)
{
	m_alias.set(alias);

	return (*this);
}

LocationBlock&
LocationBlock::root(std::string root)
{
	m_root.set(root);

	return (*this);
}

LocationBlock&
LocationBlock::listing(bool listing)
{
	m_listing.set(listing);

	return (*this);
}

LocationBlock&
LocationBlock::indexFiles(std::vector<std::string> files)
{
	m_indexFiles.set(files);

	return (*this);
}
