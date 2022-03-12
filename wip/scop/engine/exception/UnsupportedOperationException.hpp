/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnsupportedOperationException.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNSUPPORTEDOPERATIONEXCEPTION_HPP_
# define UNSUPPORTEDOPERATIONEXCEPTION_HPP_

#include <engine/exception/RuntimeException.hpp>
#include <string>

class UnsupportedOperationException :
		public RuntimeException
{
	public:
		UnsupportedOperationException();
		UnsupportedOperationException(const std::string &message);
		UnsupportedOperationException(const UnsupportedOperationException &other);

		virtual
		~UnsupportedOperationException() throw ();

		UnsupportedOperationException&
		operator=(const UnsupportedOperationException &other);
};

#endif /* UNSUPPORTEDOPERATIONEXCEPTION_HPP_ */
