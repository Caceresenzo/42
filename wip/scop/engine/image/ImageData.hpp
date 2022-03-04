/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ImageData.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:34:15 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/25 12:34:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGEDATA_HPP_
# define IMAGEDATA_HPP_

#include <engine/opengl.hpp>
#include <GL/glew.h>
#include <vector>

class ImageData
{
	public:
		enum Format
		{
			RGB = GL_RGB,
			BGR = GL_BGR,
			RGBA = GL_RGBA,
			BGRA = GL_BGRA
		};

	private:
		Format m_format;
		long m_width;
		long m_height;
		std::vector<unsigned char> m_pixels;

	public:
		ImageData(Format format, long width, long height, const std::vector<unsigned char> &pixels);

		virtual
		~ImageData();

		inline Format
		format() const
		{
			return (m_format);
		}

		inline long
		width() const
		{
			return (m_width);
		}

		inline long
		height() const
		{
			return (m_height);
		}

		inline const std::vector<unsigned char>&
		pixels() const
		{
			return (m_pixels);
		}
};

#endif /* IMAGEDATA_HPP_ */
