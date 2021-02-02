/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnsupportedHTTPVersion.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/parser/exception/version/UnsupportedHTTPVersion.hpp>
#include <util/Convert.hpp>

UnsupportedHTTPVersion::UnsupportedHTTPVersion() :
		HTTPRequestException()
{
}

UnsupportedHTTPVersion::UnsupportedHTTPVersion(const std::string &message) :
		HTTPRequestException(message)
{
}

UnsupportedHTTPVersion::UnsupportedHTTPVersion(const UnsupportedHTTPVersion &other) :
		HTTPRequestException(other)
{
}

UnsupportedHTTPVersion::~UnsupportedHTTPVersion() throw ()
{
}

UnsupportedHTTPVersion&
UnsupportedHTTPVersion::operator=(const UnsupportedHTTPVersion &other)
{
	RuntimeException::operator=(other);

	return (*this);
}

UnsupportedHTTPVersion
UnsupportedHTTPVersion::of(int major, int minor)
{
	return (UnsupportedHTTPVersion("HTTP/" + Convert::toString(major) + "/" + Convert::toString(minor)));
}
