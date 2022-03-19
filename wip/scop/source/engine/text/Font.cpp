/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Font.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 20:40:08 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 20:40:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/text/Font.hpp>
#include <lang/image/bmp/BMPImageLoader.hpp>
#include <lang/image/ImageData.hpp>
#include <string>

Font::Font(const std::string &font_atlas_file) :
		m_atlas()
{
	ImageData *image_data = NULL;

	try
	{
		BMPImageLoader loader;
		image_data = loader.load(font_atlas_file);

		m_atlas = *Texture::from_image(image_data);

		delete image_data;
		image_data = NULL;
	}
	catch (...)
	{
		if (image_data)
			delete image_data;

		throw;
	}
}

Font::Font(SharedReference<Texture> &atlas) :
		m_atlas(atlas)
{
}

Font::~Font()
{
}

Font&
Font::consolas()
{
	return (*new Font("assets/fonts/consolas.bmp"));
}
