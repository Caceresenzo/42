/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArithmeticException.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ArithmeticException_HPP_
# define ArithmeticException_HPP_

#include <engine/exception/RuntimeException.hpp>
#include <string>

class ArithmeticException :
		public RuntimeException
{
	public:
		ArithmeticException();
		ArithmeticException(const std::string &message);
		ArithmeticException(const ArithmeticException &other);

		virtual
		~ArithmeticException() throw ();

		ArithmeticException&
		operator=(const ArithmeticException &other);
};

#endif /* ArithmeticException_HPP_ */
