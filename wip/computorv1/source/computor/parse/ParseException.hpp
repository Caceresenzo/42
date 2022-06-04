/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseException.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:30:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 15:30:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEEXCEPTION_HPP_
# define PARSEEXCEPTION_HPP_

#include <core/io/StringReader.hpp>
#include <core/lang/Exception.hpp>
#include <string>

class ParseException :
		public Exception
{
	private:
		std::string::size_type m_at;

	public:
		ParseException(void);
		ParseException(const std::string &message);
		ParseException(const std::string &message, std::string::size_type at);
		ParseException(const std::string &message, const StringReader &reader);
		ParseException(const ParseException &other);

		virtual
		~ParseException() throw ();

		ParseException&
		operator=(const ParseException &other);

	public:
		const std::string::size_type&
		at() const;
};

#endif /* PARSEEXCEPTION_HPP_ */
