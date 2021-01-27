/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerBlock.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:34:45 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/21 13:38:45 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/ServerBlock.hpp>
#include <util/helper/DeleteHelper.hpp>
#include <algorithm>

const std::string ServerBlock::DEFAULT_HOST = "0.0.0.0";
const short ServerBlock::DEFAULT_PORT = 80;

ServerBlock::ServerBlock() :
		m_port(),
		m_host(),
		m_names(),
		m_maxBodySize(),
		m_root(),
		m_locations(),
		m_errors()
{
}

ServerBlock::~ServerBlock()
{
	DeleteHelper::pointers(m_locations);
	DeleteHelper::pointer(m_auth);
}

ServerBlock&
ServerBlock::port(int port)
{
	m_port.set(port);

	return (*this);
}

ServerBlock&
ServerBlock::host(const std::string &host)
{
	m_host.set(host);

	return (*this);
}

ServerBlock&
ServerBlock::isDefault(bool isDefault)
{
	m_isDefault.set(isDefault);

	return (*this);
}

ServerBlock&
ServerBlock::names(const std::list<std::string> &names)
{
	m_names.set(names);

	return (*this);
}

ServerBlock&
ServerBlock::maxBodySize(const DataSize &maxBodySize)
{
	m_maxBodySize.set(maxBodySize);

	return (*this);
}

ServerBlock&
ServerBlock::root(const std::string &root)
{
	m_root.set(root);

	return (*this);
}

ServerBlock&
ServerBlock::locations(const std::list<LocationBlock const*> &locations)
{
	m_locations.set(locations);

	return (*this);
}

ServerBlock&
ServerBlock::errors(const CustomErrorMap &errors)
{
	m_errors.set(errors);

	return (*this);
}

ServerBlock&
ServerBlock::methods(const std::list<std::string> &methods)
{
	m_methods.set(methods);

	return (*this);
}

ServerBlock&
ServerBlock::listing(bool listing)
{
	m_listing.set(listing);

	return (*this);
}

ServerBlock&
ServerBlock::index(const std::list<std::string> &files)
{
	m_indexFiles.set(files);

	return (*this);
}

ServerBlock&
ServerBlock::auth(const AuthBlock &auth)
{
	m_auth.set(&auth);

	return (*this);
}

bool
ServerBlock::hasName(const std::string &name) const
{
	if (m_names.present())
	{
		const std::list<std::string> &names = m_names.get();

		return (std::find(names.begin(), names.end(), name) != names.end());
	}

	return (false);
}

bool
ServerBlock::hasMethod(const std::string &name) const
{
	if (!m_methods.present())
		return (false);

	const std::list<std::string> &methods = m_methods.get();

	return (std::find(methods.begin(), methods.end(), name) != methods.end());
}

bool
ServerBlock::hasMaxBodySize() const
{
	if (!m_maxBodySize.present())
		return (false);

	return(true);
}
