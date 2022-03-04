/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ImageException.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGEEXCEPTION_HPP_
# define IMAGEEXCEPTION_HPP_

#include <engine/exception/RuntimeException.hpp>
#include <string>

class ImageException :
		public RuntimeException
{
	public:
		ImageException();
		ImageException(const std::string &message);
		ImageException(const ImageException &other);

		virtual
		~ImageException() throw ();

		ImageException&
		operator=(const ImageException &other);
};

#endif /* IMAGEEXCEPTION_HPP_ */
