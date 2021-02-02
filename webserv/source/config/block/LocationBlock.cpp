/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationBlock.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:10:59 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/12 17:02:52 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/LocationBlock.hpp>
#include <util/helper/DeleteHelper.hpp>
#include <algorithm>

LocationBlock::LocationBlock(const std::string &path) :
		m_path(path),
		m_methods(),
		m_root(),
		m_listing(),
		m_index(),
		m_cgi(),
		m_auth(),
		m_maxBodySize()
{
}

LocationBlock::~LocationBlock()
{
	DeleteHelper::pointer<AuthBlock>(m_auth);
}

LocationBlock&
LocationBlock::methods(const std::list<std::string> &methods)
{
	m_methods.set(methods);

	return (*this);
}

LocationBlock&
LocationBlock::root(const std::string &root)
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
LocationBlock::index(const std::list<std::string> &files)
{
	m_index.set(files);

	return (*this);
}

LocationBlock&
LocationBlock::cgi(const std::string &cgi)
{
	m_cgi.set(cgi);

	return (*this);
}

LocationBlock&
LocationBlock::auth(const AuthBlock &auth)
{
	m_auth.set(&auth);

	return (*this);
}

LocationBlock&
LocationBlock::maxBodySize(const DataSize &maxBodySize)
{
	m_maxBodySize.set(maxBodySize);

	return (*this);
}

bool
LocationBlock::hasMethod(const std::string &name) const
{
	if (!m_methods.present())
		return (false);

	return (std::find(m_methods.get().begin(), m_methods.get().end(), name) != m_methods.get().end());
}
