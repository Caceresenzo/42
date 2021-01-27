/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationValidateException.cpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/exceptions/ConfigurationValidateException.hpp>

ConfigurationValidateException::ConfigurationValidateException() :
		ConfigurationException()
{
}

ConfigurationValidateException::ConfigurationValidateException(const std::string &message) :
		ConfigurationException(message)
{
}

ConfigurationValidateException::ConfigurationValidateException(const ConfigurationValidateException &other) :
		ConfigurationException(other)
{
}

ConfigurationValidateException::~ConfigurationValidateException() throw ()
{
}

ConfigurationValidateException&
ConfigurationValidateException::operator=(const ConfigurationValidateException &other)
{
	ConfigurationException::operator=(other);

	return (*this);
}
