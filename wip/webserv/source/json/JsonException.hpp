/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonException.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONEXCEPTION_HPP_
# define JSONEXCEPTION_HPP_

#include <exception/Exception.hpp>
#include <string>

class JsonException :
		public Exception
{
	public:
		JsonException(void);
		JsonException(const std::string &message);
		JsonException(const JsonException &other);

		virtual
		~JsonException(void) throw ();

		JsonException&
		operator=(const JsonException &other);
};

#endif /* JSONEXCEPTION_HPP_ */
