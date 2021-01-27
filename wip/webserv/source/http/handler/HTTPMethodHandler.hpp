/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:59:33 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 17:59:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPMETHODHANDLER_HPP_
# define HTTPMETHODHANDLER_HPP_

class HTTPClient;
class HTTPRequest;
class HTTPResponse;

class HTTPMethodHandler
{
	public:
		virtual
		~HTTPMethodHandler();

		/**
		 * Handle a HTTP method.
		 *
		 * @param client Asking client.
		 * @param request Input request.
		 * @param response Output response.
		 * @return Whether or not the filter chain can continue or if the method handler need time to do actions. In which case, the filter chain will not next().
		 */
		virtual bool
		handle(HTTPClient &client, HTTPRequest &request, HTTPResponse &response) = 0;
};

#endif /* HTTPMETHODHANDLER_HPP_ */
