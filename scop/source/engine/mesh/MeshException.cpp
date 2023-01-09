/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshException.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/mesh/MeshException.hpp>

MeshException::MeshException(void) :
		RuntimeException()
{
}

MeshException::MeshException(const std::string &message) :
		RuntimeException(message)
{
}

MeshException::MeshException(const MeshException &other) :
		RuntimeException(other)
{
}

MeshException::~MeshException() throw ()
{
}

MeshException&
MeshException::operator=(const MeshException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
