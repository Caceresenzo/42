/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ImageData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:34:15 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/25 12:34:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/image/ImageData.hpp>

ImageData::ImageData() :
		m_width(-1),
		m_height(-1),
		m_pixels()
{
}

ImageData::ImageData(long width, long height, const std::vector<unsigned char> &pixels) :
		m_width(width),
		m_height(height),
		m_pixels(pixels)
{
}

ImageData::ImageData(const ImageData &other) :
		m_width(other.m_width),
		m_height(other.m_height),
		m_pixels(other.m_pixels)
{
}

ImageData::~ImageData()
{
}

ImageData&
ImageData::operator=(const ImageData &other)
{
	if (this != &other)
	{
		m_width = other.m_width;
		m_height = other.m_height;
		m_pixels = other.m_pixels;
	}

	return (*this);
}

long
ImageData::width() const
{
	return (m_width);
}

long
ImageData::height() const
{
	return (m_height);
}

const std::vector<unsigned char>&
ImageData::pixels() const
{
	return (m_pixels);
}
