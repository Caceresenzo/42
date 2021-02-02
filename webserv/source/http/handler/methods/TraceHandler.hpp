/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TraceHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:42:43 by alicetetu         #+#    #+#             */
/*   Updated: 2020/12/25 10:42:43 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACEHANDLER_HPP_
# define TRACEHANDLER_HPP_

#include <http/handler/HTTPMethodHandler.hpp>
#include <util/Singleton.hpp>

class TraceHandler :
		public HTTPMethodHandler,
		public Singleton<TraceHandler>
{
	public:
		TraceHandler();
		TraceHandler(const TraceHandler &other);

		virtual
		~TraceHandler();

		TraceHandler&
		operator =(const TraceHandler &other);

		bool
		handle(HTTPClient &client, HTTPRequest &request, HTTPResponse &response);
};

#endif /* TraceHANDLER_HPP_ */
