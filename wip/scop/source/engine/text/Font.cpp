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

Font::Font(SharedReference<Texture> &atlas) :
	atlas(atlas)
{
}

Font::~Font()
{
}

Font&
Font::load(const std::string &path)
{
	ImageData *image_data = NULL;

	try
	{
		BMPImageLoader loader;
		image_data = loader.load(path);

		SharedReference<Texture> atlas = *Texture::from_image(image_data);

		delete image_data;
		image_data = NULL;

		return (*new Font(atlas));
	}
	catch (...)
	{
		if (image_data)
			delete image_data;

		throw;
	}
}

Font&
Font::consolas()
{
	return (load("assets/fonts/consolas.bmp"));
}
