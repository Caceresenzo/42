/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationException.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/exceptions/ConfigurationException.hpp>

ConfigurationException::ConfigurationException() :
		RuntimeException()
{
}

ConfigurationException::ConfigurationException(const std::string &message) :
		RuntimeException(message)
{
}

ConfigurationException::ConfigurationException(const ConfigurationException &other) :
		RuntimeException(other)
{
}

ConfigurationException::~ConfigurationException() throw ()
{
}

ConfigurationException&
ConfigurationException::operator=(const ConfigurationException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
