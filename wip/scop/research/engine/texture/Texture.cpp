/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:24:02 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/26 19:24:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/exception/IllegalArgumentException.hpp>
#include <engine/image/ImageData.hpp>
#include <engine/texture/Texture.hpp>
#include <vector>

Texture::Texture() :
		m_id(-1)
{
	glGenTextures(1, &m_id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void
Texture::set_active(int unit)
{
	if (unit < 0)
		throw IllegalArgumentException("unit is negative");

	if (unit > 31)
		throw IllegalArgumentException("unit > 31");

	glActiveTexture(GL_TEXTURE0 + unit);
}

void
Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void
Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture*
Texture::from_image(ImageData *image_data)
{
	Texture *texture = new Texture();
	texture->bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_data->width(), image_data->height(), 0, GL_BGR, GL_UNSIGNED_BYTE, image_data->pixels().data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	texture->unbind();

	return (texture);
}
