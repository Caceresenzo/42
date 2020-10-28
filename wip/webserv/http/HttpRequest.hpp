/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:18:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/20 13:18:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP_
# define HTTPREQUEST_HPP_

# include <io/Socket.hpp>
# include <iostream>
# include <map>

class HttpRequest
{
	private:
		Socket m_socket;
		std::string m_raw;
		std::string m_head;
		std::map<std::string, std::string> m_headers;

	public:
		HttpRequest(void);
		HttpRequest(const Socket &socket);
		HttpRequest(const HttpRequest &other);

		virtual
		~HttpRequest(void);

		HttpRequest&
		operator =(const HttpRequest &other);

		bool
		read(void);

		bool
		write(void);

		void
		setHeader(const std::string &name, const std::string &value);

		bool
		getHeader(const std::string &name, std::string &value);
};

#endif /* HTTPREQUEST_HPP_ */
