/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BMPImageLoader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:34:01 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/25 12:34:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io/IOException.hpp>
#include <lang/image/bmp/BMPImageLoader.hpp>
#include <lang/image/ImageData.hpp>
#include <lang/image/ImageException.hpp>
#include <lang/reference/SharedReference.hpp>
#include <cstdio>
#include <cwchar>
#include <vector>

BMPImageLoader::BMPImageLoader()
{
}

BMPImageLoader::~BMPImageLoader()
{
}

SharedReference<ImageData>
BMPImageLoader::load(const std::string &path)
{
	FILE *file = fopen(path.c_str(), "rb");
	if (!file)
		throw IOException(path + " could not be open");

	unsigned char header[54];
	if (fread(header, 1, 54, file) != 54)
	{
		fclose(file);
		throw ImageException("header too small");
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		fclose(file);
		throw ImageException("invalid magic");
	}

	if (*(int*)&(header[0x1E]) != 0)
	{
		fclose(file);
		throw ImageException("unsupported compression");
	}

	if (*(int*)&(header[0x1C]) != 24)
	{
		fclose(file);
		throw ImageException("not a 24bpp");
	}

	unsigned int data_offset = *(int*)&(header[0x0A]);
	unsigned int data_size = *(int*)&(header[0x22]);
	unsigned int width = *(int*)&(header[0x12]);
	unsigned int height = *(int*)&(header[0x16]);

	if (data_size == 0)
		data_size = width * height * 3;

	if (data_offset == 0)
		data_offset = 54;

	std::vector<unsigned char> pixels(data_size);
	if (fread(pixels.data(), 1, data_size, file) != data_size)
	{
		fclose(file);
		throw ImageException("data is incomplete");
	}

	fclose(file);

	return (*new ImageData(ImageData::BGR, width, height, pixels));
}
