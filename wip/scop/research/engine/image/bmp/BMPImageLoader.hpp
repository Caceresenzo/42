/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BMPImageLoader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:34:01 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/25 12:34:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMPIMAGELOADER_HPP_
# define BMPIMAGELOADER_HPP_

#include <engine/image/ImageLoader.hpp>
#include <string>

class BMPImageLoader :
		public ImageLoader
{
	public:
		BMPImageLoader();
		BMPImageLoader(const BMPImageLoader &other);

		virtual
		~BMPImageLoader();

		BMPImageLoader&
		operator=(const BMPImageLoader &other);

		virtual ImageData*
		load(const std::string &path);
};

#endif /* BMPIMAGELOADER_HPP_ */
