/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NoSuchElementException.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOSUCHELEMENTEXCEPTION_HPP_
# define NOSUCHELEMENTEXCEPTION_HPP_

#include <exception/RuntimeException.hpp>
#include <string>

class NoSuchElementException: public RuntimeException
{
	public:
		NoSuchElementException();
		NoSuchElementException(const std::string &message);
		NoSuchElementException(const NoSuchElementException &other);

		virtual
		~NoSuchElementException() throw ();

		NoSuchElementException&
		operator=(const NoSuchElementException &other);
};

#endif /* NOSUCHELEMENTEXCEPTION_HPP_ */
