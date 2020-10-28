/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:14:21 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 15:14:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_HPP_
# define EXCEPTION_HPP_

# include <exception>
# include <string>

class Exception :
		public std::exception
{
	private:
		std::string m_message;

	public:
		Exception(void);
		Exception(std::string message);
		Exception(const Exception &other);

		virtual
		~Exception() throw ();

		Exception&
		operator=(const Exception &other);

		const std::string&
		message() const;

		virtual const char*
		what() const throw ();
};

#endif /* EXCEPTION_HPP_ */
