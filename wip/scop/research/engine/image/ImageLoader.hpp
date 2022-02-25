/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ImageLoader.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:36:00 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/25 12:36:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGELOADER_HPP_
# define IMAGELOADER_HPP_

#include <string>

class ImageData;

class ImageLoader
{
	public:
		ImageLoader();
		ImageLoader(const ImageLoader &other);

		virtual
		~ImageLoader();

		ImageLoader&
		operator=(const ImageLoader &other);

		virtual ImageData*
		load(const std::string &path) = 0;
};

#endif /* IMAGELOADER_HPP_ */
