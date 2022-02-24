/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOException.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:20:07 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 15:20:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOEXCEPTION_HPP_
# define IOEXCEPTION_HPP_

#include <engine/exception/Exception.hpp>
#include <string>

class IOException :
		public Exception
{
	private:
		int m_errorno;

	public:
		IOException(void);
		IOException(int errorno);
		IOException(const std::string &message);
		IOException(const std::string &message, int errorno);
		IOException(const IOException &other);

		virtual
		~IOException() throw ();

		IOException&
		operator=(const IOException &other);

		int
		errorno() const;

		static void
		check();

		static void
		check(int errorno);
};

#endif /* IOEXCEPTION_HPP_ */
