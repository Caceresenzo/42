/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPStatusLine.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:53:31 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/20 19:53:31 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSTATUSLINE_HPP_
# define HTTPSTATUSLINE_HPP_

#include <http/enums/HTTPStatus.hpp>
#include <http/enums/HTTPVersion.hpp>
#include <string>

class HTTPStatusLine
{
	private:
		HTTPVersion m_version;
		const HTTPStatus *m_status;

	public:
		HTTPStatusLine(void);
		HTTPStatusLine(const HTTPStatus &status);
		HTTPStatusLine(const HTTPVersion &version, const HTTPStatus &status);
		HTTPStatusLine(const HTTPStatusLine &other);

		virtual
		~HTTPStatusLine();

		HTTPStatusLine&
		operator=(const HTTPStatusLine &other);

		std::string
		format(void) const;

		const HTTPStatus&
		status() const
		{
			return (*m_status);
		}

		const HTTPVersion&
		version() const
		{
			return (m_version);
		}
};

#endif /* HTTPSTATUSLINE_HPP_ */
