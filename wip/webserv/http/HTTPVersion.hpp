/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPVersion.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:43:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 16:43:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPVERSION_HPP_
# define HTTPVERSION_HPP_

# include <iostream>

class HTTPVersion
{
	private:
		int m_major;
		int m_minor;

	public:
		HTTPVersion(void);
		HTTPVersion(int major, int minor);
		HTTPVersion(const HTTPVersion &other);

		virtual
		~HTTPVersion(void);

		HTTPVersion&
		operator=(const HTTPVersion &other);

		std::string
		format(void) const;

		int
		major(void) const;

		int
		minor(void) const;

		static HTTPVersion HTTP_1_1;
};

#endif /* HTTPVERSION_HPP_ */
