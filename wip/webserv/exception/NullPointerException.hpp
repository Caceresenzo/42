/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NullPointerException.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NULLPOINTEREXCEPTION_HPP_
# define NULLPOINTEREXCEPTION_HPP_

#include <exception/RuntimeException.hpp>
#include <string>

class NullPointerException: public RuntimeException
{
	public:
		NullPointerException();
		NullPointerException(const std::string &message);
		NullPointerException(const NullPointerException &other);

		virtual
		~NullPointerException() throw ();

		NullPointerException&
		operator=(const NullPointerException &other);
};

#endif /* NULLPOINTEREXCEPTION_HPP_ */
