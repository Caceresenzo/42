/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RuntimeException.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIMEEXCEPTION_HPP_
# define RUNTIMEEXCEPTION_HPP_

#include <engine/exception/Exception.hpp>
#include <string>

class RuntimeException :
		public Exception
{
	public:
		RuntimeException();
		RuntimeException(const std::string &message);
		RuntimeException(const RuntimeException &other);

		virtual
		~RuntimeException() throw ();

		RuntimeException&
		operator=(const RuntimeException &other);
};

#endif /* RUNTIMEEXCEPTION_HPP_ */
