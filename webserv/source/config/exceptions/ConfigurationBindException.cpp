/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationBindException.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/exceptions/ConfigurationBindException.hpp>

ConfigurationBindException::ConfigurationBindException() :
		ConfigurationException()
{
}

ConfigurationBindException::ConfigurationBindException(const std::string &message) :
		ConfigurationException(message)
{
}

ConfigurationBindException::ConfigurationBindException(const ConfigurationBindException &other) :
		ConfigurationException(other)
{
}

ConfigurationBindException::~ConfigurationBindException() throw ()
{
}

ConfigurationBindException&
ConfigurationBindException::operator=(const ConfigurationBindException &other)
{
	ConfigurationException::operator=(other);

	return (*this);
}
