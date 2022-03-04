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

ImageData::ImageData(Format format, long width, long height, const std::vector<unsigned char> &pixels) :
		m_format(format),
		m_width(width),
		m_height(height),
		m_pixels(pixels)
{
}

ImageData::~ImageData()
{
}
