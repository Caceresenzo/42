/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IllegalStateException.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ILLEGALSTATEEXCEPTION_HPP_
# define ILLEGALSTATEEXCEPTION_HPP_

#include <lang/RuntimeException.hpp>
#include <string>

class IllegalStateException: public RuntimeException
{
	public:
		IllegalStateException();
		IllegalStateException(const std::string &message);
		IllegalStateException(const IllegalStateException &other);

		virtual
		~IllegalStateException() throw ();

		IllegalStateException&
		operator=(const IllegalStateException &other);
};

#endif /* ILLEGALSTATEEXCEPTION_HPP_ */
