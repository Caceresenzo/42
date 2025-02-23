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

#include <lang/image/ImageData.hpp>
#include <lang/image/ImageLoader.hpp>
#include <lang/reference/SharedReference.hpp>
#include <string>

class BMPImageLoader :
		public ImageLoader
{
	public:
		BMPImageLoader();

		virtual
		~BMPImageLoader();

		virtual SharedReference<ImageData>
		load(const std::string &path);
};

#endif /* BMPIMAGELOADER_HPP_ */
