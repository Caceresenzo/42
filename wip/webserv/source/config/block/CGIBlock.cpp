/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIBlock.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:34:15 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 11:34:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/CGIBlock.hpp>
#include <io/File.hpp>
#include <algorithm>

CGIBlock::CGIBlock(const std::string &name) :
		m_name(name),
		m_path(),
		m_handleNotFound(),
		m_extensions(),
		m_environment()
{
}

CGIBlock::~CGIBlock()
{
}

CGIBlock&
CGIBlock::path(const std::string &path)
{
	m_path.set(path);

	return (*this);
}

CGIBlock&
CGIBlock::handleNotFound(bool handleNotFound)
{
	m_handleNotFound.set(handleNotFound);

	return (*this);
}

CGIBlock&
CGIBlock::extensions(const std::list<std::string> &extensions)
{
	m_extensions.set(extensions);

	return (*this);
}

CGIBlock&
CGIBlock::environment(const std::map<std::string, std::string> &environment)
{
	m_environment.set(environment);

	return (*this);
}

bool
CGIBlock::exists() const
{
	if (m_path.present())
		return (File(m_path.get()).exists());

	return (false);
}

bool
CGIBlock::hasExtension(const std::string &extension) const
{
	if (m_extensions.absent())
		return (true);

	const std::list<std::string> &extensions = m_extensions.get();

	return (std::find(extensions.begin(), extensions.end(), extension) != extensions.end());
}
