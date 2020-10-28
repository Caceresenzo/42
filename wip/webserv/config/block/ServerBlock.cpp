/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerBlock.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:34:45 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 11:34:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/ServerBlock.hpp>

const std::string ServerBlock::DEFAULT_HOST = "0.0.0.0";

ServerBlock::ServerBlock() :
		m_port(),
		m_host(),
		m_name(),
		m_maxBodySize(),
		m_root(),
		m_locations()
{
}

ServerBlock::ServerBlock(const ServerBlock &other) :
		m_port(other.m_port),
		m_host(other.m_host),
		m_name(other.m_name),
		m_maxBodySize(other.m_maxBodySize),
		m_root(other.m_root),
		m_locations(other.m_locations)
{
}

ServerBlock::~ServerBlock()
{
}

ServerBlock&
ServerBlock::operator =(const ServerBlock &other)
{
	if (this != &other)
	{
		m_port = other.m_port;
		m_host = other.m_host;
		m_name = other.m_name;
		m_maxBodySize = other.m_maxBodySize;
		m_root = other.m_root;
		m_locations = other.m_locations;
	}

	return (*this);
}

ServerBlock&
ServerBlock::port(int port)
{
	m_port.set(port);

	return (*this);
}

const Optional<int>
ServerBlock::port(void) const
{
	return (m_port);
}

ServerBlock&
ServerBlock::host(std::string host)
{
	m_host.set(host);

	return (*this);
}

ServerBlock&
ServerBlock::name(std::string name)
{
	m_name.set(name);

	return (*this);
}

ServerBlock&
ServerBlock::maxBodySize(DataSize maxBodySize)
{
	m_maxBodySize.set(maxBodySize);

	return (*this);
}

ServerBlock&
ServerBlock::root(std::string root)
{
	m_root.set(root);

	return (*this);
}

ServerBlock&
ServerBlock::locations(std::vector<LocationBlock> locations)
{
	m_locations.set(locations);

	return (*this);
}
