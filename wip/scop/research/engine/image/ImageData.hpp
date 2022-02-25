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

#include <vector>

class ImageData
{
	private:
		long m_width;
		long m_height;
		std::vector<unsigned char> m_pixels;

	public:
		ImageData();
		ImageData(long width, long height, const std::vector<unsigned char> &pixels);
		ImageData(const ImageData &other);

		virtual
		~ImageData();

		ImageData&
		operator=(const ImageData &other);

		long
		width() const;

		long
		height() const;

		const std::vector<unsigned char>&
		pixels() const;
};

#endif /* IMAGEDATA_HPP_ */
