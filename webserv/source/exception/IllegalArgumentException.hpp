/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IllegalArgumentException.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:30:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 15:30:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ILLEGALARGUMENTEXCEPTION_HPP_
# define ILLEGALARGUMENTEXCEPTION_HPP_

#include <exception/RuntimeException.hpp>
#include <string>

class IllegalArgumentException :
		public RuntimeException
{
	public:
		IllegalArgumentException(void);
		IllegalArgumentException(const std::string &message);
		IllegalArgumentException(const IllegalArgumentException &other);

		virtual
		~IllegalArgumentException() throw ();

		IllegalArgumentException&
		operator=(const IllegalArgumentException &other);
};

#endif /* ILLEGALARGUMENTEXCEPTION_HPP_ */
