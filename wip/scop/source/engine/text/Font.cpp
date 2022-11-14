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

Font::Font(SharedReference<Texture> &atlas, const Vector<2, float> &character_dimension) :
	atlas(atlas),
	character_dimension(character_dimension)
{
}

Font::~Font()
{
}

SharedReference<Font>
Font::load(const std::string &path, const Vector<2, float> &character_dimension)
{
	BMPImageLoader loader;
	SharedReference<ImageData> image_data = loader.load(path);

	SharedReference<Texture> atlas = Texture::from_image(image_data);

	return (*new Font(atlas, character_dimension));
}

SharedReference<Font>
Font::consolas()
{
	return (load("assets/fonts/consolas.bmp", Vector<2, float>(0.6, 1.0)));
}
