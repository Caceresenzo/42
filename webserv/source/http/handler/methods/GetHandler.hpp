/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:51:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 18:51:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETHANDLER_HPP_
# define GETHANDLER_HPP_

#include <http/handler/HTTPMethodHandler.hpp>
#include <io/File.hpp>
#include <util/Singleton.hpp>
#include <string>

class URL;

class GetHandler :
		public HTTPMethodHandler,
		public Singleton<GetHandler>
{
	public:
		GetHandler();
		GetHandler(const GetHandler &other);

		virtual
		~GetHandler();

		GetHandler&
		operator =(const GetHandler &other);

		bool
		handle(HTTPClient &client, HTTPRequest &request, HTTPResponse &response);

	private:
		std::string
		listing(const URL &url, const File &file);
};

#endif /* GETHANDLER_HPP_ */
