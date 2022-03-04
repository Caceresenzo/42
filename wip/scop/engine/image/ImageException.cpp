/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ImageException.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/image/ImageException.hpp>

ImageException::ImageException(void) :
		RuntimeException()
{
}

ImageException::ImageException(const std::string &message) :
		RuntimeException(message)
{
}

ImageException::ImageException(const ImageException &other) :
		RuntimeException(other)
{
}

ImageException::~ImageException() throw ()
{
}

ImageException&
ImageException::operator=(const ImageException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
