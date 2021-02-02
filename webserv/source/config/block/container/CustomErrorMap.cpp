/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomErrorMap.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:10:22 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/16 23:10:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/container/CustomErrorMap.hpp>
#include <http/enums/HTTPStatus.hpp>

CustomErrorMap::CustomErrorMap(void) :
		m_storage()
{
}

CustomErrorMap::CustomErrorMap(map storage) :
		m_storage(storage)
{
}

CustomErrorMap::CustomErrorMap(const CustomErrorMap &other) :
		m_storage(other.m_storage)
{
}

CustomErrorMap::~CustomErrorMap(void)
{
}

CustomErrorMap&
CustomErrorMap::operator =(const CustomErrorMap &other)
{
	if (this != &other)
		m_storage = other.m_storage;

	return (*this);
}

bool
CustomErrorMap::has(int status) const
{
	return (m_storage.find(status) != m_storage.end());
}

bool
CustomErrorMap::has(const HTTPStatus &status) const
{
	return (has(status.code()));
}

const std::string&
CustomErrorMap::get(int status) const
{
	return (m_storage.find(status)->second);
}

const std::string&
CustomErrorMap::get(const HTTPStatus &status) const
{
	return (get(status.code()));
}
